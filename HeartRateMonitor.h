#pragma once

#include <QBluetoothAddress>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
#include <QBluetoothUuid>
#include <QLowEnergyCharacteristic>
#include <QLowEnergyController>
#include <QLowEnergyDescriptor>
#include <QLowEnergyService>
#include <QObject>
#include <QTimer>

class HeartRateMonitor : public QObject {
  Q_OBJECT
  Q_PROPERTY(int currentHeartRate READ currentHeartRate NOTIFY currentHeartRateChanged)
  Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)

public:
  explicit HeartRateMonitor(QObject *parent = nullptr);
  ~HeartRateMonitor() override;

  int currentHeartRate() const { return m_currentHeartRate; }
  bool connected() const { return m_connected; }

signals:
  void currentHeartRateChanged();
  void connectedChanged();
  void heartRateReceived(int heartRate);

private slots:
  void startScan();
  void onDeviceDiscovered(const QBluetoothDeviceInfo &device);
  void onScanFinished();
  void onScanError(QBluetoothDeviceDiscoveryAgent::Error error);

  void connectToDevice(const QBluetoothDeviceInfo &device);
  void onControllerConnected();
  void onControllerDisconnected();
  void onControllerError(QLowEnergyController::Error error);
  void onServiceDiscovered(const QBluetoothUuid &serviceUuid);
  void onServiceDiscoveryFinished();

  void onServiceStateChanged(QLowEnergyService::ServiceState newState);
  void onServiceError(QLowEnergyService::ServiceError error);
  void onCharacteristicChanged(const QLowEnergyCharacteristic &characteristic, const QByteArray &value);
  void onDescriptorWritten(const QLowEnergyDescriptor &descriptor, const QByteArray &value);
  void publishPendingHeartRate();

private:
  static constexpr const char *kTargetNamePrefix = "HRMPro+";
  static constexpr const char *kTargetMac = "FC:6C:06:AC:0C:57";
  static constexpr int kScanDurationMs = 5000;
  static constexpr int kReconnectDelayMs = 3000;
  static constexpr int kPublishIntervalMs = 1000;

  bool matchesTargetDevice(const QBluetoothDeviceInfo &device) const;
  void scheduleReconnect(const QString &reason);
  void resetController();
  void resetService();
  void setCurrentHeartRate(int heartRate);
  void clearCurrentHeartRate();
  void setConnected(bool connected);
  void subscribeToHeartRateMeasurement();
  int parseHeartRate(const QByteArray &value) const;

  QBluetoothAddress m_targetAddress;
  QBluetoothDeviceDiscoveryAgent *m_discoveryAgent = nullptr;
  QLowEnergyController *m_controller = nullptr;
  QLowEnergyService *m_heartRateService = nullptr;
  QLowEnergyCharacteristic m_heartRateCharacteristic;
  QBluetoothDeviceInfo m_targetDevice;
  QTimer m_reconnectTimer;
  QTimer m_publishTimer;
  bool m_scanInProgress = false;
  bool m_heartRateServiceFound = false;
  bool m_connected = false;
  int m_currentHeartRate = 0;
  int m_pendingHeartRate = 0;
};
