import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import MusicInfo 1.0
import "../mymusic/"

Item{
    id: rootItem;
//    function init(){
//        scrollView.visible = true;
//        detailView.visible = false;
//    }

    //歌曲细表
//    MyTableView{
//        id: detailView;
//        anchors.fill: parent;
//        z: 10;
//        visible: false;
//    }
    ScrollView{
        id: scrollView;
        anchors.fill: parent;

        //背景色
        Rectangle{
            anchors.fill: parent;
            color: "#FAFAFA";
        }
        Item{
            id: scrollWrapper;
            x: 40; y: 40;
            width: scrollView.width - 100;
            height: col.height + 100;
            Column{
                id: col;
                spacing: 10;
                anchors.horizontalCenter: parent.horizontalCenter;
                Item{
                    height: 60;
                    width: scrollWrapper.width + 20;
                    Text{
                        x: 0; y:0;
                        width: contentWidth;
                        height: contentHeight;
                        font.pixelSize: 18;
                        text: "QQ音乐排行榜"
                    }
                    Rectangle{
                        width: parent.width;
                        anchors.bottom: parent.verticalCenter;
                        height: 2;
                        border.color: "gray";
                    }
                }
                Row{
                    spacing: 10;
                    TopListView{
                        id: top1;
                        width: (scrollWrapper.width)/ 3 ;
                        startColor: "#1499B4";
                        endColor: "#44C5CD";
                        firstText: "欧";
                        restText: "美榜";
                        topX: 3;
                    }

                    TopListView{
                        id: top2;
                        startColor: "#1499B4";
                        endColor: "#44C5CD";
                        firstText: "内";
                        restText: "地榜";
                        width: (scrollWrapper.width )/ 3;
                        topX: 5;

                    }
                    TopListView{
                        id: top3;
                        startColor: "#D0466E";
                        endColor: "#EC5481";
                        firstText: "港";
                        restText: "台榜";
                        width: (scrollWrapper.width)/ 3;
                        topX: 6;

                    }
                }
                Row{
                    spacing: 10;
                    TopListView{
                        id: top4;
                        width: (scrollWrapper.width)/ 3;
                        startColor: "#C15746";
                        endColor: "#CE6D45";
                        firstText: "韩";
                        restText: "国榜";
                        topX: 16;
                    }
                    TopListView{
                        id: top5;
                        width: (scrollWrapper.width)/ 3;
                        startColor: "#C15746";
                        endColor: "#CE6D45";
                        firstText: "日";
                        restText: "本榜";
                        topX: 17;

                    }
                    TopListView{
                        id: top6;
                        width: (scrollWrapper.width)/ 3;
                        startColor: "#C15746";
                        endColor: "#CE6D45";
                        firstText: "民";
                        restText: "谣榜";
                        topX: 18;

                    }
                }
                Row{
                    spacing: 10;
                    TopListView{
                        id: top7;
                        width: (scrollWrapper.width)/ 3;
                        startColor: "#C15746";
                        endColor: "#CE6D45";
                        firstText: "摇";
                        restText: "摇榜";
                        topX: 19;
                    }
                    TopListView{
                        id: top8;
                        width: (scrollWrapper.width)/ 3;
                        startColor: "#C15746";
                        endColor: "#CE6D45";
                        firstText: "销";
                        restText: "量榜";
                        topX: 23;
                    }
                    TopListView{
                        id: top9;
                        width: (scrollWrapper.width)/ 3;
                        startColor: "#C15746";
                        endColor: "#CE6D45";
                        firstText: "热";
                        restText: "歌榜";
                        topX: 26;
                    }
                }

            }

        }
    }
}
