import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import "../myJs.js" as Js

Rectangle{
    id: bBarRoot;
    height: 50;
    width: 1024;

    property real value: 0.0;
    property real vol: 0.0;

    property string leftText: "00:00";
    property string rightText: "00:00";

    property real valueSet: 0.0;
    property real volSet: 0.0;

    property bool showPIcon : true;
    //分隔条
    Rectangle{
        id: bBSeparetor;
        width: parent.width;
        height:1;
        border.width: 1;
        anchors.top: parent.top;
        anchors.left: parent.left;
        color: "#E1E1E2";
    }

    //播放按钮
    Row{
        id: bBBtnRow;
        anchors.left: parent.left;
        anchors.leftMargin: 30;
        anchors.verticalCenter: parent.verticalCenter;
        spacing: 15;


        //上一首
        Rectangle{
            id: btnPre;
            width: 30;
            height: 30;
            radius: 15;
            color: "#C62F2F";
            anchors.verticalCenter: parent.verticalCenter;
            opacity: preArea.containsMouse ? 1.0 : 0.9;
            Image{
                anchors.centerIn: parent;
                source: "qrc:///bottomwidget/btnPrevious1.png";
                z: 1;
            }
            MouseArea{
                id: preArea;
                anchors.fill: parent;
                hoverEnabled: true;
                onClicked: {
                    Js.playMusic(Js.gCurrentRow - 1);
                }
            }
        }

        //播放
        Rectangle{
            id: btnPlay;
            width: 40;
            height: 40;
            radius: 20;
            color: "#C62F2F";
            anchors.verticalCenter: parent.verticalCenter;
            opacity: playArea.containsMouse ? 1.0 : 0.9;
            visible: true;

            Image{
                id: imgPlay;
                anchors.centerIn: parent;
                source: "qrc:///bottomwidget/btnPlay1.png";
                z: 1;
                visible: bBarRoot.showPIcon;
                MouseArea{
                    anchors.fill: parent;
                    onClicked: {
                        Js.gMPlayer.play();
                    }
                }
            }
            Image{
                id: imgPause;
                anchors.centerIn: parent;
                source: "qrc:///bottomwidget/btnPause1.png";
                z: 1;
                visible: !bBarRoot.showPIcon;
                MouseArea{
                    anchors.fill: parent;
                    onClicked: {
                        Js.gMPlayer.pause();
                    }
                }
            }
            MouseArea{
                id: playArea
                anchors.fill: parent;
                hoverEnabled: true;
            }
        }


        //下一首
        Rectangle{
            id: btnNext;
            width: 30;
            height: 30;
            radius: 15;
            color: "#C62F2F";
            anchors.verticalCenter: parent.verticalCenter;
            opacity: nextArea.containsMouse ? 1.0 : 0.9;
            Image{
                anchors.centerIn: parent;
                source: "qrc:///bottomwidget/btnNext1.png";
                z: 1;
            }
            MouseArea{
                id: nextArea;
                anchors.fill: parent;
                hoverEnabled: true;
                onClicked: {
                    Js.playMusic(Js.gCurrentRow + 1);
                }
            }
        }
    }

    Text{
        id: musicSliderText;
        anchors{
            left: bBBtnRow.right;
            leftMargin: 20;
            verticalCenter: parent.verticalCenter;
        }
        width: 30;
        clip: true;
        text: bBarRoot.leftText;
    }

    //歌曲进度条
    Slider{
        id: valueSlider;
        anchors{
            left: musicSliderText.right;
            leftMargin: 10;
            right: musicSliderText2.left;
            rightMargin: 10;
            verticalCenter: parent.verticalCenter;
        }

        minimumValue: 0.0;
        maximumValue: 240.0;
        value: bBarRoot.value;
        MouseArea{
            anchors.fill: parent;
            onPressed: {
                mouse.accepted = false;
                bBarRoot.valueSet = mouse.x / parent.width ;
            }

        }

        style: SliderStyle{
            handle: Rectangle{
                width: 16;
                height: 16;
                border.width: 1;
                border.color: "#E1E1E2";
                radius: 10;
                Rectangle{
                    width: 4;
                    height: 4;
                    color: "red";
                    radius: 10;
                    anchors.centerIn: parent;
                }
            }
        }



    }

    Text{
        id: musicSliderText2;
        width: 30;
        anchors{
            right: bBSndSlider.left;
            rightMargin: 20;
            verticalCenter: parent.verticalCenter;
        }
        text: bBarRoot.rightText;
        clip: true;
    }

    //音量进度条
    Row{
        id: bBSndSlider;
        anchors.right: bBSequenceRow.left;
        anchors.rightMargin: 25;
        anchors.verticalCenter: parent.verticalCenter;
        spacing: 10;
        Image{
            anchors.verticalCenter: parent.verticalCenter;
            source: "qrc:///bottomwidget/menuVol.png";
            opacity: sndArea.containsMouse ? 1.0 : 0.9;
            MouseArea{
                id: sndArea;
                anchors.fill: parent;
                hoverEnabled: true;
            }
        }

        Slider{
            id: volSlider;
            anchors.verticalCenter: parent.verticalCenter;
            width: 120;
            minimumValue: 0.0;
            maximumValue: 1.0;
            value: bBarRoot.vol;
            MouseArea{
                anchors.fill: parent;
                onPressed: {
                    mouse.accepted = false;
                    bBarRoot.volSet = mouse.x / parent.width;
                }

            }

            style: SliderStyle{
                handle: Rectangle{
                    id: volHandle;
                    width: 16;
                    height: 16;
                    border.width: 1;
                    border.color: "#E1E1E2";
                    radius: 10;
                    Rectangle{
                        width: 4;
                        height: 4;
                        color: "red";
                        radius: 10;
                        anchors.centerIn: parent;
                    }

                }
            }
        }

    }

    //歌曲播放顺序设置
    Row{
        id: bBSequenceRow;
        spacing: 14;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.right: parent.right;
        anchors.rightMargin: 20;

        //顺序播放
        Image{
            id: sequenceBtn;
            width: 20;
            height: 20;
            anchors.verticalCenter: parent.verticalCenter;
            source: "qrc:///bottomwidget/listsequence.png";

            opacity: sequenceArea.containsMouse ? 1.0 : 0.9;
            MouseArea{
                id: sequenceArea;
                anchors.fill: parent;
                hoverEnabled: true;
                property var clickNum: 0;
                onClicked: {
                    switch(clickNum % 4)
                    {
                    case 0:
                        parent.source = "qrc:///bottomwidget/listsequence.png";
                        break;
                    case 1:
                        parent.source = "qrc:///bottomwidget/listcircle.png";
                        break;
                    case 2:
                        parent.source = "qrc:///bottomwidget/listrandom.png";
                        break;
                    case 3:
                        parent.source = "qrc:///bottomwidget/listsingle.png";
                        break;
                    }
                    clickNum++;
                }
            }
        }

        //歌词
        Image{
            id: lrcBtn;
            width: 20;
            height: 20;
            anchors.verticalCenter: parent.verticalCenter;
            source: "qrc:///bottomwidget/menuLrc.png";
            opacity: lrcArea.containsMouse ? 1.0 : 0.8;
            MouseArea{
                id: lrcArea;
                anchors.fill: parent;
                hoverEnabled: true;
            }
        }

        //歌曲列表按钮
        Rectangle{
            id: listBtn;
            width: 50;
            height: 18;
            anchors.verticalCenter: parent.verticalCenter;
            color: "#E1E1E2";
            radius: 10;
            Image{
                width: 20;
                height: 20;
                anchors.verticalCenter: parent.verticalCenter;
                anchors.left: parent.left;
                z: 1;
                source: "qrc:///bottomwidget/btnlist.png";
                opacity: lrcListArea.containsMouse ? 1.0 : 0.8;
                MouseArea{
                    id: lrcListArea;
                    anchors.fill: parent;
                    hoverEnabled: true;
                }
            }
            Text{
                anchors.verticalCenter: parent.verticalCenter;
                anchors.right: parent.right;
                anchors.rightMargin: 10;
                text: "32";
                z: 1;
            }
        }
    }

}
