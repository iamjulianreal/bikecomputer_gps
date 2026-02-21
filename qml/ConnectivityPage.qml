import QtQuick 2.7
import QtQuick.Controls 2.7
import QtPositioning 5.2

Item {
    id: root
    anchors.fill: parent

    property var positionSource
    property real fallbackLat: 48.207200
    property real fallbackLon: 15.618000

    Rectangle { anchors.fill: parent; color: "black" }

    function hasFix() {
        return root.positionSource
            && root.positionSource.valid
            && isFinite(root.positionSource.latitude)
            && isFinite(root.positionSource.longitude)
    }

    Column {
        anchors.centerIn: parent
        spacing: 8

        Text {
            color: "white"
            font.pixelSize: 20
            text: hasFix() ? "GPS: FIX" : "GPS: NO FIX (Fallback HTL)"
        }

        Text {
            color: "white"
            text: "sourceError: " + (root.positionSource ? root.positionSource.sourceError : "n/a")
        }

        Text {
            color: "white"
            text: {
                if (hasFix()) {
                    return "Lat: " + root.positionSource.latitude.toFixed(6)
                         + "\nLon: " + root.positionSource.longitude.toFixed(6)
                }
                return "Lat: " + root.fallbackLat.toFixed(6)
                     + "\nLon: " + root.fallbackLon.toFixed(6)
            }
        }
    }
}
