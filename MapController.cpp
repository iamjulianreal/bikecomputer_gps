#include "MapController.h"

#include <QDebug>
#include <QMetaMethod>
#include <QMetaObject>
#include <QMetaProperty>
#include <QSet>
#include <QVariant>

namespace {

bool hasMethod(QObject *obj, const char *signature) {
  if (!obj) {
    return false;
  }
  const QByteArray normalized = QMetaObject::normalizedSignature(signature);
  return obj->metaObject()->indexOfMethod(normalized.constData()) >= 0;
}

bool tryInvoke2d(QObject *obj, const char *name, double a, double b) {
  return obj && QMetaObject::invokeMethod(obj, name, Q_ARG(double, a), Q_ARG(double, b));
}

bool tryInvoke1d(QObject *obj, const char *name, double v) {
  return obj && QMetaObject::invokeMethod(obj, name, Q_ARG(double, v));
}

bool tryInvoke1i(QObject *obj, const char *name, int v) {
  return obj && QMetaObject::invokeMethod(obj, name, Q_ARG(int, v));
}

bool trySetCenterAndZoom(QObject *obj, double lat, double lon, double zoom) {
  if (!obj) {
    return false;
  }

  bool latLonSet = false;
  bool zoomSet = false;

  const bool latSet = obj->setProperty("lat", lat);
  const bool lonSet = obj->setProperty("lon", lon);
  if (latSet && lonSet) {
    latLonSet = true;
  }

  if (!latLonSet) {
    if (hasMethod(obj, "showCoordinatesInstantly(double,double)")) {
      latLonSet = tryInvoke2d(obj, "showCoordinatesInstantly", lat, lon);
    } else if (hasMethod(obj, "showCoordinates(double,double)")) {
      latLonSet = tryInvoke2d(obj, "showCoordinates", lat, lon);
    }
  }

  if (!latLonSet) {
    if (hasMethod(obj, "SetCoord(double,double)")) latLonSet = tryInvoke2d(obj, "SetCoord", lat, lon);
    else if (hasMethod(obj, "setCoord(double,double)")) latLonSet = tryInvoke2d(obj, "setCoord", lat, lon);
    else if (hasMethod(obj, "Set(double,double)")) latLonSet = tryInvoke2d(obj, "Set", lat, lon);
    else if (hasMethod(obj, "set(double,double)")) latLonSet = tryInvoke2d(obj, "set", lat, lon);
    else if (hasMethod(obj, "setCenter(double,double)")) latLonSet = tryInvoke2d(obj, "setCenter", lat, lon);
    else if (hasMethod(obj, "SetCenter(double,double)")) latLonSet = tryInvoke2d(obj, "SetCenter", lat, lon);
    else if (hasMethod(obj, "moveTo(double,double)")) latLonSet = tryInvoke2d(obj, "moveTo", lat, lon);
    else if (hasMethod(obj, "MoveTo(double,double)")) latLonSet = tryInvoke2d(obj, "MoveTo", lat, lon);
  }

  zoomSet = obj->setProperty("magLevel", static_cast<int>(zoom)) ||
            obj->setProperty("magLevel", zoom) ||
            obj->setProperty("mag", zoom) ||
            obj->setProperty("zoomLevel", zoom);

  if (!zoomSet) {
    if (hasMethod(obj, "SetZoom(double)")) zoomSet = tryInvoke1d(obj, "SetZoom", zoom);
    else if (hasMethod(obj, "setZoom(double)")) zoomSet = tryInvoke1d(obj, "setZoom", zoom);
    else if (hasMethod(obj, "SetMagnification(double)")) zoomSet = tryInvoke1d(obj, "SetMagnification", zoom);
    else if (hasMethod(obj, "setMagnification(double)")) zoomSet = tryInvoke1d(obj, "setMagnification", zoom);
    else if (hasMethod(obj, "setMag(double)")) zoomSet = tryInvoke1d(obj, "setMag", zoom);
    else if (hasMethod(obj, "SetMag(double)")) zoomSet = tryInvoke1d(obj, "SetMag", zoom);
    else if (hasMethod(obj, "SetZoom(int)")) zoomSet = tryInvoke1i(obj, "SetZoom", static_cast<int>(zoom));
    else if (hasMethod(obj, "setZoom(int)")) zoomSet = tryInvoke1i(obj, "setZoom", static_cast<int>(zoom));
  }

  // Centering is essential; zoom is optional if API does not expose writable zoom.
  return latLonSet;
}

void dumpMetaObjectOnce(QObject *obj, const char *tag) {
  static QSet<QString> dumped;
  if (!obj) {
    return;
  }
  const QString key = QString::fromLatin1(tag) + QLatin1Char(':') + obj->metaObject()->className();
  if (dumped.contains(key)) {
    return;
  }
  dumped.insert(key);

  QStringList properties;
  const QMetaObject *mo = obj->metaObject();
  for (int i = mo->propertyOffset(); i < mo->propertyCount(); ++i) {
    const QMetaProperty p = mo->property(i);
    properties << QStringLiteral("%1(%2)").arg(QString::fromLatin1(p.name()), p.isWritable() ? "rw" : "ro");
  }

  QStringList methods;
  for (int i = mo->methodOffset(); i < mo->methodCount(); ++i) {
    const QMetaMethod m = mo->method(i);
    methods << QString::fromLatin1(m.methodSignature());
  }

  qWarning().noquote() << "MapController meta dump" << tag << mo->className();
  qWarning().noquote() << "  properties:" << properties.join(", ");
  qWarning().noquote() << "  methods:" << methods.join(", ");
}

} // namespace

void MapController::setView(QObject *mapObj, double lat, double lon, double zoom) {
  if (!mapObj) {
    qWarning() << "MapController::setView: map object is null";
    return;
  }

  if (trySetCenterAndZoom(mapObj, lat, lon, zoom)) {
    return;
  }

  QObject *viewObj = nullptr;
  const QVariant viewVariant = mapObj->property("view");
  if (viewVariant.isValid()) {
    viewObj = viewVariant.value<QObject *>();
  }

  if (trySetCenterAndZoom(viewObj, lat, lon, zoom)) {
    return;
  }

  dumpMetaObjectOnce(mapObj, "map");
  dumpMetaObjectOnce(viewObj, "view");

  qWarning() << "MapController::setView: no writable center/zoom API found"
             << "mapClass=" << mapObj->metaObject()->className()
             << "viewClass=" << (viewObj ? viewObj->metaObject()->className() : "<none>");
}
