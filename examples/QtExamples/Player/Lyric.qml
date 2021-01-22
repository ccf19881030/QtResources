import QtQuick 2.0
import QtQuick.Controls 1.3
import Qt.labs.folderlistmodel 2.1


Rectangle {
    id: bgRec
    color: "#00cc99"
    width: parent.width
    height: parent.height
    property string lyricUrl: musicLyric.folder + "/Lyric/"
    property var lyricT: null
    property var lyricL: null
    property int time: 5
    property bool starts: false
    property int times: 0
    property real count: 0

    function iniFun(){
        time = 5;
        starts = false;
        times = 0;
        count = 0;
    }

    Timer {
        id: timer
        interval: 1000
        running: starts//音乐后退 不行，前进貌似也有点问题，会是歌词同步出现问题
        repeat: true
        onTriggered: {
            count += 100;
            //console.log(count + "*" +lyricT[times] )
            for(;;)
            {
                if(count >= lyricT[times])
                {
                    if(times < 2)
                    {

                    }else{
                        time +=1;
                    }
                    times++;
                }else{
                    break;
                }
           }
        }
    }

    Rectangle {
        id: titles
        width: parent.width
        height: parent.height / 12
        color: "#00cc99"
        z: 2
        Text {
            id: nameMusic
            width: parent.width / 5 * 4
            height: parent.height
            x : 0
            text: qsTr(music.musicName)
            font.pointSize: 12
            color: "#7c7c7c"
            clip: true
            elide: Text.Right
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            MouseArea {
                anchors.fill: parent
            }
        }
        Rectangle {
            id: quitBotton
            color: "#349172"
            width: parent.width / 5
            height: parent.height
            anchors.right: parent.right
            Text {
                text: "烦人"
                font.pointSize: 18
                anchors.centerIn: parent
                color: "lightblue"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                     Qt.quit();
                }
            }
        }
    }

    FolderListModel {
        id: musicLyric
        folder: music.listModel.parentFolder
    }

    Rectangle {
        id: a
        y: parent.height / 12
        width: parent.width
        height: parent.height / 12 * 11 / 5
        color: Qt.rgba(1,1,1,0.1)
        Text {
            id: aText
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: lyricL[time - 5]
            font.pointSize: 12
            font.family: "幼圆"
        }
    }
    Rectangle {
        id: b
        width: parent.width
        height: parent.height / 12 * 11 / 5
        anchors.top: a.bottom
        color: Qt.rgba(1,1,1,0.2)
        Text {
            id: bText
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: lyricL[time - 4]
            font.pointSize: 13
            font.family: "幼圆"
        }
    }
    Rectangle {
        id: c
        width: parent.width
        height: parent.height / 12 * 11 / 5
        anchors.top: b.bottom
        color: Qt.rgba(1,1,1,0.3)
        Text {
            id: cText
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: lyricL[time - 3]
            font.bold: times > 1 ? true : false
            font.pointSize: 14
            font.family: "幼圆"
        }
    }
    Rectangle {
        id: d
        width: parent.width
        height: parent.height / 12 * 11 / 5
        anchors.top: c.bottom
        color: Qt.rgba(1,1,1,0.4)
        Text {
            id: dText
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: lyricL[time - 2]
            font.pointSize: 13
            font.family: "幼圆"
        }
    }
    Rectangle {
        id:e
        width: parent.width
        height: parent.height / 12 * 11 / 5
        anchors.top: d.bottom
        color: Qt.rgba(1,1,1,0.5)
        Text {
            id: eText
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: lyricL[time - 1]
            font.pointSize: 12
            font.family: "幼圆"
        }
    }

    MouseArea {
        id: lyricPinch
        enabled: bgRec.visible ? true : false
        anchors.fill: parent
        z: 1

        property int clickPosX: 0
        property int clickPosY: 0
        property int judges: 0

        onReleased: {
            if(judges == 0)
            {
                lyricAnimationT.running = true
            }
            judges = 0
        }
        onPressed: {
            clickPosX = mouse.x
            clickPosY = mouse.y
        }

        onPositionChanged: {
            var a = mouse.x-clickPosX
            var b = mouse.y-clickPosY
            mainWindow.x = mainWindow.x+ a
            mainWindow.y = mainWindow.y+ b
            judges = 1
        }
    }
}


