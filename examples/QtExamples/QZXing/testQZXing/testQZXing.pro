#-------------------------------------------------
#
# Project created by QtCreator 2015-08-21T14:09:30
#
#-------------------------------------------------

QT       += core gui declarative

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += ../QZXingLib

LIBS += -L$$PWD/lib         -lQZXing

TARGET = testQZXing
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += MainWindow.h

FORMS    += MainWindow.ui
