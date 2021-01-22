#-------------------------------------------------
#
# Project created by QtCreator 2016-07-21T09:58:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myClock
TEMPLATE = app

DESTDIR = $$PWD\bin
RC_FILE = myapp.rc

SOURCES += main.cpp\
        mainwindow.cpp \
    MyDialog.cpp \
    MyFile.cpp

HEADERS  += mainwindow.h \
    MyDialog.h \
    MyFile.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc
