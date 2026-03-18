#include "HeartRateMonitor.h"

#include <QDebug>

namespace {
const QBluetoothUuid kHeartRateServiceUuid(
    QStringLiteral("0000180d-0000-1000-8000-00805f9b34fb"));
const QBluetoothUuid kHeartRateMeasurementUuid(
    QStringLiteral("00002a37-0000-1000-8000-00805f9b34fb"));
const QByteArray kNotificationEnableValue = QByteArray::fromHex("0100");
}

HeartRateMonitor::HeartRateMonitor(QObject *parent)
    : QObject(parent), m_targetAddress(QString::fromLatin1(kTargetMac)),
      m_discoveryAgent(new QBluetoothDeviceDiscoveryAgent(this)) {
  m_discoveryAgent->setLowEnergyDiscoveryTimeout(kScanDurationMs);

  connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this,
          &HeartRateMonitor::onDeviceDiscovered);
  connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished, this,
          &HeartRateMonitor::onScanFinished);
  connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::canceled, this,
          &HeartRateMonitor::onScanFinished);
  connect(m_discoveryAgent,
          QOverload<QBluetoothDeviceDiscoveryAgent::Error>::of(&QBluetoothDeviceDiscoveryAgent::error), this,
          &HeartRateMonitor::onScanError);

  m_reconnectTimer.setSingleShot(true);
  connect(&m_reconnectTimer, &QTimer::timeout, this, &HeartRateMonitor::startScan);

  m_publishTimer.setInterval(kPublishIntervalMs);
  connect(&m_publishTimer, &QTimer::timeout, this, &HeartRateMonitor::publishPendingHeartRate);

  qDebug() << "HeartRateMonitor initialized for" << kTargetNamePrefix << m_targetAddress.toString();
  QTimer::singleShot(0, this, &HeartRateMonitor::startScan);
}

HeartRateMonitor::~HeartRateMonitor() {
  m_publishTimer.stop();
  m_reconnectTimer.stop();
  if (m_discoveryAgent->isActive()) {
    m_discoveryAgent->stop();
  }
  resetController();
}

void HeartRateMonitor::startScan() {
  if (m_controller != nullptr) {
    qDebug() << "HeartRateMonitor skipping scan because controller already exists";
    return;
  }

  if (m_discoveryAgent->isActive()) {
    qDebug() << "HeartRateMonitor scan already in progress";
    return;
  }

  m_reconnectTimer.stop();
  m_targetDevice = QBluetoothDeviceInfo();
  m_scanInProgress = true;
  setConnected(false);

  qDebug() << "HeartRateMonitor starting BLE scan for" << m_targetAddress.toString();
  m_discoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
}

void HeartRateMonitor::onDeviceDiscovered(const QBluetoothDeviceInfo &device) {
  const bool isLowEnergy = (device.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration) != 0;
  qDebug() << "HeartRateMonitor found device" << device.name() << device.address().toString() << "LE=" << isLowEnergy;

  if (!isLowEnergy || !matchesTargetDevice(device)) {
    return;
  }

  m_targetDevice = device;
  qDebug() << "HeartRateMonitor matched target device" << device.name() << device.address().toString();

  if (m_discoveryAgent->isActive()) {
    m_discoveryAgent->stop();
  }
}

void HeartRateMonitor::onScanFinished() {
  m_scanInProgress = false;

  if (!m_targetDevice.isValid()) {
    qDebug() << "HeartRateMonitor scan finished without finding target belt";
    scheduleReconnect(QStringLiteral("target not found during scan"));
    return;
  }

  connectToDevice(m_targetDevice);
}

void HeartRateMonitor::onScanError(QBluetoothDeviceDiscoveryAgent::Error error) {
  m_scanInProgress = false;
  qDebug() << "HeartRateMonitor scan error" << error << m_discoveryAgent->errorString();
  scheduleReconnect(QStringLiteral("scan error: %1").arg(m_discoveryAgent->errorString()));
}

void HeartRateMonitor::connectToDevice(const QBluetoothDeviceInfo &device) {
  if (m_controller != nullptr) {
    qDebug() << "HeartRateMonitor controller already exists, not creating a second one";
    return;
  }

  qDebug() << "HeartRateMonitor connecting to" << device.name() << device.address().toString();

  m_heartRateServiceFound = false;
  m_heartRateCharacteristic = QLowEnergyCharacteristic();

  m_controller = QLowEnergyController::createCentral(device, this);
  connect(m_controller, &QLowEnergyController::connected, this, &HeartRateMonitor::onControllerConnected);
  connect(m_controller, &QLowEnergyController::disconnected, this, &HeartRateMonitor::onControllerDisconnected);
  connect(m_controller, &QLowEnergyController::serviceDiscovered, this, &HeartRateMonitor::onServiceDiscovered);
  connect(m_controller, &QLowEnergyController::discoveryFinished, this,
          &HeartRateMonitor::onServiceDiscoveryFinished);
  connect(m_controller, QOverload<QLowEnergyController::Error>::of(&QLowEnergyController::error), this,
          &HeartRateMonitor::onControllerError);

  m_controller->connectToDevice();
}

void HeartRateMonitor::onControllerConnected() {
  qDebug() << "HeartRateMonitor connected, discovering services";
  if (m_controller != nullptr) {
    m_controller->discoverServices();
  }
}

void HeartRateMonitor::onControllerDisconnected() {
  qDebug() << "HeartRateMonitor disconnected from belt";
  setConnected(false);
  clearCurrentHeartRate();
  resetController();
  scheduleReconnect(QStringLiteral("device disconnected"));
}

void HeartRateMonitor::onControllerError(QLowEnergyController::Error error) {
  const QString errorString = m_controller != nullptr ? m_controller->errorString() : QStringLiteral("unknown error");
  qDebug() << "HeartRateMonitor controller error" << error << errorString;
  setConnected(false);
  clearCurrentHeartRate();
  resetController();
  scheduleReconnect(QStringLiteral("controller error: %1").arg(errorString));
}

void HeartRateMonitor::onServiceDiscovered(const QBluetoothUuid &serviceUuid) {
  qDebug() << "HeartRateMonitor discovered service" << serviceUuid.toString();
  if (serviceUuid == kHeartRateServiceUuid) {
    m_heartRateServiceFound = true;
  }
}

void HeartRateMonitor::onServiceDiscoveryFinished() {
  qDebug() << "HeartRateMonitor service discovery finished, heart rate service found=" << m_heartRateServiceFound;

  if (m_controller == nullptr || !m_heartRateServiceFound) {
    scheduleReconnect(QStringLiteral("heart rate service not found"));
    return;
  }

  resetService();
  m_heartRateService = m_controller->createServiceObject(kHeartRateServiceUuid, this);
  if (m_heartRateService == nullptr) {
    qDebug() << "HeartRateMonitor failed to create heart rate service object";
    scheduleReconnect(QStringLiteral("failed to create heart rate service"));
    return;
  }

  connect(m_heartRateService, &QLowEnergyService::stateChanged, this, &HeartRateMonitor::onServiceStateChanged);
  connect(m_heartRateService,
          QOverload<QLowEnergyService::ServiceError>::of(&QLowEnergyService::error), this,
          &HeartRateMonitor::onServiceError);
  connect(m_heartRateService, &QLowEnergyService::characteristicChanged, this,
          &HeartRateMonitor::onCharacteristicChanged);
  connect(m_heartRateService, &QLowEnergyService::descriptorWritten, this,
          &HeartRateMonitor::onDescriptorWritten);

  qDebug() << "HeartRateMonitor discovering Heart Rate service details";
  m_heartRateService->discoverDetails();
}

void HeartRateMonitor::onServiceStateChanged(QLowEnergyService::ServiceState newState) {
  qDebug() << "HeartRateMonitor service state changed" << newState;
  if (newState == QLowEnergyService::ServiceDiscovered) {
    subscribeToHeartRateMeasurement();
  }
}

void HeartRateMonitor::onServiceError(QLowEnergyService::ServiceError error) {
  qDebug() << "HeartRateMonitor service error" << error;
  setConnected(false);
  scheduleReconnect(QStringLiteral("heart rate service error"));
}

void HeartRateMonitor::onCharacteristicChanged(const QLowEnergyCharacteristic &characteristic,
                                               const QByteArray &value) {
  if (characteristic.uuid() != kHeartRateMeasurementUuid) {
    return;
  }

  const int heartRate = parseHeartRate(value);
  if (heartRate <= 0) {
    qDebug() << "HeartRateMonitor received invalid HR payload" << value.toHex();
    return;
  }

  m_pendingHeartRate = heartRate;

  if (!m_publishTimer.isActive()) {
    publishPendingHeartRate();
    m_publishTimer.start();
  }
}

void HeartRateMonitor::onDescriptorWritten(const QLowEnergyDescriptor &descriptor, const QByteArray &value) {
  qDebug() << "HeartRateMonitor descriptor written" << descriptor.uuid().toString() << value.toHex();

  if (descriptor.uuid() == QBluetoothUuid::ClientCharacteristicConfiguration && value == kNotificationEnableValue) {
    setConnected(true);
  }
}

void HeartRateMonitor::publishPendingHeartRate() {
  if (m_pendingHeartRate <= 0) {
    return;
  }

  const int heartRate = m_pendingHeartRate;
  m_pendingHeartRate = 0;

  qDebug() << "HeartRateMonitor HR value" << heartRate << "bpm";
  setCurrentHeartRate(heartRate);
  emit heartRateReceived(heartRate);
}

bool HeartRateMonitor::matchesTargetDevice(const QBluetoothDeviceInfo &device) const {
  if (device.address() != m_targetAddress) {
    return false;
  }

  const QString name = device.name().trimmed();
  if (!name.isEmpty() && !name.startsWith(QString::fromLatin1(kTargetNamePrefix))) {
    qDebug() << "HeartRateMonitor target MAC matched, but name differs:" << name;
  }

  return true;
}

void HeartRateMonitor::scheduleReconnect(const QString &reason) {
  if (m_scanInProgress || m_discoveryAgent->isActive()) {
    m_discoveryAgent->stop();
  }

  if (m_controller != nullptr) {
    resetController();
  }

  if (!m_reconnectTimer.isActive()) {
    qDebug() << "HeartRateMonitor scheduling reconnect in" << kReconnectDelayMs << "ms because" << reason;
    m_reconnectTimer.start(kReconnectDelayMs);
  } else {
    qDebug() << "HeartRateMonitor reconnect already scheduled, latest reason:" << reason;
  }
}

void HeartRateMonitor::resetController() {
  resetService();

  if (m_controller == nullptr) {
    return;
  }

  m_controller->disconnect(this);
  if (m_controller->state() != QLowEnergyController::UnconnectedState) {
    m_controller->disconnectFromDevice();
  }
  m_controller->deleteLater();
  m_controller = nullptr;
  m_heartRateServiceFound = false;
  m_heartRateCharacteristic = QLowEnergyCharacteristic();
}

void HeartRateMonitor::resetService() {
  if (m_heartRateService == nullptr) {
    return;
  }

  m_heartRateService->disconnect(this);
  m_heartRateService->deleteLater();
  m_heartRateService = nullptr;
  m_heartRateCharacteristic = QLowEnergyCharacteristic();
}

void HeartRateMonitor::setCurrentHeartRate(int heartRate) {
  if (m_currentHeartRate == heartRate) {
    return;
  }

  m_currentHeartRate = heartRate;
  emit currentHeartRateChanged();
}

void HeartRateMonitor::clearCurrentHeartRate() {
  m_publishTimer.stop();
  m_pendingHeartRate = 0;

  if (m_currentHeartRate == 0) {
    return;
  }

  m_currentHeartRate = 0;
  emit currentHeartRateChanged();
}

void HeartRateMonitor::setConnected(bool connected) {
  if (m_connected == connected) {
    return;
  }

  m_connected = connected;
  emit connectedChanged();
}

void HeartRateMonitor::subscribeToHeartRateMeasurement() {
  if (m_heartRateService == nullptr) {
    scheduleReconnect(QStringLiteral("service object missing during subscribe"));
    return;
  }

  m_heartRateCharacteristic = m_heartRateService->characteristic(kHeartRateMeasurementUuid);
  if (!m_heartRateCharacteristic.isValid()) {
    qDebug() << "HeartRateMonitor heart rate measurement characteristic missing";
    scheduleReconnect(QStringLiteral("heart rate measurement characteristic missing"));
    return;
  }

  const QLowEnergyDescriptor cccDescriptor =
      m_heartRateCharacteristic.descriptor(QBluetoothUuid::ClientCharacteristicConfiguration);
  if (!cccDescriptor.isValid()) {
    qDebug() << "HeartRateMonitor CCC descriptor missing for HR measurement";
    scheduleReconnect(QStringLiteral("ccc descriptor missing for heart rate measurement"));
    return;
  }

  qDebug() << "HeartRateMonitor subscribing to HR notifications";
  m_heartRateService->writeDescriptor(cccDescriptor, kNotificationEnableValue);
}

int HeartRateMonitor::parseHeartRate(const QByteArray &value) const {
  if (value.size() < 2) {
    return 0;
  }

  const quint8 flags = static_cast<quint8>(value.at(0));
  if ((flags & 0x01U) == 0U) {
    return static_cast<quint8>(value.at(1));
  }

  if (value.size() < 3) {
    return 0;
  }

  const quint8 low = static_cast<quint8>(value.at(1));
  const quint8 high = static_cast<quint8>(value.at(2));
  return static_cast<int>((static_cast<quint16>(high) << 8U) | low);
}
