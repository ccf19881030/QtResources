import QtQuick.Window 2.0
import QtQuick 2.6
import QtMultimedia 5.5
import "./mymusic/"
import "./foundmusic/"

Window {
    id: mainWindow
    width: 1020;
    height: 670;
    flags: Qt.Window | Qt.FramelessWindowHint;
    visible: true;
    color: "#666666";
    Rectangle{
        id: mainWRoot;
        x: 1; y: 1;
        width: parent.width - 2;
        height: parent.height - 2;


        TitleBar{
            id: titleBar;
            width: parent.width;
            height: 50;
            mainWindow: mainWindow;
        }                        
        LeftWidget{
            id: leftWidget;
            anchors.top: titleBar.bottom;
            anchors.left: parent.left;
            anchors.bottom: bottomBar.top;
            width: 200;
            onBtnClicked:musicList.currentViewId = btnId;
        }

        Item{
            id: musicList;
            anchors.top: titleBar.bottom;
            anchors.left: leftWidget.right;
            anchors.bottom: bottomBar.top;
            anchors.right: parent.right;
            property int currentViewId: 0;
            Text{
                id: errorText;
                anchors.fill: parent;
                horizontalAlignment: Text.AlignHCenter;
                verticalAlignment: Text.AlignVCenter;
                elide: Text.ElideRight;
                clip: true;
                font.pointSize: 16;
                color: "red";
                visible: parent.currentViewId == -1 ? true : false;
            }
            MyTableView{
                id: detailView;
                anchors.fill: parent;
                visible: parent.currentViewId == 10 ? true : false;
            }
            TopMusicView{
                id: topMusciView;
                anchors.fill: parent;
                visible:musicList.currentViewId == 0 ? true : false;
            }
            MyMusicList{
                id: myMusicList;
                anchors.fill: parent;
                visible: musicList.currentViewId == 4 ? true : false;


            }
        }



        MediaPlayer{
            id: mediaPlayer;
            property int currentSongIndex: 0;
            property string currentSongName;
            property string currrentSingerName;
            property string currentAlbumpicSmall;
            property var musicManager: null;
            property bool isAutoStop: true;
            onMusicManagerChanged: {
                currentList.refresh(musicManager);
            }

            onPaused: bottomBar.showPIcon = true;
            onPlaying: {
                bottomBar.showPIcon = false;
                isAutoStop = true;
            }
            onStopped:{
                bottomBar.showPIcon = true;
                if(isAutoStop){
                    switch(bottomBar.playWay)
                    {
                        //顺序播放
                    case 0:
                        if(currentSongIndex != mediaPlayer.musicManager.musicCount - 1)
                            playMusic(1);
                        break;
                        //循环播放
                    case 1:
                        playMusic(1);
                        break;
                        //随机播放
                    case 2:
                        var num = Math.round(Math.random() * mediaPlayer.musicManager.musicCount) ;
                        playMusic(num);
                        break;
                        //单曲循环播放
                    case 3:
                        playMusic(0);
                        break;
                    }
                }
            }
            //-1播放前一首，+1播放后一首, 0播放当前
            function playMusic(offset){
                if(mediaPlayer.musicManager.musicCount <= 0)
                    return;

                var i = (mediaPlayer.currentSongIndex +
                         offset +  mediaPlayer.musicManager.musicCount) %
                        mediaPlayer.musicManager.musicCount;
                mediaPlayer.isAutoStop = false;
                mediaPlayer.stop();
                mediaPlayer.currentSongIndex = i;
                mediaPlayer.source =  mediaPlayer.musicManager.musicModelList[i].url;
                mediaPlayer.currentAlbumpicSmall = mediaPlayer.musicManager.musicModelList[i].albumpicSmall;
                mediaPlayer.currentSongName = mediaPlayer.musicManager.musicModelList[i].songname;
                mediaPlayer.currrentSingerName = mediaPlayer.musicManager.musicModelList[i].singername;
                mediaPlayer.play();
            }
        }
        //底部
        BottomBar{
            id: bottomBar;
            anchors.left: parent.left;
            anchors.bottom: parent.bottom;
            width: parent.width;
        }

        MyListView{
            id: currentList;
            anchors.right: bottomBar.right;
            anchors.bottom: bottomBar.top;
            width: 300;
            height: 400;
            visible: false;
            z: 10;
        }
    }
}




