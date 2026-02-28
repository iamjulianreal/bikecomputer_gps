import QtQuick 2.7
import QtQuick.Controls 2.7

Item {
    id: root
    anchors.fill: parent

    property var positionSource
    property real fallbackLat: 48.207200
    property real fallbackLon: 15.618000

    Rectangle { anchors.fill: parent; color: "#0f1116" }

    function hasFix() {
        return root.positionSource
            && root.positionSource.valid
            && isFinite(root.positionSource.latitude)
            && isFinite(root.positionSource.longitude)
    }

    Column {
        anchors.fill: parent
        anchors.margins: 14
        spacing: 10

        Rectangle {
            width: parent.width
            height: 52
            radius: 8
            color: "#1c2230"
            border.color: hasFix() ? "#2ecc71" : "#e74c3c"

            Text {
                anchors.centerIn: parent
                color: "white"
                font.pixelSize: 22
                font.bold: true
                text: hasFix() ? "GPS FIX" : "KEIN GPS FIX"
            }
        }

        Rectangle {
            width: parent.width
            height: 62
            radius: 8
            color: "#1c2230"
            border.color: "#2b3344"
            Text {
                anchors.centerIn: parent
                color: "#cfd6e6"
                font.pixelSize: 16
                horizontalAlignment: Text.AlignHCenter
                text: (batteryMonitor.available
                      ? ("AKKU: " + batteryMonitor.percent + " %")
                      : "AKKU: -- %")
                      + "\nLICHT: " + backlightController.brightness + " %"
            }
        }

    }
}
