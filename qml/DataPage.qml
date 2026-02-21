import QtQuick 2.7

Item {
    id: root
    anchors.fill: parent

    property var positionSource

    Rectangle { anchors.fill: parent; color: "#101010" }

    Column {
        anchors.centerIn: parent
        spacing: 10

        Text {
            color: "white"
            font.pixelSize: 20
            text: positionSource && positionSource.valid ? "GPS FIX" : "GPS NO FIX"
        }

        Text {
            color: "white"
            text: "Recording: " + (gpxLogger.recording ? "ON" : "OFF")
        }

        Text {
            color: "white"
            text: "Track points: " + gpxLogger.pointCount
        }

        Text {
            color: "white"
            text: "Last GPX:\n" + (gpxLogger.lastSavedPath.length > 0 ? gpxLogger.lastSavedPath : "-")
        }
    }
}
