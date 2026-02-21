#include "MapController.h"
#include <QDebug>

// IMPORTANT: include the libosmscout Qt headers that define osmscout::MapView
// The exact include path can differ depending on how you built libosmscout.
// Try these in order; one should work in your project:
#include <osmscoutclientqt/MapView.h>
// If that fails, alternatives (comment the above and try one):
// #include <osmscout/MapView.h>
// #include <osmscoutqt/MapView.h>

void MapController::setView(QObject* mapViewObj, double lat, double lon, double zoom)
{
  if (!mapViewObj) {
    qWarning() << "MapController::setView: mapViewObj is null";
    return;
  }

  // QML gives us an osmscout::MapView as QObject*. We need a cast.
  auto* view = qobject_cast<osmscout::MapView*>(mapViewObj);
  if (!view) {
    qWarning() << "MapController::setView: object is not osmscout::MapView, got:" << mapViewObj;
    return;
  }

  // These method names depend on libosmscout version. Common patterns:
  // Try the one that matches your headers. If compile fails, I’ll tell you the exact one to use.
  view->SetCoord(lat, lon);   // or view->Set(lat, lon) depending on version
  view->SetZoom(zoom);        // or view->SetMagnification(...)
}
