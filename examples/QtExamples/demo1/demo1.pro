#-------------------------------------------------
#
# Project created by QtCreator 2016-01-29T14:46:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = demo1
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    showdatetime.cpp \
    showdevicesize.cpp \
    showcpumemory.cpp

HEADERS  += widget.h \
    showcpumemory.h \
    showdatetime.h \
    showdevicesize.h

FORMS    += widget.ui
