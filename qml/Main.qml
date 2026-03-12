import QtQuick 2.7
import QtQuick.Controls 2.7

ApplicationWindow {
    id: win
    visible: true
    width: 320
    height: 240
    title: "BikeComputer"

    property int pageIndex: 0
    property string mode: "NAV"
    property bool menuOpen: false
    property bool okDown: false
    property bool okLongFired: false
    property bool connectivityBrightnessMode: false

    property real fallbackLat: 48.207200
    property real fallbackLon: 15.618000

    Connections {
        target: gpsSource
        function onFixAvailable(latitude, longitude, speedKmh, courseDeg, isoTimestamp) {
            gpxLogger.addPoint(latitude, longitude, speedKmh, courseDeg, isoTimestamp)
        }
        function onError(message) {
            console.log("GPS error:", message)
        }
    }

    MapPage {
        id: mapPage
        anchors.fill: parent
        visible: win.pageIndex === 0
        positionSource: gpsSource
    }

    DataPage {
        id: dataPage
        anchors.fill: parent
        visible: win.pageIndex === 1
        positionSource: gpsSource
        recording: gpxLogger.recording
    }

    ConnectivityPage {
        id: connPage
        anchors.fill: parent
        visible: win.pageIndex === 2
        positionSource: gpsSource
    }

    StartStopMenu {
        id: menu
        anchors.fill: parent
        visible: win.menuOpen
        recording: gpxLogger.recording

        onCloseRequested: win.menuOpen = false
        onStartStopRequested: {
            if (gpxLogger.recording) {
                gpxLogger.stop()
            } else {
                gpxLogger.start()
            }
            win.menuOpen = false
        }
        onSaveRequested: {
            var path = gpxLogger.save()
            console.log("GPX saved:", path)
            win.menuOpen = false
        }
    }

    Timer {
        id: okHoldTimer
        interval: 650
        repeat: false
        onTriggered: {
            if (win.okDown && !win.menuOpen) {
                win.okLongFired = true
                menu.index = 0
                win.menuOpen = true
                console.log("MENU OPEN (long press)")
            }
        }
    }

    function nextPage() {
        win.pageIndex = (win.pageIndex + 1) % 3
        if (win.pageIndex !== 2) win.connectivityBrightnessMode = false
    }

    function prevPage() {
        win.pageIndex = (win.pageIndex + 2) % 3
        if (win.pageIndex !== 2) win.connectivityBrightnessMode = false
    }

    function toggleMapZoomMode() {
        if (win.pageIndex !== 0) return
        win.mode = (win.mode === "MAP_ZOOM") ? "NAV" : "MAP_ZOOM"
        mapPage.setZoomMode(win.mode === "MAP_ZOOM")
    }

    function toggleConnectivityBrightnessMode() {
        if (win.pageIndex !== 2) return
        win.connectivityBrightnessMode = !win.connectivityBrightnessMode
    }

    Connections {
        target: btnOk
        function onPressedChanged(down) {
            win.okDown = down

            if (down) {
                win.okLongFired = false
                if (!win.menuOpen) {
                    okHoldTimer.start()
                }
            } else {
                okHoldTimer.stop()

                if (win.okLongFired) return

                if (win.menuOpen) {
                    menu.select()
                    return
                }

                if (win.pageIndex === 0) {
                    win.toggleMapZoomMode()
                } else if (win.pageIndex === 2) {
                    win.toggleConnectivityBrightnessMode()
                }
            }
        }
    }

    Connections {
        target: btnUp
        function onPressed() {
            if (win.menuOpen) { menu.up(); return }

            if (win.pageIndex === 0 && win.mode === "MAP_ZOOM") {
                mapPage.zoomIn()
            } else if (win.pageIndex === 2 && win.connectivityBrightnessMode) {
                backlightController.increase()
            } else {
                win.prevPage()
            }
        }
    }

    Connections {
        target: btnDown
        function onPressed() {
            if (win.menuOpen) { menu.down(); return }

            if (win.pageIndex === 0 && win.mode === "MAP_ZOOM") {
                mapPage.zoomOut()
            } else if (win.pageIndex === 2 && win.connectivityBrightnessMode) {
                backlightController.decrease()
            } else {
                win.nextPage()
            }
        }
    }

    Rectangle {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 6
        radius: 6
        color: "#66000000"
        width: 156
        height: 40

        Text {
            anchors.centerIn: parent
            color: "white"
            font.pixelSize: 12
            horizontalAlignment: Text.AlignHCenter
            text: win.menuOpen
                  ? "MENU"
                  : (win.pageIndex === 0 && win.mode === "MAP_ZOOM" ? "MAP ZOOM" : "PAGES")
                    + "\nREC " + (gpxLogger.recording ? "ON" : "OFF")
        }
    }
}
