/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import io.qt.turing 1.0

Page {
    id: root

    Turning{
        id: robot
    }

    function addToSession(text, me)
    {
        if(text.length <= 0)
        {
            return;
        }

        listView.model.insert(0, {"content": text, "Me": me});
        messageField.text = "";
        messageField.focus = true;
        //verScrollBar.increase()
        verScrollBar.setPosition(1.0)

        if(me)
        {
            robot.send(text)
        }
    }

    ColumnLayout {
        anchors.fill: parent

        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: pane.leftPadding + messageField.leftPadding
            displayMarginBeginning: 40
            displayMarginEnd: 40
            verticalLayoutDirection: ListView.BottomToTop
            spacing: 16
            model: ListModel {

            }

            delegate: Column {
                anchors.right: sentByMe ? parent.right : undefined
                spacing: 6

                property bool sentByMe: Me

                Label {
                    id: timestampText
                    text: Qt.formatDateTime(new Date(), "yyyy-MM-dd hh:mm:ss")
                    color: "gray"
                    anchors.right: sentByMe ? parent.right : undefined
                }

                Row {
                    id: messageRow
                    spacing: 6
                    anchors.right: sentByMe ? parent.right : undefined

                    Image {
                        id: avatarLeft
                        height: 32
                        width: height
                        visible: !sentByMe
                        source: "qrc:/robot.png"
                    }

                    Rectangle {
                        width: Math.min(messageText.implicitWidth + 24, listView.width - (sentByMe ? avatarRight.width : avatarLeft.width) - messageRow.spacing)
                        height: messageText.implicitHeight + 24
                        color: sentByMe ? "lightgrey" : "steelblue"

                        Label {
                            id: messageText
                            text: content
                            color: sentByMe ? "black" : "white"
                            anchors.fill: parent
                            anchors.margins: 12
                            wrapMode: Label.Wrap
                        }
                    }

                    Image {
                        id: avatarRight
                        height: 32
                        width: height
                        visible: sentByMe
                        source: "qrc:/me.png"
                    }
                }
            }

            ScrollBar.vertical: ScrollBar {
                id: verScrollBar
            }
        }

        Rectangle{
            Layout.fillWidth: true
            height: 2
            color: "gray"
        }

        Pane {
            id: pane
            Layout.fillWidth: true
            RowLayout {
                width: parent.width
                spacing: 6

                TextArea {
                    id: messageField
                    Layout.fillWidth: true
                    placeholderText: qsTr("输入消息")
                    wrapMode: TextArea.Wrap

                    Keys.onReturnPressed: {
                        addToSession(messageField.text, true)
                    }
                }

                Button {
                    id: sendButton
                    text: qsTr("发送")
                    enabled: messageField.length > 0
                    onClicked: {
                        addToSession(messageField.text, true)
                    }
                }
            }
        }

        Connections{
            target: robot
            onReceived:{
                addToSession(str, false)
            }
        }
    }
}

