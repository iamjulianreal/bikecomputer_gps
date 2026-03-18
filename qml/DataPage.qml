import QtQuick 2.7

Item {
    id: root
    anchors.fill: parent

    property var positionSource
    property var hrMonitor
    property real totalDistanceM: 0
    property real totalAscentM: 0
    property bool hasLastPoint: false
    property real lastLat: 0
    property real lastLon: 0
    property real lastAlt: 0
    property string clockText: "--:--:--"
    property bool recording: false
    property var activityStartTime: undefined
    property string activityDurationText: "00:00"

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

    function updateActivityDuration() {
        if (!activityStartTime) {
            activityDurationText = "00:00"
            return
        }

        var elapsedMs = (new Date()).getTime() - activityStartTime.getTime()
        if (elapsedMs < 0)
            elapsedMs = 0

        var elapsedMinutes = Math.floor(elapsedMs / 60000)
        var hours = Math.floor(elapsedMinutes / 60)
        var minutes = elapsedMinutes % 60
        activityDurationText = (hours < 10 ? "0" : "") + hours
                + ":" + (minutes < 10 ? "0" : "") + minutes
    }

    function metricText(value, unit) {
        return value + "\n" + unit
    }

    function heartRateText() {
        return hrMonitor && hrMonitor.currentHeartRate > 0 ? hrMonitor.currentHeartRate : "--"
    }

    Component.onCompleted: updateClock()

    Timer {
        interval: 1000
        running: true
        repeat: true
        onTriggered: root.updateClock()
    }

    Timer {
        interval: 1000
        running: root.recording
        repeat: true
        onTriggered: root.updateActivityDuration()
    }

    Connections {
        target: positionSource
        enabled: !!positionSource

        function onPositionChanged() {
            if (!recording || !positionSource.valid) {
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

    onRecordingChanged: {
        if (recording) {
            totalDistanceM = 0
            totalAscentM = 0
            hasLastPoint = false
            lastLat = 0
            lastLon = 0
            lastAlt = 0
            activityStartTime = new Date()
            activityDurationText = "00:00"
        } else {
            updateActivityDuration()
        }
    }

    Rectangle { anchors.fill: parent; color: "#101010" }

    Column {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 8

        Row {
            width: parent.width
            spacing: 8

            Rectangle {
                width: (parent.width - parent.spacing) / 2
                height: 40
                radius: 6
                color: "#1E1E1E"
                Text {
                    anchors.centerIn: parent
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    text: root.metricText(positionSource && positionSource.valid ? positionSource.speedKmh.toFixed(1) : "-", "km/h")
                }
            }

            Rectangle {
                width: (parent.width - parent.spacing) / 2
                height: 40
                radius: 6
                color: "#1E1E1E"
                Text {
                    anchors.centerIn: parent
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    text: root.metricText((root.totalDistanceM / 1000.0).toFixed(2), "km")
                }
            }
        }

        Row {
            width: parent.width
            spacing: 8

            Rectangle {
                width: (parent.width - parent.spacing) / 2
                height: 40
                radius: 6
                color: "#1E1E1E"
                Text {
                    anchors.centerIn: parent
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    text: root.metricText(root.totalAscentM.toFixed(0), "m+")
                }
            }

            Rectangle {
                width: (parent.width - parent.spacing) / 2
                height: 40
                radius: 6
                color: "#1E1E1E"
                Text {
                    anchors.centerIn: parent
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    text: root.metricText(root.activityDurationText, "h:min")
                }
            }
        }

        Row {
            width: parent.width
            spacing: 8

            Rectangle {
                width: (parent.width - parent.spacing) / 2
                height: 40
                radius: 6
                color: "#1E1E1E"
                Text {
                    anchors.centerIn: parent
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    text: root.metricText(positionSource ? root.formatCoord(positionSource.latitude) : "-", "lat")
                }
            }

            Rectangle {
                width: (parent.width - parent.spacing) / 2
                height: 40
                radius: 6
                color: "#1E1E1E"
                Text {
                    anchors.centerIn: parent
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    text: root.metricText(positionSource ? root.formatCoord(positionSource.longitude) : "-", "lon")
                }
            }
        }

        Row {
            width: parent.width
            spacing: 8

            Rectangle {
                width: (parent.width - parent.spacing) / 2
                height: 40
                radius: 6
                color: "#1E1E1E"
                Text {
                    anchors.centerIn: parent
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    text: root.metricText(root.heartRateText(), "bpm")
                }
            }

            Rectangle {
                width: (parent.width - parent.spacing) / 2
                height: 40
                radius: 6
                color: "#1E1E1E"
                Text {
                    anchors.centerIn: parent
                    color: "white"
                    horizontalAlignment: Text.AlignHCenter
                    text: root.metricText(root.clockText, "clock")
                }
            }
        }
    }
}
