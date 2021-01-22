import QtQuick 2.0
import QtQuick.Controls 1.0

Rectangle {
    id: rectangle1
    width: 600
    height: 360

    Repeater {
        id: repeater
        model: 20

        property int currentItem

        Rectangle {
            id: rect1

            property int currentState: 1

            width: 250
            height: 250

            smooth: true

            anchors.centerIn: parent

            Text {
                color: "#ffffff"
                font.family: "Arial Black"
                font.pointSize: 60

                anchors.centerIn: parent

                text: index
            }

            Behavior on opacity {
                NumberAnimation { duration: 200 }
            }

            Behavior on z {
                NumberAnimation { duration: 300 }
            }

            transform: [
                Rotation {
                    id: rotate; angle: 0; origin.y: 125; origin.x: 125;  axis { x: 0; y: 1; z: 0 }
                    Behavior on angle {
                        NumberAnimation { easing.overshoot: 1; easing.type: Easing.OutBack; duration: 600 }
                    }
                },
                Translate {
                    id: trans; x: 0
                    Behavior on x {
                        NumberAnimation { easing.overshoot: 1; easing.type: Easing.OutBack; duration: 600;  }
                    }
                }
            ]

            states: [
                State {
                    name: "pos3"
                    PropertyChanges {
                        target: rotate
                        angle: 0
                    }
                    PropertyChanges {
                        target: trans
                        x: 0
                    }
                    PropertyChanges {
                        target: rect1
                        z: 1
                    }
                },

                State {
                    name: "pos2"
                    PropertyChanges {
                        target: rotate
                        angle: 50
                    }
                    PropertyChanges {
                        target: trans
                        x: -150
                    }
                    PropertyChanges {
                        target: rect1
                        z: 0
                    }
                },

                State {
                    name: "pos1"
                    PropertyChanges {
                        target: rotate
                        angle: 55
                    }
                    PropertyChanges {
                        target: trans
                        x: -180
                    }
                    PropertyChanges {
                        target: rect1
                        opacity: 0
                    }
                    PropertyChanges {
                        target: rect1
                        z: 0
                    }
                },

                State {
                    name: "pos5"
                    PropertyChanges {
                        target: rotate
                        angle: -55
                    }
                    PropertyChanges {
                        target: trans
                        x: 180
                    }
                    PropertyChanges {
                        target: rect1
                        opacity: 0
                    }
                    PropertyChanges {
                        target: rect1
                        z: 0
                    }
                },

                State {
                    name: "pos4"
                    PropertyChanges {
                        target: rotate
                        angle: -50
                    }
                    PropertyChanges {
                        target: trans
                        x: 150
                    }
                    PropertyChanges {
                        target: rect1
                        opacity: 1
                    }
                    PropertyChanges {
                        target: rect1
                        z: 0
                    }
                }
            ]

            color: "blue"
        }
    }

    Text {
        id: label
        font.family: "Arial"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top;
        anchors.topMargin: 10
    }

    Button {
        id: button1
        width: 100
        text: qsTr("Next")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: 60
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10

        onClicked: {
            repeater.currentItem += 1;

            if (repeater.currentItem > repeater.count - 1)
            {
                repeater.currentItem = 0;
            }

            for (var i = 0; i < repeater.count; i++)
            {
                var item = repeater.itemAt(i);

                item.currentState -= 1;

                if (item.currentState < 1)
                {
                    item.currentState = repeater.count;
                }

                if (item.currentState >= 1 && item.currentState <= 5)
                {
                    item.state = "pos" + item.currentState;
                }
            }

            label.text = "Current: " + repeater.currentItem;
        }
    }

    Button {
        id: button2
        width: 100
        text: qsTr("Prev")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: -60
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10

        onClicked: {
            repeater.currentItem -= 1;

            if (repeater.currentItem < 0)
            {
                repeater.currentItem = repeater.count - 1;
            }

            for (var i = 0; i < repeater.count; i++)
            {
                var item = repeater.itemAt(i);

                item.currentState += 1;

                if (item.currentState > repeater.count) {
                    item.currentState = 1;
                }

                if (item.currentState >= 1 && item.currentState <= 5)
                {
                    item.state = "pos" + item.currentState;
                }
            }

            label.text = "Current: " + repeater.currentItem;
        }
    }

    Component.onCompleted: {
        repeater.currentItem = 2;

        for (var i = 0; i < repeater.count; i++)
        {
            var item = repeater.itemAt(i);
            item.currentState = i + 1;

            item.color = Qt.rgba(Math.random(125), Math.random(125), Math.random(125), 255);

            if (item.currentState >= 1 && item.currentState <= 5)
            {
                item.state = "pos" + item.currentState;
            } else {
                item.state = "pos5";
            }
        }

        label.text = "Current: " + repeater.currentItem;
    }
}
