#-------------------------------------------------
#
# Project created by QtCreator 2014-11-24T22:57:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TrackEditor
TEMPLATE = app


SOURCES += main.cpp\
        trackeditor.cpp \
    trackdelegate.cpp

HEADERS  += trackeditor.h \
    trackdelegate.h

FORMS    += trackeditor.ui
