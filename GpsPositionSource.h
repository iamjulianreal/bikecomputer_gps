#pragma once

#include <QByteArray>
#include <QDateTime>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>
#include <QTimer>

class GpsPositionSource : public QGeoPositionInfoSource {
  Q_OBJECT
  Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)
  Q_PROPERTY(bool valid READ valid NOTIFY validChanged)
  Q_PROPERTY(double latitude READ latitude NOTIFY positionChanged)
  Q_PROPERTY(double longitude READ longitude NOTIFY positionChanged)
  Q_PROPERTY(double speedKmh READ speedKmh NOTIFY positionChanged)
  Q_PROPERTY(double courseDeg READ courseDeg NOTIFY positionChanged)
  Q_PROPERTY(double altitudeMeters READ altitudeMeters NOTIFY positionChanged)

public:
  explicit GpsPositionSource(QObject *parent = nullptr);
  ~GpsPositionSource() override;

  QGeoPositionInfo lastKnownPosition(bool fromSatellitePositioningMethodsOnly = false) const override;
  Error error() const override;

  PositioningMethods supportedPositioningMethods() const override {
    return QGeoPositionInfoSource::AllPositioningMethods;
  }

  int minimumUpdateInterval() const override { return 200; }

  bool active() const { return m_active; }
  bool valid() const { return m_valid; }
  double latitude() const { return m_last.coordinate().latitude(); }
  double longitude() const { return m_last.coordinate().longitude(); }
  double speedKmh() const { return m_last.attribute(QGeoPositionInfo::GroundSpeed) * 3.6; }
  double courseDeg() const { return m_last.attribute(QGeoPositionInfo::Direction); }
  double altitudeMeters() const { return m_last.coordinate().altitude(); }
  void setActive(bool on);

public slots:
  void startUpdates() override;
  void stopUpdates() override;
  void requestUpdate(int timeout = 0) override;

signals:
  void activeChanged();
  void validChanged();
  void positionChanged();
  void error(const QString &message);
  void fixAvailable(double latitude, double longitude, double speedKmh, double courseDeg, const QString &isoTimestamp);

private slots:
  void pollPigpio();

private:
  bool openPigpio();
  static bool isRelevantNmeaSentence(const QByteArray &line);
  void closePigpio();
  void processBuffer();
  void processNmeaLine(const QByteArray &line);
  bool parseRmc(const QByteArray &line, QGeoPositionInfo &outInfo, double &speedKmh, double &courseDeg) const;
  bool parseGgaPosition(const QByteArray &line, QGeoPositionInfo &outInfo) const;
  bool parseGgaAltitude(const QByteArray &line, double &altitudeMeters) const;
  static bool parseLatitude(const QByteArray &value, const QByteArray &hemi, double &out);
  static bool parseLongitude(const QByteArray &value, const QByteArray &hemi, double &out);

  int m_pi = -1;
  int m_rxPin = 13;
  int m_txPin = 12;
  int m_baud = 9600;

  bool m_logRelevantNmea = false;
  bool m_logAllNmea = false;
  double m_lastAltitudeMeters = 0.0;
  bool m_hasAltitude = false;

  QTimer m_pollTimer;
  QByteArray m_readBuffer;

  QGeoPositionInfo m_last;
  bool m_active = false;
  bool m_valid = false;
  Error m_lastError = QGeoPositionInfoSource::NoError;
};
