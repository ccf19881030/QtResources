#-------------------------------------------------
#
# Project created by QtCreator 2014-11-19T19:28:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = addressbook
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tablemodel.cpp \
    newaddresstab.cpp \
    addresswidget.cpp \
    adddialog.cpp

HEADERS  += mainwindow.h \
    tablemodel.h \
    newaddresstab.h \
    addresswidget.h \
    adddialog.h

FORMS    += mainwindow.ui
