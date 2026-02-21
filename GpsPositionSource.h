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

public:
  explicit GpsPositionSource(QObject *parent = nullptr);
  ~GpsPositionSource() override;

  QGeoPositionInfo lastKnownPosition(bool fromSatellitePositioningMethodsOnly = false) const override;
  Error error() const override;

  PositioningMethods supportedPositioningMethods() const override {
    return QGeoPositionInfoSource::SatellitePositioningMethods;
  }

  int minimumUpdateInterval() const override { return 200; }

  bool active() const { return m_active; }
  bool valid() const { return m_valid; }
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
  void closePigpio();
  void processBuffer();
  void processNmeaLine(const QByteArray &line);
  bool parseRmc(const QByteArray &line, QGeoPositionInfo &outInfo, double &speedKmh, double &courseDeg) const;
  static bool parseLatitude(const QByteArray &value, const QByteArray &hemi, double &out);
  static bool parseLongitude(const QByteArray &value, const QByteArray &hemi, double &out);

  int m_pi = -1;
  int m_rxPin = 13;
  int m_txPin = 12;
  int m_baud = 9600;

  QTimer m_pollTimer;
  QByteArray m_readBuffer;

  QGeoPositionInfo m_last;
  bool m_active = false;
  bool m_valid = false;
  Error m_lastError = QGeoPositionInfoSource::NoError;
};
