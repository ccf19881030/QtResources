import QtQuick 2.5

Rectangle{
    id: musicTitle;
    property string name ;
    property string singer ;

    color: "#fafafa";
    border{
        width: 1;
        color: "#E1E1E2"
    }
    TextEdit{
        id: musicName;
        anchors{
            left: parent.left;
            leftMargin: 20;
            top: parent.top;
            topMargin: 20;
        }
        verticalAlignment: Text.AlignVCenter;
        readOnly: true;
        text: parent.name + "\n" + parent.singer;
    }
}
