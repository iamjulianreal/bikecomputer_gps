#pragma once

#include <QDateTime>
#include <QObject>
#include <QVector>

struct TrackPoint {
  double lat = 0.0;
  double lon = 0.0;
  double speedKmh = 0.0;
  double courseDeg = 0.0;
  QDateTime time;
};

class GpxLogger : public QObject {
  Q_OBJECT
  Q_PROPERTY(bool recording READ recording NOTIFY recordingChanged)
  Q_PROPERTY(int pointCount READ pointCount NOTIFY pointCountChanged)
  Q_PROPERTY(QString lastSavedPath READ lastSavedPath NOTIFY lastSavedPathChanged)

public:
  explicit GpxLogger(QObject *parent = nullptr);

  bool recording() const { return m_recording; }
  int pointCount() const { return m_points.size(); }
  QString lastSavedPath() const { return m_lastSavedPath; }

  Q_INVOKABLE void start();
  Q_INVOKABLE void stop();
  Q_INVOKABLE void clear();
  Q_INVOKABLE QString save();

public slots:
  void addPoint(double latitude, double longitude, double speedKmh, double courseDeg, const QString &isoTimestamp);

signals:
  void recordingChanged();
  void pointCountChanged();
  void lastSavedPathChanged();
  void saveFailed(const QString &message);

private:
  bool m_recording = false;
  QVector<TrackPoint> m_points;
  QString m_lastSavedPath;
};
