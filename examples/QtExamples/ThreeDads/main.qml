import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
ApplicationWindow {
    visible: true
    width: 320
    height: 640
    title: qsTr("空气净化器")
MainForm{
    anchors.fill: parent
}

/*
    MessageDialog {
        id: messageDialog
        title: qsTr("May I have your attention, please?")

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }*/
}
