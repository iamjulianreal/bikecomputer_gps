#include "MapController.h"

#include <QDebug>
#include <QMetaObject>

void MapController::setView(QObject *mapViewObj, double lat, double lon, double zoom) {
  if (!mapViewObj) {
    qWarning() << "MapController::setView: mapViewObj is null";
    return;
  }

  bool coordSet = QMetaObject::invokeMethod(mapViewObj, "SetCoord", Q_ARG(double, lat), Q_ARG(double, lon));
  if (!coordSet) {
    coordSet = QMetaObject::invokeMethod(mapViewObj, "setCoord", Q_ARG(double, lat), Q_ARG(double, lon));
  }
  if (!coordSet) {
    coordSet = QMetaObject::invokeMethod(mapViewObj, "Set", Q_ARG(double, lat), Q_ARG(double, lon));
  }

  bool zoomSet = QMetaObject::invokeMethod(mapViewObj, "SetZoom", Q_ARG(double, zoom));
  if (!zoomSet) {
    zoomSet = QMetaObject::invokeMethod(mapViewObj, "setZoom", Q_ARG(double, zoom));
  }

  if (!coordSet || !zoomSet) {
    qWarning() << "MapController::setView: could not invoke expected methods on map view object" << mapViewObj
               << "coordSet=" << coordSet << "zoomSet=" << zoomSet;
  }
}
