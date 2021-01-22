import QtQuick 2.4
import QtQuick.Window 2.0
import MusicInfo 1.0

Rectangle{
    id: titleRect;
    height: 50;
    width: 1024;
    color: "#C62F2F";
    property Window mainWindow: null;

    MouseArea { //为窗口添加鼠标事件
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton //只处理鼠标左键
        property point clickPos: "0,0"
        onPressed: { //接收鼠标按下事件
            clickPos  = Qt.point(mouse.x,mouse.y)
        }
        onPositionChanged: { //鼠标按下后改变位置
            if(mainWindow == null || mainWindow.visibility == Window.FullScreen)
                return;
            //鼠标偏移量
            var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)

            //如果mainwindow继承自QWidget,用setPos
            mainWindow.setX(mainWindow.x+delta.x)
            mainWindow.setY(mainWindow.y+delta.y)
        }
        onDoubleClicked: {
            if(mainWindow.visibility == Window.FullScreen)
                mainWindow.showNormal();
            else{
               mainWindow.visibility = Window.FullScreen;
            }
        }
    }

    //添加标题图片
    Image{
        id: titleImg
        cache: true;
        sourceSize.width: 120;
        sourceSize.height: 25;
        anchors.top: parent.top;
        anchors.topMargin: 16;
        anchors.left: parent.left;
        anchors.leftMargin: 15;
        source: "qrc:///images/title.png";
    }

    //添加搜索栏
    Row{
        anchors.left: titleImg.right;
        anchors.leftMargin: 65;
        anchors.verticalCenter: parent.verticalCenter;
        spacing: 15;

        Row{
            //前一个界面
            Rectangle{
                id: preBtn;
                width: 28;
                height:22;
                radius: 2;
                border.width: 1;
                border.color: "#A82828";
                color: "#C62F2F";
                Image{
                    anchors.centerIn: parent;
                    source: "qrc:///topwidget/btnReturn1.png";
                    opacity: preArea.containsMouse ? 1.0 : 0.5;
                }
                MouseArea{
                    id: preArea;
                    anchors.fill: parent;
                    hoverEnabled: true;
                }
            }

            //后一个界面
            Rectangle{
                id: nextBtn;
                width: 28;
                height:22;
                radius: 2;
                border.width: 1;
                border.color: "#A82828";
                color: "#C62F2F";
                Image{
                    anchors.centerIn: parent;
                    source: "qrc:///topwidget/btnReturn1.png";
                    rotation: 180;
                    opacity: nextArea.containsMouse ? 1.0 : 0.5;
                }
                MouseArea{
                    id: nextArea;
                    anchors.fill: parent;
                    hoverEnabled: true;
                }
            }
        }


        //搜索条
        Rectangle{
            width: 220;
            height: 22;
            border.width: 1;
            border.color: "#A82828";
            color: "#A82828";
            radius: 20;
            TextInput{
                id: searchText
                anchors.top: parent.top;
                anchors.topMargin: 5;
                anchors.left: parent.left;
                anchors.leftMargin: 10;
                width: parent.width - 35;
                clip: true;
                color: "white";
                property string preText: "";
                onEditingFinished:{
                    if(text == "" || preText == text)
                        return;
                    preText = text;
                    musicManager.keyword = searchText.text;
                    musicManager.startRequest = true;
                }
                cursorDelegate: Rectangle{
                    id: searchCursor
                    width: 1;
                    height: searchText.height;
                    border.width: 1
                    border.color: "white";
                    Timer{
                        id: shinInterval;
                        interval: 500;
                        running: true
                        repeat: true;
                        onTriggered: {
                            searchCursor.visible = !searchCursor.visible;
                        }
                    }
                }
                MouseArea{
                    anchors.fill: parent;
                    onClicked: searchText.focus = true;

                }
                MusicManager{
                    id: musicManager;
                    type: MusicManager.Search;
                    onFinished: {                        
                        if(musicCount <= 0){
                            musicList.currentViewId = -1;
                            errorText.text = "没有搜索到歌曲!"
                        }else{
                            musicList.currentViewId = 10;
                            detailView.refresh(musicManager);
                        }
                    }
                }
            }

            Image{
                anchors.verticalCenter: parent.verticalCenter;
                anchors.right: parent.right;
                anchors.rightMargin: 4;
                source: "qrc:///topwidget/btnSearch1.png";
                opacity: searchArea.containsMouse ? 1.0 : 0.5;

                MouseArea{
                    id: searchArea;
                    anchors.fill: parent;
                    hoverEnabled: true;
                    onClicked: {
                        musicManager.keyword = searchText.text;
                        musicManager.startRequest = true;
                    }
                }

            }
        }
    }


    //添加换肤等图标
    Row{
        spacing: 25;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.right: btnWindow.left;
        anchors.rightMargin: 20;

        //皮肤
        Image{
            id: btnSkin;
            anchors.verticalCenter: parent.verticalCenter;
            source: "qrc:///topwidget/btnSkin1.png";
            opacity: skinArea.containsMouse ? 1.0 : 0.5;
            MouseArea{
                id: skinArea;
                anchors.fill: parent;
                hoverEnabled: true;

            }
        }

        //信息
        Image{
            id: btnMessage;
            anchors.verticalCenter: parent.verticalCenter;
            source: "qrc:///topwidget/btnMessage1.png";
            opacity: messageArea.containsMouse ? 1.0 : 0.5;
            MouseArea{
                id: messageArea;
                anchors.fill: parent;
                hoverEnabled: true;

            }
        }

        //设置
        Image{
            id: btnSetting;
            anchors.verticalCenter: parent.verticalCenter;
            source: "qrc:///topwidget/btnSetting1.png";
            opacity: settingArea.containsMouse ? 1.0 : 0.5;
            MouseArea{
                id: settingArea;
                anchors.fill: parent;
                hoverEnabled: true;
            }
        }

        //分隔条
        Rectangle{
            width: 20;
            height: 25;
            color: "#C62F2F";
            Rectangle{
                anchors.horizontalCenter: parent.horizontalCenter;
                width: 1;
                height: parent.height;
                //border.width: 1;
                color: "#A82828";
            }
        }
    }

    //添加控制最大最小关闭按钮
    Row{
        id: btnWindow
        spacing: 12;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.right: parent.right;
        anchors.rightMargin: 20;

        //最小化
        Image{
            id: btnMini;
            anchors.verticalCenter: parent.verticalCenter;
            source: "qrc:///topwidget/btnMini1.png";
            opacity: miniArea.containsMouse ? 1.0 : 0.5;
            MouseArea{
                id: miniArea;
                anchors.fill: parent;
                hoverEnabled: true;
                onReleased: {
                    if(mainWindow == null)
                        return;
                    mainWindow.visibility = Window.Minimized;
                }
            }
        }

        //最大化
        Rectangle{
            width: 20;
            height: 20;
            color: "#C62F2F";
            Rectangle{
                id: btnMaximum;
                anchors.centerIn: parent;
                width: 15;
                height: 10;
                border.width: 1;
                border.color: maxiArea.containsMouse ? "#FFFFFF" : "#E29595";
                color: "#C62F2F";
                radius: 2;
            }
            MouseArea{
                id: maxiArea
                anchors.fill: parent;
                hoverEnabled: true;
                onReleased: {
                    if(mainWindow == null)
                        return;
                    if(mainWindow.visibility == Window.FullScreen)
                        mainWindow.showNormal();
                    else
                        mainWindow.visibility = Window.FullScreen;
                }
            }

        }

        //关闭
        Image{
            id: btnClose;
            anchors.verticalCenter: parent.verticalCenter;
            source: "qrc:///topwidget/btnClose1.png";
            opacity: closeArea.containsMouse ? 1.0 : 0.5;
            MouseArea{
                id: closeArea;
                anchors.fill: parent;
                hoverEnabled: true;
                onReleased: {
                    if(mainWindow == null)
                        return;
                    mainWindow.close();
                }
            }
        }
    }
}
