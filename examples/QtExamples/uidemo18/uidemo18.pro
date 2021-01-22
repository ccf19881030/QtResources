#-------------------------------------------------
#
# Project created by QtCreator 2017-02-19T12:55:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = uidemo18
TEMPLATE    = app
MOC_DIR     = temp/moc
RCC_DIR     = temp/rcc
UI_DIR      = temp/ui
OBJECTS_DIR = temp/obj
DESTDIR     = $$PWD/../bin

SOURCES     += main.cpp
SOURCES     += iconhelper.cpp
SOURCES     += appinit.cpp
SOURCES     += uidemo18.cpp

HEADERS     += iconhelper.h
HEADERS     += appinit.h
HEADERS     += uidemo18.h

FORMS       += uidemo18.ui

RESOURCES   += main.qrc
CONFIG      += qt warn_off
INCLUDEPATH += $$PWD
