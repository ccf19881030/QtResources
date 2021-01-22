import QtQuick 2.5
import QtQuick.Controls.Styles 1.4

Rectangle{
    id: rootItem;
    //property var model: musicModel;
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
            var cnt = musicManager.musicCount > 10 ? 10 : musicManager.musicCount;
            for(var i = 0; i < cnt; i++){
                musicModel.append({
                                      "songid": i + 1,
                                      "songname": musicManager.musicModelList[i].songname
                                  });
            }
        }
    }

    ListView{
        id: listView;
        x: 1;
        y: 1;
        width: parent.width - 2;
        height: parent.height - 2;
        headerPositioning:ListView.OverlayHeader;
        clip: true;
        currentIndex: -1;
        model: ListModel{
            id: musicModel;
        }
        highlight:Rectangle{
            color: "lightblue"
        }
        delegate: Rectangle{
            id: delegateRoot;
            height: 26;
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
            }
        }

    }
}
