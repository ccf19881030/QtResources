import QtQuick 2.5
import QtQuick.Controls.Styles 1.4

Rectangle{
    id: rootItem;
    width: 200;
    height: 302;
    gradient: Gradient {
        GradientStop {
            position: 0.00;
            color: "#ffffff";
        }
        GradientStop {
            position: 1.00;
            color: "#d9d8d8";
        }
    }
    border.color: "darkgray";
    border.width: 1;

    function refresh(musicManager){
        musicModel.clear();
        if(musicManager != null){
            for(var i = 0; i < musicManager.musicCount; i++){
                musicModel.append({
                                      "songid": i + 1,
                                      "songname": musicManager.musicModelList[i].songname
                                  });
            }
        }
    }
    ListView{
        id: listView;
        x: 1;y: 1;
        width: parent.width - 2;
        height: parent.height - 2;
        clip: true;
        currentIndex: mediaPlayer.currentSongIndex;
        displayMarginBeginning: 4;
        displayMarginEnd: 4;
        //刷新模型数据
        model: ListModel{
            id: musicModel;
        }
        highlight:Rectangle{
            color: "lightblue"
        }
        header: Rectangle{
            height: 30;
            color: delegateRoot.ListView.isCurrentItem ? "#b9b9b9" :
                    (mouserArea.containsMouse ? "#e0e0e0" :
                    ( index % 2 == 0 ? "#F5F5F7" : "#FAFAFA"));
            border.width: 2;
            border.color: "black";
            Text{
                anchors.left: parent.left;
                anchors.leftMargin: 10;
                anchors.right: parent.right;
                anchors.rightMargin: 10;
                anchors.verticalCenter: parent.verticalCenter;
                height: parent.height;
                verticalAlignment: Text.AlignVCenter;
                font.bold: true;
                font.family: "Adobe Arabic";
                text: "  \t歌 曲 名";
            }
        }

        delegate: Rectangle{
            id: delegateRoot;
            height: 30;
            width: parent.width;
            color: delegateRoot.ListView.isCurrentItem ? "#b9b9b9" :
                   (mouserArea.containsMouse ? "#e0e0e0" :
                    ( index % 2 == 0 ? "#F5F5F7" : "#FAFAFA"));

            Text{
                anchors.left: parent.left;
                anchors.leftMargin: 10;
                anchors.right: parent.right;
                anchors.rightMargin: 10;
                anchors.verticalCenter: parent.verticalCenter;
                height: parent.height;
                verticalAlignment: Text.AlignVCenter;
                font.weight: Font.Medium
                font.pointSize: 10;
                text: songid + "\t" + songname;
            }
            MouseArea{
                id: mouserArea;
                anchors.fill: parent;
                hoverEnabled: true;
                onDoubleClicked: {
                    mediaPlayer.currentSongIndex = index;
                    mediaPlayer.playMusic(0);
                }
            }
        }

    }
}


