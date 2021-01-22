import QtQuick 2.0
import QtQuick.Window 2.1
import QtMultimedia 5.0
import QtQuick.Controls 1.3
import QtQuick.Particles 2.0
import QtQuick.Controls.Styles 1.3
import lyrics 1.0

Window {
    id: mainWindow
    visible: true
    width: 260
    height: 400
    flags: Qt.FramelessWindowHint | Qt.Window
    title: "I●Love◇Crazy"
    MediaPlayer {
        id: mediaPlayer
        source: music.musicName.length == 0 ? "" : music.musicUrl + music.musicName
        autoPlay: false
        loops: MediaPlayer.Infinite
        onPositionChanged: {
            if(mediaPlayer.position >= mediaPlayer.duration)
            {
                lyric.iniFun()
                lyric.starts = true
            }
        }

    }

    Rectangle {
        id: backgroundRec
        color: "#add9ff"
        anchors.fill: parent
        width: parent.width
        height: parent.height

        Music {
            id: music
            anchors.top: backgroundRec.top
            anchors.bottom: timeGress.top
            onExchangeChanged: {
                if(music.exchange == 1)
                {
                    musicAnimation.running = true;
                }
            }
            onMusicNameChanged: {
                lyric.count = 0
                lyric.time = 5
                mediaPlayer.source = music.musicUrl + music.musicName
                lyric.lyricL = urlLy.getLyric(lyric.lyricUrl + music.musicName)
                lyric.lyricT = urlLy.getTime()
                lyric.starts = true
            }

            Ly {
                id: urlLy
            }
        }

        Lyric {
            id: lyric
            width: parent.width
            height: parent.height / 3 * 2
            anchors.top: backgroundRec.top
            anchors.bottom: buttomRow.top
            anchors.bottomMargin: 3
            visible: false
            opacity: 0
            scale: 0
        }

        ParallelAnimation {
            id: musicAnimation
            NumberAnimation {
                target: music
                property: "opacity"
                duration: 640
                to: 0
                easing.type: Easing.InCubic
            }
            NumberAnimation {
                target: music
                property: "scale"
                duration: 640
                to: 0
                easing.type: Easing.InCubic
            }
            running: false
            onStopped: {
                lyricAnimation.running = true;
                lyric.visible = true
                music.visible = false
            }
        }

        ParallelAnimation {
            id: musicAnimationT
            NumberAnimation {
                target: music
                property: "opacity"
                duration: 640
                to: 1
                easing.type: Easing.InCubic
            }
            NumberAnimation {
                target: music
                property: "scale"
                duration: 640
                to: 1
                easing.type: Easing.InCubic
            }
            running: false
            onStopped: {
                music.exchange = 0;
            }
        }

        ParallelAnimation {
            id: lyricAnimation
            NumberAnimation {
                target: lyric
                property: "opacity"
                duration: 640
                to: 1
                easing.type: Easing.InCubic
            }
            NumberAnimation {
                target: lyric
                property: "scale"
                duration: 640
                to: 1
                easing.type: Easing.InCubic
            }
            running: false
            onStopped: {
                canvasMiddle_play.visible = true
                canvasMiddle_stop.visible = false
                mediaPlayer.play()
            }
        }

        ParallelAnimation {
            id: lyricAnimationT
            NumberAnimation {
                target: lyric
                property: "opacity"
                duration: 640
                to: 0
                easing.type: Easing.InCubic
            }
            NumberAnimation {
                target: lyric
                property: "scale"
                duration: 640
                to: 0
                easing.type: Easing.InCubic
            }
            running: false
            onStopped: {
                musicAnimationT.running = true
                lyric.visible = false
                music.visible = true
            }
        }

        ProgressBar {
            id: timeGress
            width: parent.width
            height: 3
            antialiasing: true
            anchors.bottom: buttomRow.top
            anchors.bottomMargin: 2
            value: mediaPlayer.position / mediaPlayer.duration
            z: 10
            property int itemWidth: 6

            style: ProgressBarStyle {
                  background: Rectangle {
                      radius: 2
                      color: "#ffffff"
                      implicitWidth: timeGress.width
                      implicitHeight: 3
                  }
                  progress: Rectangle {
                      color: "#00cc99"
                      border.color: "#00cc99"

                      Rectangle {
                          id: item
                          width: timeGress.itemWidth
                          height: timeGress.itemWidth
                          radius: timeGress.itemWidth / 2
                          color: "white"
                          anchors.right: parent.right
                          anchors.rightMargin: -timeGress.itemWidth / 2
                          anchors.verticalCenter: parent.verticalCenter
                          ParticleSystem {id: s1}

                          ImageParticle {
                              system: s1
                              source: "image/glowdot.png"
                              color: "cyan"
                              alpha: 0

                              SequentialAnimation on color {
                                  loops: Animation.Infinite
                                  ColorAnimation {
                                      from: "red"
                                      to: "yellow"
                                      duration: 1000
                                  }
                                  ColorAnimation {
                                      from: "yellow"
                                      to: "red"
                                      duration: 1000
                                  }
                              }
                              colorVariation: 0.3
                          }

                          Emitter {
                              id: trailsNormal
                              system: s1

                              emitRate: 100
                              lifeSpan: 2000

                              x: item.width / 2
                              y: item.height / 2

                              velocity: PointDirection {xVariation: 4; yVariation: 4;}
                              acceleration: PointDirection {xVariation: 10; yVariation: 10;}
                              velocityFromMovement: 8
                              size: 8
                              sizeVariation: 4
                          }
                      }
                  }
              }
            MouseArea {
                anchors.fill: parent
                onPressed: {
                    mediaPlayer.seek(mouse.x / parent.width * mediaPlayer.duration);
                    lyric.count = Math.round(mediaPlayer.position / 10)
                }
                hoverEnabled: true
                onEntered: timeGress.itemWidth = 8
                onExited: timeGress.itemWidth = 6
            }
         }

        Row{
        id: buttomRow
        width: backgroundRec.width / 10 * 9
        height: backgroundRec.width / 5 - 2
        opacity: 0.8
        spacing: backgroundRec.width / 10
        anchors.bottom: backgroundRec.bottom
        anchors.bottomMargin: buttomRow.height / 6
        anchors.left: backgroundRec.left
        anchors.leftMargin: backgroundRec.width / 10

        Rectangle {
            id: leftRec
            width: backgroundRec.width / 5
            height: backgroundRec.width / 5
            radius: backgroundRec.width / 2
            border.color: "white"
            border.width: 0
            color: "#00cc99"

            MouseArea {
                anchors.fill: parent
                onPressed: {
                    leftRec.border.width = 1;
                    mediaPlayer.play();
                    mediaPlayer.autoPlay = "true";
                    lyric.iniFun();
                    lyric.starts = true
                    canvasMiddle_play.visible = true
                    canvasMiddle_stop.visible = false
                }
                onReleased: {
                    leftRec.border.width = 0;
                    if(music.musicIndex >= 1)
                    {
                        music.musicIndex -= 1;
                        music.musicName = music.listModel.get(music.musicIndex,"fileName")
                    }
                }
            }

            Canvas {
                id: canvasLeft
                anchors.fill: parent
                onPaint: {
                    var ctx = getContext("2d");
                    ctx.lineWidth = 1;
                    ctx.strokeStyle = "white";
                    ctx.fillStyle = "white";
                    ctx.beginPath();
                    ctx.moveTo(parent.width / 3 * 2, parent.height / 4);
                    ctx.lineTo(parent.width / 6 , parent.height / 2);
                    ctx.lineTo(parent.width / 3 * 2, parent.height / 4 * 3);
                    ctx.closePath();
                    ctx.fill();
                    ctx.stroke();
            }
          }
        }

        Rectangle {
            id: middleRec
            width: mainWindow.width / 5
            height: mainWindow.width / 5
            radius: mainWindow.width / 2
            border.color: "white"
            border.width: 0
            color: "#00cc99"

            MouseArea {
                anchors.fill: parent
                onPressed: {
                    middleRec.border.width = 1;
                    if(canvasMiddle_play.visible)
                    {
                        mediaPlayer.pause();
                        lyric.starts = false;
                    }else
                    {
                        lyric.starts = true;
                        mediaPlayer.play();
                    }

                }
                onReleased: {
                    middleRec.border.width = 0;
                    canvasMiddle_play.visible = canvasMiddle_play.visible == true ? false : true
                    canvasMiddle_stop.visible = canvasMiddle_play.visible == true ? false : true
                }
            }

            Canvas {
                id: canvasMiddle_stop
                visible: true
                anchors.fill: parent
                onPaint: {
                    var ctx = getContext("2d");
                    ctx.lineWidth = 1;
                    ctx.strokeStyle = "white";
                    ctx.fillStyle = "white";
                    ctx.beginPath();
                    ctx.rect(parent.width / 3 ,parent.width / 3, parent.width / 3, parent.width / 3);
                    ctx.fill();
                    ctx.stroke();
            }
          }
            Canvas {
                id: canvasMiddle_play
                visible: false
                anchors.fill: parent
                onPaint: {
                    var ctx = getContext("2d");
                    ctx.lineWidth = 1;
                    ctx.strokeStyle = "white";
                    ctx.fillStyle = "white";
                    ctx.beginPath();
                    ctx.moveTo(parent.width / 3 ,parent.width /3);
                    ctx.lineTo(parent.width / 3 + parent.width / 9,parent.width / 3);
                    ctx.lineTo(parent.width / 3 + parent.width / 9,parent.height /3 *2);
                    ctx.lineTo(parent.width / 3, parent.width / 3 * 2);
                    ctx.lineTo(parent.width / 3, parent.width / 3);

                    ctx.moveTo(parent.width / 3 + parent.width / 9 * 2 ,parent.width / 3);
                    ctx.lineTo(parent.width / 3 * 2,parent.width / 3);
                    ctx.lineTo(parent.width / 3 * 2,parent.height /3 *2);
                    ctx.lineTo(parent.width / 3 + parent.width / 9 * 2, parent.width / 3 * 2);
                    ctx.lineTo(parent.width / 3 + parent.width / 9 * 2, parent.width / 3);

                    ctx.closePath();
                    ctx.fill();
                    ctx.stroke();
                }
            }
        }

        Rectangle {
            id: rightRec
            width: mainWindow.width / 5
            height: mainWindow.width / 5
            radius: mainWindow.width / 2
            border.color: "white"
            border.width: 0
            color: "#00cc99"

            MouseArea {
                anchors.fill: parent
                onPressed: {
                    rightRec.border.width = 1;
                    mediaPlayer.play();
                    lyric.iniFun();
                    lyric.starts = true
                    mediaPlayer.autoPlay = "true";
                    canvasMiddle_play.visible = true
                    canvasMiddle_stop.visible = false
                }
                onReleased: {
                    rightRec.border.width = 0;
                    if(music.musicIndex < music.listModel.count - 1)
                    {
                        music.musicIndex += 1;
                        music.musicName = music.listModel.get(music.musicIndex,"fileName")
                    }
                }
            }

            Canvas {
                id: canvasRight
                anchors.fill: parent
                onPaint: {
                    var ctx = getContext("2d");
                    ctx.lineWidth = 1;
                    ctx.strokeStyle = "white";
                    ctx.fillStyle = "white";
                    ctx.beginPath();
                    ctx.moveTo(parent.width / 3 , parent.height / 4);
                    ctx.lineTo(parent.width / 6 * 5 , parent.height / 2);
                    ctx.lineTo(parent.width / 3 , parent.height / 4 * 3);
                    ctx.closePath();
                    ctx.fill();
                    ctx.stroke();
            }
          }
        }
    }
  }
}

























