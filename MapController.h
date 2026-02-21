#pragma once
#include <QObject>

class MapController : public QObject {
  Q_OBJECT
public:
  explicit MapController(QObject* parent=nullptr) : QObject(parent) {}

  Q_INVOKABLE void setView(QObject* mapViewObj, double lat, double lon, double zoom);
};
