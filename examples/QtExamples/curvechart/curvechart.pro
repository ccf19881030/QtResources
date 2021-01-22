#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T09:56:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = curvechart
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmcurvechart.cpp \
    curvechart.cpp

HEADERS  += frmcurvechart.h \
    curvechart.h

FORMS    += frmcurvechart.ui
