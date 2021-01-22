import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

Item {
    id: bottom
    width: 480
    height: 640

    Rectangle {
        id: rectangle0
        height: 31
        color: "#FFEC8B"
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top

        Text {
            id: title
            x: 206
            y: 110
            width: 53
            height: 37
            text: qsTr("木格")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            font.pointSize: 18
        }
    }





    Rectangle {
        id: rectangle1
        y: 172
        height: 22
        color: "#FFB6C1"
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: rectangle0.bottom

        Image {
            id: nav1Icon
            x: 45
            anchors.right: parent.horizontalCenter
            anchors.top: parent.top
            source: "icons/drawable-hdpi-v4/nav2.png"
        }

        Image {
            id: nav2Icon
            anchors.left: parent.horizontalCenter
            anchors.top: parent.top
            source: "icons/drawable-hdpi-v4/nav1.png"
        }
    }





    Rectangle {
        id: rectangle2
        y: 165
        height: 371
        gradient: Gradient {
            GradientStop {
                position: 0
                color: "#ffffff"
            }

            GradientStop {
                position: 0.973
                color: "#fff0e5"
            }

            GradientStop {
                position: 1
                color: "#000000"
            }

        }
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: rectangle1.bottom

        Image {
            id: image1
            x: 146
            y: 63
            width: 192
            height: 192
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            source: "icons/drawable-xxhdpi-v4/apptheme_btn_default_pressed_holo_light.9.png"

            Text {
                id: text1
                x: 72
                y: 108
                text: qsTr("109")
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 40
            }

            Text {
                id: text2
                x: 72
                y: 31
                text: qsTr("PM2.5")
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 16
            }
        }

        Image {
            id: image2
            x: 378
            y: 69
            width: 32
            height: 32
            source: "icons/drawable-xxhdpi-v4/power_off.png"
        }
    }





    Rectangle {
        id: rectangle3
        y: 225
        height: 46
        color: "#FF4040"
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: rectangle2.bottom

        Rectangle {
            id: rectangle6
            width: 115
            height: 33
            color: "#0000ee"
            radius: 10
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0

            Text {
                id: text3
                x: 28
                y: 13
                color: "#ffffff"
                text: qsTr("绑定设备管理")
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                font.pointSize: 12
            }
        }

        Text {
            id: text4
            x: 333
            y: 32
            text: qsTr("室外PM2.5/")
            anchors.bottom: parent.bottom
            font.pointSize: 16
        }

        Text {
            id: text5
            x: 447
            y: 31
            text: qsTr("30")
            anchors.bottomMargin: 0
            anchors.bottom: parent.bottom
            font.pointSize: 16
        }
    }






    Rectangle {
        id: rectangle4
        height: 30
        color: "#ffffff"
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: rectangle3.bottom

        Rectangle {
            id: splitLineTop
            height: 1
            color: "#7fff00"
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
        }
        RowLayout {
            Text {
                id: standbyText
                text: qsTr("待机")
                font.family: "Courier"
                font.pointSize: 12
            }


            Text {
                id: muteText
                text: qsTr("静音")
                font.pointSize: 12
            }


            Text {
                id: lowText
                text: qsTr("低速")
                font.pointSize: 12
            }


            Text {
                id: middleText
                text: qsTr("中速")
                font.pointSize: 12
            }

            Text {
                id: highText
                text: qsTr("高速")
                font.pointSize: 12
            }




            Text {
                id: ejectText
                text: qsTr("喷射")
                font.pointSize: 12
            }
        }

        Rectangle {
            id: splitLineBottom
            x: 1
            width: 481
            height: 1
            color: "#7fff00"
            anchors.bottomMargin: -44
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.left: parent.left
            anchors.leftMargin: 0
        }


    }




    Rectangle {
        id: rectangle5
        color: "#FF1493"
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: rectangle4.bottom
        Grid {
            id: grid1
            anchors.rightMargin: 0
            anchors.leftMargin: 0
            anchors.topMargin: 0
            anchors.bottomMargin: -89
            spacing: 0
            rows: 2
            columns: 3
            anchors.fill: parent
            Image {
                id: lockIcon
                width: 96
                height: 96
                source: "icons/drawable-hdpi-v4/btn_csl_open.png"
            }
            Image {
                id: modeIcon
                width: 96
                height: 96
                source: "icons/drawable-hdpi-v4/btn_auto.png"
            }
            Image {
                id: timeIcon
                width: 96
                height: 96
                source: "icons/drawable-hdpi-v4/btn_settime_blue.png"
            }

            Text {
                id: lockText
                text: qsTr("儿童锁")
                font.pointSize: 18
            }
            Text {
                id: modeText
                text: qsTr("智能")
                font.pointSize: 18
            }
            Text {
                id: timeText
                text: qsTr("定时")
                font.pointSize: 18
            }
        }



    }
}
