import QtQuick 2.6
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4
import QtMultimedia 5.0

TableView{
    id: rootView;
    width: 800;
    height: 600;
    headerDelegate: mMLHeader;
    rowDelegate: mMLRow;
    itemDelegate: mMLItem;
    verticalScrollBarPolicy: Qt.ScrollBarAsNeeded;
    horizontalScrollBarPolicy: Qt.ScrollBarAsNeeded;
    property var musicManager: null;
    property int playingRow: mediaPlayer.musicManager == rootView.musicManager ? mediaPlayer.currentSongIndex : -1;

    //将时间转化成00:00格式
    function  calTime(seconds){
        var m = Math.round(seconds % 60);
        var mins = "";
        if(m >= 0 && m < 10)
            mins = "0%1".arg(m);
        else
            mins = m;
        return "%1:%2".arg(Math.round(seconds / 60)).arg(mins);
    }

    //刷新模型数据
    function refresh(musicManager){
        rootView.musicManager = musicManager;
        musicModel.clear();
        if(musicManager != null){
            for(var i = 0; i < musicManager.musicCount; i++){
                musicModel.append({
                                         "id": i + 1,
                                         "songname": musicManager.musicModelList[i].songname,
                                         "seconds": rootView.calTime(musicManager.musicModelList[i].seconds),
                                         "singername": musicManager.musicModelList[i].singername,
                                     });
            }
        }
    }


    model: ListModel{
        id: musicModel;
    }

    style: TableViewStyle{
        scrollBarBackground: Rectangle{
            color: "#FAFAFA"
            //注意，height指定下方的scrollbar的高，
            //width指定右方的scroolbar的宽
            height: 8;
            width: 8;
        }
        handle:Button{
            id: button;
            property var hovered: styleData.hovered;
            style:ButtonStyle{
                background: Rectangle{
                    radius: 4;
                    color: button.hovered ? "#CFCFD1" : "#E1E2E2";
                }
            }
        }
        incrementControl: Item{}
        decrementControl: Item{}
    }

    TableViewColumn{
        role: "id"; title: ""; width: 50;
        horizontalAlignment: Text.AlignRight;
    }
    TableViewColumn{
        role: "songname"; title: "音乐标题"; width: 230;
    }

    TableViewColumn{
        role: "singername"; title: "歌手"; width: 150;
    }
    TableViewColumn{
        role: "seconds"; title: "时长"; width: 150;
    }

    Component{
        id: mMLHeader;
        Rectangle{
            color: "#ECEDEE";
            height: 30;
            Rectangle{
                width: parent.width - 2;
                height: parent.height - 2;
                anchors.centerIn: parent;
                property var pressedG: Gradient{
                    GradientStop{ position: 0.0; color: "#ECEDEE" }
                    GradientStop{ position: 1.0; color: "#FAFAFA" }
                }
                property var hoverG: Gradient{
                    GradientStop{ position: 0.0; color: "#FAFAFA" }
                    GradientStop{ position: 1.0; color: "#ECEDEE" }
                }
                property var normalG: Gradient{
                    GradientStop{ position: 0.0; color: "#FAFAFA" }
                    GradientStop{ position: 1.0; color: "#FAFAFA" }
                }

                gradient: styleData.pressed ? pressedG :
                                              (styleData.containsMouse ? hoverG : normalG);

                Text{
                    anchors.left: parent.left;
                    anchors.leftMargin: 10;
                    anchors.verticalCenter: parent.verticalCenter;
                    text: styleData.value;
                    color: "#666666";
                }
            }
        }
    }
    Component{
        id: mMLRow;
        Rectangle{
            height: 30;
            color: styleData.selected ? "#ECEDEE" :
                                        (styleData.alternate ? "#F5F5F7" : "#FAFAFA");
        }
    }
    Component{
        id: mMLItem;
        Item{
            Text{
                width: parent.width - 10;
                height: parent.height;
                anchors.left: parent.left;
                anchors.leftMargin: 10;
                anchors.verticalCenter: parent.verticalCenter;
                color: "black";
                text: img.visible ? "" :styleData.value;
                verticalAlignment: Text.AlignVCenter;
                elide: Text.ElideRight;
                clip: true;

                Image{
                    id: img;
                    anchors.verticalCenter: parent.verticalCenter;
                    anchors.left: parent.left;
                    source: "qrc:///middlewidget/megaphone.png";
                    visible: ((rootView.playingRow == styleData.row )&& (styleData.column == 0)) ?
                            true : false;
                }
            }
        }
    }
    onDoubleClicked: {
        mediaPlayer.musicManager = rootView.musicManager;
        mediaPlayer.currentSongIndex = row;
        mediaPlayer.playMusic(0);
    }
}




