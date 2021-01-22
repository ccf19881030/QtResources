import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

Item {
    id: bottom
    width: 320
    height: 640
    //title
    Rectangle {
        id: rectangle0
        color: "#FFEC8B"
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        height: title.height * 2
        Image {
            id: rrr
            width: parent.height*3/4/2
            height: parent.height*3/4
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            source: "qrc:/icons/drawable-hdpi-v4/btn_top_more.png"
        }
        Text {
            id: title
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            text: qsTr("木格")
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
            source: "qrc:/icons/drawable-hdpi-v4/nav2.png"
        }

        Image {
            id: nav2Icon
            anchors.left: parent.horizontalCenter
            anchors.top: parent.top
            source: "qrc:/icons/drawable-hdpi-v4/nav1.png"
        }
    }

    //底部按键
    Rectangle {
        id: rectangle5
        color: "#FF1493"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.right: parent.right
        anchors.left: parent.left
        // anchors.top: rectangle4.bottom
        height: lockIcon.height + lockText.height
        Image {
            id: lockIcon
            width: 96
            height: 96
            anchors.left: parent.left
            anchors.leftMargin: parent.width / 6 - 96 / 2
            source: "qrc:/icons/drawable-hdpi-v4/btn_csl_open.png"
            MouseArea{
                anchors.fill: parent
                onClicked:
                {
                    if(lockIcon.source=="qrc:/icons/drawable-hdpi-v4/btn_csl_locked.png")
                    {
                        lockIcon.source="qrc:/icons/drawable-hdpi-v4/btn_csl_open.png"
                        console.log("unlock")
                    }
                    else
                    {
                        lockIcon.source="qrc:/icons/drawable-hdpi-v4/btn_csl_locked.png"
                        console.log("lock")
                    }
                }
            }
        }
        Image {
            id: modeIcon
            width: 96
            height: 96
            anchors.horizontalCenter: parent.horizontalCenter
            source: "qrc:/icons/drawable-hdpi-v4/btn_auto.png"
            MouseArea{
                anchors.fill: parent
                onClicked:
                {
                    if(modeIcon.source=="qrc:/icons/drawable-hdpi-v4/btn_auto.png")
                    {
                        modeIcon.source="qrc:/icons/drawable-hdpi-v4/btn_manual.png"
                        console.log("manual")
                    }
                    else
                    {
                        modeIcon.source="qrc:/icons/drawable-hdpi-v4/btn_auto.png"
                        console.log("auto")
                    }
                }
            }
        }
        Image {
            id: timeIcon
            width: 96
            height: 96
            anchors.right: parent.right
            anchors.rightMargin: parent.width / 6 - 96 / 2
            source: "qrc:/icons/drawable-hdpi-v4/btn_settime_blue.png"
        }

        Text {
            id: lockText
            anchors.top: lockIcon.bottom
            anchors.horizontalCenter: lockIcon.horizontalCenter
            text: qsTr("儿童锁")
            font.pointSize: 18
        }
        Text {
            id: modeText
            anchors.top: modeIcon.bottom
            anchors.horizontalCenter: modeIcon.horizontalCenter
            text: qsTr("智能")
            font.pointSize: 18
        }
        Text {
            id: timeText
            anchors.top: timeIcon.bottom
            anchors.horizontalCenter: timeIcon.horizontalCenter
            text: qsTr("定时")
            font.pointSize: 18
        }
    }
    //分割线
    Rectangle {
        id: splitLineBottom
        height: 5
        color: "#7fff00"
        anchors.bottom: rectangle5.top
        anchors.bottomMargin: 20
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.leftMargin: 0
    }
    RowLayout {
        id: rowLayout
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 30
        anchors.rightMargin: 30
        anchors.bottom: splitLineBottom.top
        anchors.bottomMargin: 20
        Text {
            id: standbyText
            text: qsTr("待机")
            font.pointSize: 14
        }

        Text {
            id: muteText
            text: qsTr("静音")
            font.pointSize: 14
        }

        Text {
            id: lowText
            text: qsTr("低速")
            font.pointSize: 14
        }

        Text {
            id: middleText
            text: qsTr("中速")
            font.pointSize: 14
        }

        Text {
            id: highText
            text: qsTr("高速")
            font.pointSize: 14
        }

        Text {
            id: ejectText
            text: qsTr("喷射")
            font.pointSize: 14
        }
    }
    //分割线
    Rectangle {
        id: splitLineTop
        height: 5
        color: "#7fff00"
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: rowLayout.top
        anchors.bottomMargin: 10
    }
    //设备管理
    Rectangle {
        id: rectangle6
        width: text3.width * 1.5
        height: text3.height * 1.5
        color: "#0000ee"
        radius: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: text4.top

        Text {
            id: text3
            color: "#ffffff"
            text: qsTr("绑定设备管理")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pointSize: 12
        }
    }

    Text {
        id: text4
        text: qsTr("室外PM2.5/")
        anchors.bottom: splitLineTop.top
        anchors.right: text5.left
        font.pointSize: 16
    }

    Text {
        id: text5
        text: qsTr("30")
        anchors.bottom: splitLineTop.top
        anchors.right: parent.right
        anchors.rightMargin: 10
        font.pointSize: 16
    }

    //中间气泡
    Rectangle {
        id: rectangle2
        color: "#FFEC8B"
        y: 165
        height: 371

        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: rectangle1.bottom
        anchors.bottom: rectangle6.top
        Image {
            id: image1
            width: parent.width * 3 / 5
            height: parent.width * 3 / 5
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/icons/drawable-xxhdpi-v4/apptheme_btn_default_pressed_holo_light.9.png"

            Text {
                id: text1
                text: qsTr("109")
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 40
            }

            Text {
                id: text2
                text: qsTr("PM2.5")
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 16
            }
        }

        Image {
            id: image2
            width: 32
            height: 32
            anchors.top: image1.top
            anchors.right: parent.right
            anchors.rightMargin: parent.width / 8
            source: "qrc:/icons/drawable-xxhdpi-v4/power_off.png"
        }
    }
}
