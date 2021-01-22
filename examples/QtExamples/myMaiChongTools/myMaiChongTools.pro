#-------------------------------------------------
#
# Project created by QtCreator 2013-09-24T10:03:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myMaiChongTools
TEMPLATE = app


SOURCES += main.cpp\
        frmmain.cpp \
    win_qextserialport.cpp \
    qextserialbase.cpp \
    myapp.cpp \
    mymaichongapi.cpp

HEADERS  += frmmain.h \
    win_qextserialport.h \
    qextserialbase.h \
    myhelper.h \
    myapp.h \
    mymaichongapi.h

FORMS    += frmmain.ui

MOC_DIR=temp/moc
RCC_DIR=temp/rcc
UI_DIR=temp/ui
OBJECTS_DIR=temp/obj
DESTDIR=bin

win32:RC_FILE=main.rc

RESOURCES += \
    main.qrc
