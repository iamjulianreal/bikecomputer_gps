import QtQuick 2.7

Item {
    id: root
    anchors.fill: parent

    property var positionSource
    property real totalDistanceM: 0
    property real totalAscentM: 0
    property bool hasLastPoint: false
    property real lastLat: 0
    property real lastLon: 0
    property real lastAlt: 0
    property string clockText: "--:--:--"

    function formatCoord(v) {
        return isFinite(v) ? v.toFixed(6) : "-"
    }

    function toRad(deg) {
        return deg * Math.PI / 180.0
    }

    function distanceMeters(lat1, lon1, lat2, lon2) {
        var earthRadius = 6371000.0
        var dLat = toRad(lat2 - lat1)
        var dLon = toRad(lon2 - lon1)
        var a = Math.sin(dLat / 2) * Math.sin(dLat / 2) +
                Math.cos(toRad(lat1)) * Math.cos(toRad(lat2)) *
                Math.sin(dLon / 2) * Math.sin(dLon / 2)
        var c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a))
        return earthRadius * c
    }

    function updateClock() {
        clockText = Qt.formatTime(new Date(), "hh:mm:ss")
    }

    Component.onCompleted: updateClock()

    Timer {
        interval: 1000
        running: true
        repeat: true
        onTriggered: root.updateClock()
    }

    Connections {
        target: positionSource
        enabled: !!positionSource

        function onPositionChanged() {
            if (!positionSource.valid) {
                return
            }

            var currentLat = positionSource.latitude
            var currentLon = positionSource.longitude
            var currentAlt = positionSource.altitudeMeters

            if (root.hasLastPoint) {
                root.totalDistanceM += root.distanceMeters(root.lastLat, root.lastLon, currentLat, currentLon)

                if (isFinite(currentAlt) && isFinite(root.lastAlt)) {
                    var deltaAlt = currentAlt - root.lastAlt
                    if (deltaAlt > 0) {
                        root.totalAscentM += deltaAlt
                    }
                }
            }

            root.lastLat = currentLat
            root.lastLon = currentLon
            root.lastAlt = currentAlt
            root.hasLastPoint = true
        }
    }

    Rectangle { anchors.fill: parent; color: "#101010" }

    Grid {
        anchors.centerIn: parent
        columns: 2
        spacing: 10

        Text {
            color: "white"
            font.pixelSize: 20
            text: "Speed"
        }

        Text {
            color: "white"
            font.pixelSize: 20
            text: positionSource && positionSource.valid ? positionSource.speedKmh.toFixed(1) + " km/h" : "-"
        }

        Text {
            color: "white"
            text: "Anstieg"
        }

        Text {
            color: "white"
            text: root.totalAscentM.toFixed(0) + " m"
        }

        Text {
            color: "white"
            text: "Distanz"
        }

        Text {
            color: "white"
            text: (root.totalDistanceM / 1000.0).toFixed(2) + " km"
        }

        Text {
            color: "white"
            text: "Uhrzeit"
        }

        Text {
            color: "white"
            text: root.clockText
        }

        Text {
            color: "white"
            text: "Lat"
        }

        Text {
            color: "white"
            text: positionSource ? root.formatCoord(positionSource.latitude) : "-"
        }

        Text {
            color: "white"
            text: "Lon"
        }

        Text {
            color: "white"
            text: positionSource ? root.formatCoord(positionSource.longitude) : "-"
        }
    }
}
