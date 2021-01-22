import QtQuick 2.6
import QtMultimedia 5.5

import "myJs.js" as Js
import an.qt.MusicList 1.0
import "./componets"


Item {
    id: mainWRoot;
    width: 1024;
    height: 620;

    function loadContent(type){
        switch(type)
        {
        case 4:
            listWidget.visible = true;
            break;
        default:
            listWidget.visible = false;
            break;
        }
    }

    LeftWidget{
        id: leftWidget;
        anchors.top: parent.top;
        anchors.left: parent.left;
        anchors.bottom: bottomBar.top;
        width: 200;
        MusicInfo{
            id: musicInfo;
            anchors{
                bottom: parent.bottom;
                left: parent.left;
            }
            width: parent.width;
            height: 80;
        }
        onBtnPressed: mainWRoot.loadContent(btnType);
    }

    MyMusicList{
        id: listWidget;
        anchors.top: parent.top;
        anchors.left: leftWidget.right;
        anchors.bottom: bottomBar.top;
        anchors.right: parent.right;
        visible: false;
        playingRow: musiclist.currentRow;

        MusicList{
            id: musiclist;
            //正在播放的歌曲行号
            property int currentRow: -1;

            onCurrentRowChanged: {
                musicInfo.name = listWidget.tableModel.get(musiclist.currentRow).mName;
                musicInfo.singer = listWidget.tableModel.get(musiclist.currentRow).mSinger;

                listWidget.tableView.selection.clear();
                listWidget.tableView.selection.select(currentRow);
            }

            Component.onCompleted: {
                Js.initMusicList(musiclist);
            }
        }

        MediaPlayer{
            id: mediaPlayer;
            onPlaybackStateChanged: {
                if(playbackState == 0){
                    bottomBar.showPIcon = true;
                    if(duration == position)
                        Js.playMusic(musiclist.currentRow + 1);
                }else if(playbackState == 1){
                    bottomBar.showPIcon = false;
                }else if(playbackState == 2 ){
                    bottomBar.showPIcon = true;
                }
            }

            Component.onCompleted: {
                Js.initPlayer(mediaPlayer);
            }
        }
    }

    //底部
    BottomBar{
        id: bottomBar
        anchors.left: parent.left;
        anchors.bottom: parent.bottom;
        width: parent.width;

        value: (mediaPlayer.position * 1.0 / mediaPlayer.duration) * 240.0;
        vol: mediaPlayer.volume;
        leftText: Js.calTime(mediaPlayer.position);
        rightText: Js.calTime(mediaPlayer.duration);

        onValueSetChanged: mediaPlayer.seek(Math.round(valueSet * mediaPlayer.duration));
        onVolSetChanged: mediaPlayer.volume = volSet;
    }
}
