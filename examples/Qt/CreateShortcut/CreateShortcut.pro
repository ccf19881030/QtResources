#-------------------------------------------------
#
# Project created by QtCreator 2015-07-20T19:55:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CreateShortcut
TEMPLATE = app


SOURCES += main.cpp\
        createshortcut.cpp

HEADERS  += createshortcut.h

LIBS += -L"D:/Microsoft SDKs/Windows/v7.0/Lib" -lshell32

LIBS += -L"D:/Microsoft SDKs/Windows/v7.0/Lib" -lole32


