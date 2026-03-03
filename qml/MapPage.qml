import QtQuick 2.7
import QtPositioning 5.2
import net.sf.libosmscout.map 1.0

Item {
    id: root
    anchors.fill: parent

    property var positionSource
    property real fallbackLat: 48.207200
    property real fallbackLon: 15.618000
    property real startZoom: 12000
    property bool follow: true
    property bool zoomMode: false

    property bool initialViewSet: false
    property bool fallbackUsed: false

    function haveFix() {
        return root.positionSource
            && isFinite(root.positionSource.latitude)
            && isFinite(root.positionSource.longitude)
    }

    function setView(lat, lon, zoom) {
        if (!map) return
        mapController.setView(map, lat, lon, zoom)
    }

    function applyInitialView() {
        if (root.initialViewSet)
            return

        if (haveFix()) {
            setView(root.positionSource.latitude, root.positionSource.longitude, root.startZoom)
            root.fallbackUsed = false
        } else {
            setView(root.fallbackLat, root.fallbackLon, root.startZoom)
            root.fallbackUsed = true
        }

        root.initialViewSet = true
    }

    Map {
        id: map
        anchors.fill: parent
        focus: true
        renderingType: "plane"
        interactiveIcons: true
 
        vehicleStandardIconFile: ":/qml/icons/vehicle.svg"
        vehicleNoGpsSignalIconFile: ":/qml/icons/vehicle_not_fixed.svg"
        vehicleInTunnelIconFile: ":/qml/icons/vehicle_tunnel.svg"

        onDatabaseLoadedChanged: {
            if (databaseLoaded) {
                Qt.callLater(root.applyInitialView)
            }
        }

        Component.onCompleted: {
            console.log("Map has view:", map.view)
            if (map.view) {
                console.log("view keys:", Object.keys(map.view))
                console.log("view.toString:", map.view.toString())
            }
            if (map.databaseLoaded) Qt.callLater(root.applyInitialView)
        }

    }

    Item {
        id: riderMarker
        width: 22
        height: 22
        anchors.centerIn: parent
        visible: root.haveFix()

        rotation: {
            if (!root.positionSource)
                return 0
            var d = root.positionSource.courseDeg
            return isNaN(d) ? 0 : d
        }

        Rectangle {
            anchors.centerIn: parent
            width: 4
            height: 4
            radius: 2
            color: "white"
        }

        Canvas {
            anchors.centerIn: parent
            width: 20
            height: 20
            onPaint: {
                var ctx = getContext("2d")
                ctx.reset()
                ctx.beginPath()
                ctx.moveTo(width / 2, 1)
                ctx.lineTo(width - 2, height - 3)
                ctx.lineTo(width / 2, height - 8)
                ctx.lineTo(2, height - 3)
                ctx.closePath()
                ctx.fillStyle = "#00AEEF"
                ctx.fill()
                ctx.lineWidth = 1
                ctx.strokeStyle = "white"
                ctx.stroke()
            }
        }
    }

    Connections {
        target: root.positionSource

        function onPositionChanged() {
            if (!root.initialViewSet && map.databaseLoaded) {
                Qt.callLater(root.applyInitialView)
            }

            if (!haveFix()) {
                if (root.initialViewSet && !root.fallbackUsed) {
                    root.setView(root.fallbackLat, root.fallbackLon, root.startZoom)
                    root.fallbackUsed = true
                }
                return
            }

            root.fallbackUsed = false

            if (!root.follow)
                return

            root.setView(root.positionSource.latitude,
                         root.positionSource.longitude,
                         root.startZoom)
        }
    }

    function zoomIn()  { map.zoomIn(1.4) }
    function zoomOut() { map.zoomOut(1.4) }

    function setZoomMode(enabled) { root.zoomMode = enabled }
    function toggleFollow() { root.follow = !root.follow }

    function recenter() {
        root.follow = true
        root.fallbackUsed = false
        if (map.databaseLoaded)
            Qt.callLater(root.applyInitialView)
    }
}
