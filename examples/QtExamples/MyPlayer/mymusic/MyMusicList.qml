import QtQuick 2.6
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import MusicInfo 1.0
import "../"

Item {
    id: rootItem;
    width: 800;
    height: 570;

    MusicManager{
        id: musicManager;        
        onFinished: {
            myMList.refresh(musicManager);
        }
    }


    //标题部分
    Rectangle{
        id: myMTitle;
        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.right: parent.right;
        height: 50;
        color: "#FAFAFA";
        //左部
        Text{
            id: mMTText;
            anchors.left: parent.left;
            anchors.leftMargin: 20;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 8;
            text: "本地音乐";
            font.pixelSize: 22;
            color: "#333333";
        }
        Row{
            anchors.left: mMTText.right;
            anchors.leftMargin: 12;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 8;
            spacing: 4;
            Text{
                text: musicManager.musicCount + "首音乐，";
                color: "#333333";
            }
            
            Text{
                text:  "选择目录";
                color: mouseArea1.containsMouse ? "darkBlue" : "blue";
                MouseArea{
                    id: mouseArea1;
                    anchors.fill: parent;
                    hoverEnabled: true;
                    onClicked: {
                        fileDialog.open();
                    }
                }
                FileDialog{
                    id: fileDialog;
                    selectFolder: true;
                    title: "请选择文件";
                    onAccepted:{
                        musicManager.localPath = fileUrl;
                    }
                }

            }
        }

        //上部边框
        Rectangle{
            width: parent.width;
            height: 1;
            anchors.top: parent.top;
            color: "#E1E1E2";
        }

        //下部边框
        Rectangle{
            width: parent.width;
            height: 1;
            anchors.bottom: parent.bottom;
            color: "#E1E1E2";
        }
    }
    //播放、搜索
    Rectangle{
        id: myMSearch;
        anchors.top: myMTitle.bottom;
        anchors.left: parent.left;
        anchors.right: parent.right;
        height: 50;
        color: "#FAFAFA";

        //全部播放按钮
        Rectangle{
            id: mMSBtn1;
            width: 94;
            height: 26
            radius: 4;
            color: "#E1E1E2";
            anchors.left: parent.left;
            anchors.leftMargin: 30;
            anchors.verticalCenter: parent.verticalCenter;
            MyButton{
                width: 92;
                height: 24;
                spacing: 4;
                leftSpace: 4;
                radius: 4;
                anchors.centerIn: parent;
                myText: "全部播放";
                source: "";
                onBtnClicked: {

                }
            }
        }

        //+按钮
        Rectangle{
            id: mMSBtn2;
            width: 34;
            height: 26
            color: "#E1E1E2";
            radius: 4;
            anchors.left: mMSBtn1.right;
            anchors.verticalCenter: parent.verticalCenter;
            MyButton{
                width: 32;
                height: 24;
                spacing: 4;
                leftSpace: 4;
                radius: 4;
                anchors.centerIn: parent;
                source: "";
            }
        }

        //匹配音乐按钮
        Rectangle{
            id: mMSBtn3;
            width: 94;
            height: 26
            color: "#E1E1E2";
            radius: 4;
            anchors.left: mMSBtn2.right;
            anchors.leftMargin: 16;
            anchors.verticalCenter: parent.verticalCenter;
            MyButton{
                width: 92;
                height: 24;
                spacing: 4;
                leftSpace: 4;
                radius: 4;
                anchors.centerIn: parent;
                myText: "匹配音乐";
                source: "";
            }
        }
    }
    //歌曲列表
    MyTableView{
        id: myMList;
        anchors.top: myMSearch.bottom;
        anchors.left: parent.left;
        anchors.bottom: parent.bottom;
        width: parent.width;
        //playingRow: mediaPlayer.musicManager == musicManager ? mediaPlayer.currentSongIndex : -1;
//        onDoubleClicked: {
//            mediaPlayer.musicManager = musicManager;
//            mediaPlayer.currentSongIndex = row;
//            mediaPlayer.playMusic(0);
//        }
    }
}
