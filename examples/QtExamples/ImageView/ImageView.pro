#-------------------------------------------------
#
# Project created by QtCreator 2017-06-05T17:11:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageView
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    blackpixmapitem.cpp \
    imageloadthread.cpp \
    customgraphicsview.cpp \
    imagepreview.cpp \
    imageview.cpp

HEADERS  += mainwindow.h \
    blackpixmapitem.h \
    imageloadthread.h \
    customgraphicsview.h \
    imagepreview.h \
    imageview.h

FORMS    += mainwindow.ui
