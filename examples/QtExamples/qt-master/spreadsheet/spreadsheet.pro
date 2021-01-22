#-------------------------------------------------
#
# Project created by QtCreator 2014-11-12T20:28:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = spreadsheet
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    spreadsheet.cpp \
    cell.cpp \
    finddialog.cpp \
    sortdialog.cpp \
    gotocelldialog.cpp

HEADERS  += mainwindow.h \
    spreadsheet.h \
    cell.h \
    finddialog.h \
    gotocelldialog.h \
    sortdialog.h \
    ui_gotocelldialog.h \
    ui_sortdialog.h \
    sortdialog.h \
    gotocelldialog.h

FORMS    += mainwindow.ui \
    gotocelldialog.ui \
    sortdialog.ui

RESOURCES += \
    images.qrc
