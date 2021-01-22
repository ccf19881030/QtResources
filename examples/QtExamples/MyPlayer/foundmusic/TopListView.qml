import QtQuick 2.5
import QtQuick.Layouts 1.1
import MusicInfo 1.0

Rectangle{
    id: wrapper;
    width: 350;
    height: 345;
    color: "gray";
    property color startColor:"#3C8DDE";
    property color endColor: "#4C9EE6";
    property string firstText: "飚";
    property string restText: "升榜";
    property int topX: 5;

    MusicManager{
        id: musicManager;
        type: MusicManager.Top;
        topX: wrapper.topX;
        startRequest: true;
        onFinished: {
            bottomItem.refresh(musicManager);
        }
    }

    Rectangle{
        id: rootItem;
        x: 1; y: 1;
        width: parent.width - 2;
        height: parent.height - 2;
        Rectangle{
            id: topItem;
            x: 0; y: 0;
            width: rootItem.width;
            height: 80;
            gradient: Gradient{
                GradientStop{
                    position: 0.0;
                    color: wrapper.startColor;
                }
                GradientStop{
                    position: 1.0;
                    color:wrapper.endColor;
                }
            }
            Text{
                x: 20; y: parent.height / 2 - contentHeight / 2;
                width: contentWidth;
                height: contentHeight;
                font{
                    //family: "华文彩云"
                    pointSize: 50;
                    weight: Font.Bold;
                }
                color: "white";
                text: wrapper.firstText;
            }
            Text{
                x: 90; y: 20;
                height: contentHeight;
                width: contentWidth
                font{
                    //family: "华文彩云"
                    pointSize: 30;
                    weight: Font.ExtraBold;
                    italic: true;
                }
                color: "white";
                text: wrapper.restText;
            }
            MouseArea{
                anchors.fill: parent;
                onClicked:{
                    detailView.refresh(musicManager);
                    musicList.currentViewId = 10;

                }
            }
        }

        SmallListView{
            id: bottomItem;
            x: 0; y: topItem.height;
            width: rootItem.width;
            height: rootItem.height - topItem.height;
        }

    }
}



