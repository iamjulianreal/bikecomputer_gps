import QtQuick 2.7
import QtQuick.Controls 2.7
import Bike.GPS 1.0

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

    property real fallbackLat: 48.207200
    property real fallbackLon: 15.618000

    GpsPositionSource {
        id: gps
        active: true
        onFixAvailable: function(latitude, longitude, speedKmh, courseDeg, isoTimestamp) {
            gpxLogger.addPoint(latitude, longitude, speedKmh, courseDeg, isoTimestamp)
        }
        onError: function(message) {
            console.log("GPS error:", message)
        }
    }

    MapPage {
        id: mapPage
        anchors.fill: parent
        visible: win.pageIndex === 0
        positionSource: gps
        fallbackLat: win.fallbackLat
        fallbackLon: win.fallbackLon
    }

    DataPage {
        id: dataPage
        anchors.fill: parent
        visible: win.pageIndex === 1
        positionSource: gps
    }

    ConnectivityPage {
        id: connPage
        anchors.fill: parent
        visible: win.pageIndex === 2
        positionSource: gps
        fallbackLat: win.fallbackLat
        fallbackLon: win.fallbackLon
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
                win.menuOpen = true
                console.log("MENU OPEN (long press)")
            }
        }
    }

    function nextPage() {
        win.pageIndex = (win.pageIndex + 1) % 3
    }

    function prevPage() {
        win.pageIndex = (win.pageIndex + 2) % 3
    }

    function toggleMapZoomMode() {
        if (win.pageIndex !== 0) return
        win.mode = (win.mode === "MAP_ZOOM") ? "NAV" : "MAP_ZOOM"
        mapPage.setZoomMode(win.mode === "MAP_ZOOM")
    }

    Connections {
        target: btnOk
        function onPressedChanged(down) {
            win.okDown = down

            if (down) {
                win.okLongFired = false
                okHoldTimer.start()
            } else {
                okHoldTimer.stop()

                if (win.okLongFired) return

                if (win.menuOpen) {
                    menu.select()
                    return
                }

                win.toggleMapZoomMode()
            }
        }
    }

    Connections {
        target: btnUp
        function onPressed() {
            if (win.menuOpen) { menu.up(); return }

            if (win.pageIndex === 0 && win.mode === "MAP_ZOOM") mapPage.zoomIn()
            else win.prevPage()
        }
    }

    Connections {
        target: btnDown
        function onPressed() {
            if (win.menuOpen) { menu.down(); return }

            if (win.pageIndex === 0 && win.mode === "MAP_ZOOM") mapPage.zoomOut()
            else win.nextPage()
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
