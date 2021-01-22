import QtQuick 2.5
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("聊天机器人")

    ConversationPage{
        anchors.fill: parent
    }
}
