import QtQuick 2.0
import QtQuick.Dialogs 1.2
import Qt.labs.folderlistmodel 2.1

Item {
    id: musicItem
    width: parent.width
    height: parent.height
    property string musicUrl: ""
    property string musicName: ""
    property int exchange: 0
    property FolderListModel listModel: folderModel
    property int musicIndex: 0

    Component {
        id: delegates
        Item {
            id: urlText
            width: musicList.width
            height: musicList.height / 7
            Text {
                text: fileName
                anchors.centerIn: parent
                font.pointSize: 11
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    musicUrl = folderModel.folder
                    musicName = fileName
                    exchange = 1;
                    musicIndex = index;
                }
            }
        }
    }

    Rectangle {
        id: musicRectangle
        anchors.fill: parent
        color: "#add9ff"
        antialiasing: true
        ListView {
            id: musicList
            x: 0
            y: 0
            width: parent.width
            height: parent.height / 12 * 11
            clip: true
            visible: false
            focus: true
            delegate: delegates
            model: folderModel
            snapMode: ListView.SnapToItem
            }
        }

    FileDialog {
        id: dialog
        selectFolder: true
        title: "Choose Music for me !"
        onAccepted: {
            folderModel.folder = fileUrl + "/"
            musicList.visible = true
        }
    }

    FolderListModel {
        id: folderModel
        showFiles: true
        nameFilters: ["*.mp3"]
        }

    Row {
        id: theSetsRow
        anchors.bottom: musicRectangle.bottom
        anchors.left: musicItem.left
        width: musicItem.width
        height: musicItem.width / 12

        Rectangle {
            color: "#add9ff"
            width: parent.width / 3
            height: parent.height

            MouseArea {
                 anchors.fill: parent
                 onClicked: {
                     dialog.open();
                 }
             }

            Canvas {
                anchors.fill: parent
                onPaint: {
                    var ctx = getContext("2d");
                    ctx.lineWidth = 1;
                    ctx.strokeStyle = "cyan";
                    ctx.fillStyle = "cyan";
                    ctx.beginPath();
                    ctx.ellipse(parent.width / 2 - parent.height / 2 + 1,1,parent.height - 2,parent.height - 2);
                    ctx.closePath();
                    ctx.fill();
                    ctx.stroke();
            }
          }
        }
        Rectangle {
            color: "#add9ff"
            width: parent.width / 3
            height: parent.height
            Canvas {
                id: musicFile
                anchors.fill: parent
                onPaint: {
                    var ctx = getContext("2d");
                    ctx.lineWidth = 1;
                    ctx.strokeStyle = "#1fcc8d";
                    ctx.fillStyle = "#1fcc8d";
                    ctx.beginPath();
                    ctx.ellipse(parent.width / 2 - parent.height / 2 + 1,1,parent.height - 2,parent.height - 2);
                    ctx.closePath();
                    ctx.fill();
                    ctx.stroke();
            }
          }
            MouseArea {
                 anchors.fill: parent
                 onClicked: {
                     dialog.open();
                 }
             }
        }
        Rectangle {
            width: parent.width / 3
            height: parent.height
            color: "#add9ff"


            MouseArea {
                 anchors.fill: parent
                 onClicked: {
                     dialog.open();
                 }
             }

            Canvas {
                anchors.fill: parent
                onPaint: {
                    var ctx = getContext("2d");
                    ctx.lineWidth = 1;
                    ctx.strokeStyle = "green";
                    ctx.fillStyle = "green";
                    ctx.beginPath();
                    ctx.ellipse(parent.width / 2 - parent.height / 2 + 1,1,parent.height - 2,parent.height - 2);
                    ctx.closePath();
                    ctx.fill();
                    ctx.stroke();
            }
          }
        }
    }
}
