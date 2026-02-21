import QtQuick 2.7
import QtQuick.Controls 2.7

Rectangle {
    id: root
    anchors.fill: parent
    color: "#CC000000"

    signal closeRequested()
    signal startStopRequested()
    signal saveRequested()

    property int index: 0
    property bool recording: false

    Column {
        anchors.centerIn: parent
        spacing: 20

        Repeater {
            model: 3

            delegate: Rectangle {
                width: 220
                height: 50
                radius: 8

                color: index === model.index ? "#00AEEF" : "#222222"
                border.color: "white"

                Text {
                    anchors.centerIn: parent
                    text: model.index === 0 ? (root.recording ? "STOP RECORDING" : "START RECORDING")
                         : model.index === 1 ? "SAVE GPX"
                         : "CANCEL"
                    color: "white"
                    font.pixelSize: 18
                }
            }
        }
    }

    function up() {
        index = (index + 2) % 3
    }

    function down() {
        index = (index + 1) % 3
    }

    function select() {
        if (index === 0) {
            startStopRequested()
        }
        else if (index === 1) {
            saveRequested()
        }
        else {
            closeRequested()
        }
    }
}
