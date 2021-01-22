#-------------------------------------------------
#
# Project created by QtCreator 2017-05-24T18:38:15
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = uidemo17
TEMPLATE    = app

SOURCES     += main.cpp
SOURCES     += iconhelper.cpp
SOURCES     += flatui.cpp
SOURCES     += appinit.cpp
SOURCES     += uidemo17.cpp

HEADERS     += head.h
HEADERS     += iconhelper.h
HEADERS     += flatui.h
HEADERS     += appinit.h
HEADERS     += uidemo17.h

FORMS       += uidemo17.ui

RESOURCES   += main.qrc
CONFIG      += qt warn_off
