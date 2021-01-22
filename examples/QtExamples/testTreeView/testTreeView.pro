#-------------------------------------------------
#
# Project created by QtCreator 2013-03-07T19:35:29
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = testTreeView
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    TreeView.cpp \
    TreeModel.cpp \
    DevRoot.cpp \
    NodeBase.cpp \
    NodeAA.cpp \
    NodeBB.cpp \
    NodeAAChildA.cpp \
    NodeMac.cpp \
    NodeBBChildA.cpp \
    NodeCC.cpp \
    NodeCCChild.cpp \
    NodeCCChildChild.cpp \
#    CQTGUINetWorkTicketList.cpp \
#    QTableModelNetTicketList.cpp \
#    GUIRealTimeData.cpp \
#    TableModelRealTimeData.cpp

HEADERS  += mainwindow.h \
    TreeView.h \
    TreeModel.h \
    DevRoot.h \
    NodeBase.h \
    NodeAA.h \
    NodeBB.h \
    NodeAAChildA.h \
    NodeMac.h \
    NodeBBChildA.h \
    NodeCC.h \
    NodeCCChild.h \
    NodeCCChildChild.h \
#    CQTGUINetWorkTicketList.h \
#    QTableModelNetTicketList.h \
#    GUIRealTimeData.h \
#    TableModelRealTimeData.h

FORMS    += mainwindow.ui \
#    CQTGUINetWorkTicketList.ui \
#    GUIRealTimeData.ui

RESOURCES += \
    testTreeView.qrc
