import QtQuick 2.4
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle{
    id: lWRoot;
    width: 200;
    height: 570;
    color: "#F5F5F7";
    signal btnPressed(var btnType);

    //右边分割线
    Rectangle{
        id: lWRightSeparator;
        width: 1;
        height: parent.height;
        color:  "#E1E1E2";
        anchors.top: parent.top;
        anchors.right: parent.right;
    }

    //主列表
    Column{
        id: mainList;
        width: parent.width - lWRightSeparator.width;
        height: parent.height;
        anchors.top: parent.top;
        anchors.left: parent.left;
        spacing: 20;

        //推荐列表
        Column{
            width: parent.width;
            //推荐
            Text{
                id: recommendPart;
                width: parent.width;
                height: 34;
                text: "  推荐";
                color: "#5C5C5C";
                verticalAlignment: Text.AlignVCenter;
            }

            MyButton{
                id: fdMusicPart;
                width: parent.width;
                height: 34;
                source: "qrc:///middlewidget/btnmusic2.png";
                myText: "发现音乐";
                onBtnClicked: lWRoot.btnPressed(0);
            }
            MyButton{
                id: fmPart;
                width: parent.width;
                height: 34;
                source: "qrc:///middlewidget/btnradio2.png";
                myText: "私人FM";
               onBtnClicked: lWRoot.btnPressed(1);
            }
            MyButton{
                id: mvPart;
                width: parent.width;
                height: 34;
                source: "qrc:///images/btnmv.png";
                myText: "MV";
               onBtnClicked: lWRoot.btnPressed(2);
            }
            MyButton{
                id: friendsPart;
                width: parent.width;
                height: 34;
                source: "qrc:///images/btnfriends.png";
                myText: "朋友";
                onBtnClicked: lWRoot.btnPressed(3);
            }
        }

        // 我的音乐
        Column{
            width: parent.width;
            //推荐
            Text{
                id: myMusicPart;
                width: parent.width;
                height: 34;
                text: "  我的音乐";
                color: "#5C5C5C";
                verticalAlignment: Text.AlignVCenter;
            }

            MyButton{
                id: localMusicPart;
                width: parent.width;
                height: 34;
                source: "qrc:///images/btnmusic.png";
                myText: "本地音乐";
                onBtnClicked: lWRoot.btnPressed(4);
            }

            MyButton{
                id: downloadedPart;
                width: parent.width;
                height: 34;
                source: "qrc:///images/btndownload.png";
                myText: "下载管理";
                onBtnClicked: lWRoot.btnPressed(5);
            }

        }

        //创建歌单
        Column{
            width: parent.width;
            //推荐
            Item{
                width: parent.width;
                height: 34;
                Text{
                    id: createdListPart;
                    text: "  创建的歌单";
                    color:"#5c5c5c"
                    anchors.left: parent.left;
                    anchors.verticalCenter: parent.verticalCenter;
                }
                Row{
                    height: parent.height;
                    anchors.right: parent.right;
                    anchors.rightMargin: 10;
                    spacing: 10;

                    //新建歌单按钮
                    Image{
                        width: 20;
                        height: 20;
                        source: "qrc:///middlewidget/btncross1.png";
                        opacity: mouseArea1.containsMouse ? 1.0 : 0.8;
                        MouseArea{
                            id: mouseArea1;
                            anchors.fill: parent;
                            hoverEnabled: true;
                        }
                    }

                    //打开列表按钮
                    Image{
                        id: addList;
                        width: 20;
                        height: 20;
                        source: "qrc:///middlewidget/indicatortop1.png";
                        opacity: mouseArea2.containsMouse ? 1.0 : 0.8;
                        MouseArea{
                            id: mouseArea2;
                            anchors.fill: parent;
                            hoverEnabled: true;
                            onClicked: {
                                favoritePart.visible = !favoritePart.visible;
                                if(favoritePart.visible){
                                    addList.rotation = 90;
                                }else{
                                    addList.rotation = 0;
                                }
                            }
                        }
                    }
                }
            }

            MyButton{
                id: favoritePart;
                width: parent.width;
                height: 34;
                visible: false;
                source: "qrc:///middlewidget/btnfavorite.png";
                myText: "我喜欢的音乐";
            }

        }
    }

 }
