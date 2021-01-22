#-------------------------------------------------
#
# Project created by QtCreator 2016-10-28T23:00:13
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NavListView
TEMPLATE = app


SOURCES += main.cpp\
    frmnavlistview.cpp \
    frmnavlistviewform.cpp \
    navlistview.cpp

HEADERS  += \
    navlistview.h \
    frmnavlistview.h \
    frmnavlistviewform.h

FORMS    += \
    frmnavlistview.ui \
    frmnavlistviewform.ui

RESOURCES += \
    rc.qrc
