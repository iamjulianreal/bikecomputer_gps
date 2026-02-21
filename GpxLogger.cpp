#include "GpxLogger.h"

#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QTextStream>
#include <utility>

GpxLogger::GpxLogger(QObject *parent)
    : QObject(parent) {}

void GpxLogger::start() {
  if (m_recording) {
    return;
  }
  m_recording = true;
  emit recordingChanged();
}

void GpxLogger::stop() {
  if (!m_recording) {
    return;
  }
  m_recording = false;
  emit recordingChanged();
}

void GpxLogger::clear() {
  if (m_points.isEmpty()) {
    return;
  }
  m_points.clear();
  emit pointCountChanged();
}

void GpxLogger::addPoint(double latitude, double longitude, double speedKmh, double courseDeg, const QString &isoTimestamp) {
  if (!m_recording) {
    return;
  }

  TrackPoint p;
  p.lat = latitude;
  p.lon = longitude;
  p.speedKmh = speedKmh;
  p.courseDeg = courseDeg;

  p.time = QDateTime::fromString(isoTimestamp, Qt::ISODate);
  if (!p.time.isValid()) {
    p.time = QDateTime::currentDateTimeUtc();
  }

  m_points.push_back(p);
  emit pointCountChanged();
}

QString GpxLogger::save() {
  if (m_points.isEmpty()) {
    emit saveFailed(QStringLiteral("No points to save"));
    return QString();
  }

  QString baseDir = qEnvironmentVariable("BIKECOMPUTER_GPX_DIR");
  if (baseDir.isEmpty()) {
    baseDir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
  }
  if (baseDir.isEmpty()) {
    baseDir = QDir::homePath();
  }

  QDir dir(baseDir);
  if (!dir.exists() && !dir.mkpath(".")) {
    emit saveFailed(QStringLiteral("Failed to create GPX directory: %1").arg(baseDir));
    return QString();
  }

  const QString fileName = QStringLiteral("bikecomputer_%1.gpx")
                               .arg(QDateTime::currentDateTimeUtc().toString("yyyyMMdd_HHmmss"));
  const QString path = dir.filePath(fileName);

  QFile file(path);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    emit saveFailed(QStringLiteral("Failed to open GPX file for writing: %1").arg(path));
    return QString();
  }

  QTextStream out(&file);
  out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
  out << "<gpx version=\"1.1\" creator=\"bikecomputer\" xmlns=\"http://www.topografix.com/GPX/1/1\">\n";
  out << "  <trk>\n";
  out << "    <name>Bike Activity</name>\n";
  out << "    <trkseg>\n";

  for (const TrackPoint &p : std::as_const(m_points)) {
    out << "      <trkpt lat=\"" << QString::number(p.lat, 'f', 8)
        << "\" lon=\"" << QString::number(p.lon, 'f', 8) << "\">\n";
    out << "        <time>" << p.time.toUTC().toString(Qt::ISODate) << "</time>\n";
    out << "        <course>" << QString::number(p.courseDeg, 'f', 2) << "</course>\n";
    out << "        <speed>" << QString::number(p.speedKmh / 3.6, 'f', 3) << "</speed>\n";
    out << "      </trkpt>\n";
  }

  out << "    </trkseg>\n";
  out << "  </trk>\n";
  out << "</gpx>\n";

  file.close();

  m_lastSavedPath = path;
  emit lastSavedPathChanged();

  return path;
}
