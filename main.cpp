#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>

#include <osmscoutclientqt/OSMScoutQt.h>

#include "GpsPositionSource.h"
#include "GpxLogger.h"
#include "gpio_reader.h"
#include "MapController.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QQuickWindow::setSceneGraphBackend(QSGRendererInterface::OpenGL);

    QGuiApplication app(argc, argv);

    osmscout::OSMScoutQt::RegisterQmlTypes();
    qmlRegisterType<GpsPositionSource>("Bike.GPS", 1, 0, "GpsPositionSource");

    QStringList mapDirs;
    const QString mapDir = qEnvironmentVariable("BIKECOMPUTER_MAP_DIR");
    if (!mapDir.isEmpty()) {
        mapDirs << mapDir;
    }

    const bool success =
        osmscout::OSMScoutQt::NewInstance()
            .WithMapLookupDirectories(mapDirs)
            .Init();

    if (!success)
    {
        qFatal("OSMScout init failed. Set BIKECOMPUTER_MAP_DIR to a valid map directory.");
        return -1;
    }

    GpioReader btnUp("/dev/gpiochip0", 5);
    GpioReader btnDown("/dev/gpiochip0", 6);
    GpioReader btnOk("/dev/gpiochip0", 26);
    GpxLogger gpxLogger;

    QQmlApplicationEngine engine;

    MapController mapController;
    engine.rootContext()->setContextProperty("mapController", &mapController);

    engine.addImportPath("/usr/local/lib/qml");
    engine.addImportPath("/usr/lib/aarch64-linux-gnu/qt5/qml");

    engine.rootContext()->setContextProperty("btnUp", &btnUp);
    engine.rootContext()->setContextProperty("btnDown", &btnDown);
    engine.rootContext()->setContextProperty("btnOk", &btnOk);
    engine.rootContext()->setContextProperty("gpxLogger", &gpxLogger);

    engine.load(QUrl(QStringLiteral("qrc:/qml/Main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    const int result = app.exec();

    osmscout::OSMScoutQt::FreeInstance();

    return result;
}
