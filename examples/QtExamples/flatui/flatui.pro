#-------------------------------------------------
#
# Project created by QtCreator 2017-01-09T09:29:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = flatui
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmflatui.cpp \
    flatui.cpp

HEADERS  += frmflatui.h \
    flatui.h

FORMS    += frmflatui.ui
