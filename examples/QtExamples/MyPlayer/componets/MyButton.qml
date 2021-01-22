import QtQuick 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Rectangle{
    id: myBRoot;
    width: 200;
    height: 34;
    color: myBArea.containsMouse ? "#E6E7EA" : "#F5F5F7";

    property var myText: "";
    property var source: "";
    property var leftSpace: 10;
    property var spacing: 10;
    signal btnClicked(var txt);

    MouseArea{
        id: myBArea;
        anchors.fill: parent;
        hoverEnabled: true;
        onClicked: {
            myBRoot.btnClicked(myText);
        }
    }

    Row{
        height: 30;
        anchors.verticalCenter: parent.verticalCenter;
        anchors.left: parent.left;
        anchors.leftMargin: myBRoot.leftSpace;
        spacing: myBRoot.spacing;

        Image{
            id: mBIcon;
            width: 20;
            height: 20;
            anchors.verticalCenter: parent.verticalCenter;
            source: myBRoot.source;
            opacity: myBArea.containsMouse ? 1.0 : 0.7;
        }

        Text{
            id: mBText
            anchors.verticalCenter: parent.verticalCenter;
            opacity: myBArea.containsMouse ? 1.0 : 0.7;
            text: myBRoot.myText;
        }
    }

}
