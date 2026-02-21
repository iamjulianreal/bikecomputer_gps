#include "GpsPositionSource.h"

#include <QDebug>
#include <array>

#if __has_include(<pigpiod_if2.h>)
#include <pigpiod_if2.h>
#define BIKECOMPUTER_HAS_PIGPIOD 1
#else
#define BIKECOMPUTER_HAS_PIGPIOD 0
#endif

namespace {
constexpr int kPollMs = 100;

bool envEnabled(const char *name) {
  const QByteArray value = qgetenv(name).trimmed().toLower();
  return value == "1" || value == "true" || value == "yes" || value == "on";
}

QByteArray sentenceType(const QByteArray &line) {
  if (line.size() < 6 || !line.startsWith('$')) {
    return QByteArray();
  }
  return line.mid(3, 3);
}
}

GpsPositionSource::GpsPositionSource(QObject *parent)
    : QGeoPositionInfoSource(parent) {
  m_rxPin = qEnvironmentVariableIntValue("BIKECOMPUTER_GPS_RX_PIN");
  if (m_rxPin <= 0) {
    m_rxPin = 13;
  }

  m_txPin = qEnvironmentVariableIntValue("BIKECOMPUTER_GPS_TX_PIN");
  if (m_txPin <= 0) {
    m_txPin = 12;
  }

  m_baud = qEnvironmentVariableIntValue("BIKECOMPUTER_GPS_BAUD");
  if (m_baud <= 0) {
    m_baud = 9600;
  }

  connect(&m_pollTimer, &QTimer::timeout, this, &GpsPositionSource::pollPigpio);
  m_pollTimer.setInterval(kPollMs);

  m_logRelevantNmea = envEnabled("BIKECOMPUTER_GPS_LOG_RELEVANT_NMEA");
  m_logAllNmea = envEnabled("BIKECOMPUTER_GPS_LOG_ALL_NMEA");
}

GpsPositionSource::~GpsPositionSource() {
  stopUpdates();
  closePigpio();
}

void GpsPositionSource::setActive(bool on) {
  if (m_active == on) {
    return;
  }

  m_active = on;
  if (m_active) {
    startUpdates();
  } else {
    stopUpdates();
  }

  emit activeChanged();
}

void GpsPositionSource::startUpdates() {
  if (!openPigpio()) {
    return;
  }
  if (!m_active) {
    m_active = true;
    emit activeChanged();
  }
  m_pollTimer.start();
}

void GpsPositionSource::stopUpdates() {
  m_pollTimer.stop();

  if (m_valid) {
    m_valid = false;
    emit validChanged();
  }
}

void GpsPositionSource::requestUpdate(int timeout) {
  Q_UNUSED(timeout)
  if (!m_pollTimer.isActive()) {
    startUpdates();
  }
  pollPigpio();
}

QGeoPositionInfo GpsPositionSource::lastKnownPosition(bool) const {
  return m_last;
}

QGeoPositionInfoSource::Error GpsPositionSource::error() const {
  return m_lastError;
}

bool GpsPositionSource::openPigpio() {
#if BIKECOMPUTER_HAS_PIGPIOD
  if (m_pi >= 0) {
    return true;
  }

  m_pi = pigpio_start(nullptr, nullptr);
  if (m_pi < 0) {
    m_lastError = QGeoPositionInfoSource::ClosedError;
    emit error(QStringLiteral("pigpio_start failed. Is pigpiod running?"));
    return false;
  }

  set_mode(m_pi, m_txPin, PI_OUTPUT);
  set_mode(m_pi, m_rxPin, PI_INPUT);

  bb_serial_read_close(m_pi, m_rxPin);
  const int openResult = bb_serial_read_open(m_pi, m_rxPin, m_baud, 8);
  if (openResult != 0) {
    m_lastError = QGeoPositionInfoSource::ClosedError;
    emit error(QStringLiteral("bb_serial_read_open failed on RX pin %1, baud %2")
                   .arg(m_rxPin)
                   .arg(m_baud));
    pigpio_stop(m_pi);
    m_pi = -1;
    return false;
  }

  m_lastError = QGeoPositionInfoSource::NoError;
  return true;
#else
  m_lastError = QGeoPositionInfoSource::UnknownSourceError;
  emit error(QStringLiteral("pigpiod_if2.h not available at build time; GPS disabled"));
  return false;
#endif
}

void GpsPositionSource::closePigpio() {
#if BIKECOMPUTER_HAS_PIGPIOD
  if (m_pi < 0) {
    return;
  }

  bb_serial_read_close(m_pi, m_rxPin);
  pigpio_stop(m_pi);
  m_pi = -1;
#endif
}

void GpsPositionSource::pollPigpio() {
#if BIKECOMPUTER_HAS_PIGPIOD
  if (m_pi < 0 && !openPigpio()) {
    return;
  }

  std::array<char, 4096> raw{};
  const int count = bb_serial_read(m_pi, m_rxPin, raw.data(), raw.size());

  if (count > 0) {
    m_readBuffer.append(raw.data(), count);
    processBuffer();
  }
#else
  m_pollTimer.stop();
#endif
}

void GpsPositionSource::processBuffer() {
  while (true) {
    const int newlineIndex = m_readBuffer.indexOf('\n');
    if (newlineIndex < 0) {
      break;
    }

    QByteArray line = m_readBuffer.left(newlineIndex).trimmed();
    m_readBuffer.remove(0, newlineIndex + 1);

    if (!line.isEmpty()) {
      processNmeaLine(line);
    }
  }
}

void GpsPositionSource::processNmeaLine(const QByteArray &line) {
  if (m_logAllNmea || (m_logRelevantNmea && isRelevantNmeaSentence(line))) {
    qInfo().noquote() << "NMEA:" << QString::fromLatin1(line);
  }

  QGeoPositionInfo info;
  double speedKmh = 0.0;
  double courseDeg = 0.0;

  if (!parseRmc(line, info, speedKmh, courseDeg)) {
    return;
  }

  m_last = info;

  if (!m_valid) {
    m_valid = true;
    emit validChanged();
  }

  emit positionUpdated(info);
  emit positionChanged();
  emit fixAvailable(info.coordinate().latitude(), info.coordinate().longitude(), speedKmh, courseDeg,
                    info.timestamp().toString(Qt::ISODate));
}


bool GpsPositionSource::isRelevantNmeaSentence(const QByteArray &line) {
  const QByteArray type = sentenceType(line);
  return type == "RMC" || type == "GGA" || type == "GSA" || type == "GSV";
}

bool GpsPositionSource::parseRmc(const QByteArray &line, QGeoPositionInfo &outInfo, double &speedKmh,
                                 double &courseDeg) const {
  if (sentenceType(line) != "RMC") {
    return false;
  }

  const QList<QByteArray> fields = line.split(',');
  if (fields.size() < 10) {
    return false;
  }

  const QByteArray status = fields.at(2);
  if (status != "A") {
    return false;
  }

  double latitude = 0.0;
  double longitude = 0.0;
  if (!parseLatitude(fields.at(3), fields.at(4), latitude) ||
      !parseLongitude(fields.at(5), fields.at(6), longitude)) {
    return false;
  }

  bool speedOk = false;
  const double speedKnots = fields.at(7).toDouble(&speedOk);
  speedKmh = speedOk ? speedKnots * 1.852 : 0.0;

  bool courseOk = false;
  courseDeg = fields.at(8).toDouble(&courseOk);
  if (!courseOk) {
    courseDeg = 0.0;
  }

  QDateTime timestamp = QDateTime::currentDateTimeUtc();
  const QByteArray timeRaw = fields.at(1);
  const QByteArray dateRaw = fields.at(9);
  if (timeRaw.size() >= 6 && dateRaw.size() == 6) {
    const int hour = timeRaw.mid(0, 2).toInt();
    const int minute = timeRaw.mid(2, 2).toInt();
    const int second = timeRaw.mid(4, 2).toInt();

    const int day = dateRaw.mid(0, 2).toInt();
    const int month = dateRaw.mid(2, 2).toInt();
    const int year = 2000 + dateRaw.mid(4, 2).toInt();

    const QDate date(year, month, day);
    const QTime time(hour, minute, second);
    if (date.isValid() && time.isValid()) {
      timestamp = QDateTime(date, time, Qt::UTC);
    }
  }

  const QGeoCoordinate coordinate(latitude, longitude);
  if (!coordinate.isValid()) {
    return false;
  }

  outInfo = QGeoPositionInfo(coordinate, timestamp);
  outInfo.setAttribute(QGeoPositionInfo::GroundSpeed, speedKmh / 3.6);
  outInfo.setAttribute(QGeoPositionInfo::Direction, courseDeg);
  return true;
}

bool GpsPositionSource::parseLatitude(const QByteArray &value, const QByteArray &hemi, double &out) {
  if (value.size() < 4) {
    return false;
  }

  bool degOk = false;
  bool minOk = false;
  const int degrees = value.left(2).toInt(&degOk);
  const double minutes = value.mid(2).toDouble(&minOk);
  if (!degOk || !minOk) {
    return false;
  }

  out = degrees + (minutes / 60.0);
  if (hemi == "S") {
    out = -out;
  }

  return true;
}

bool GpsPositionSource::parseLongitude(const QByteArray &value, const QByteArray &hemi, double &out) {
  if (value.size() < 5) {
    return false;
  }

  bool degOk = false;
  bool minOk = false;
  const int degrees = value.left(3).toInt(&degOk);
  const double minutes = value.mid(3).toDouble(&minOk);
  if (!degOk || !minOk) {
    return false;
  }

  out = degrees + (minutes / 60.0);
  if (hemi == "W") {
    out = -out;
  }

  return true;
}
