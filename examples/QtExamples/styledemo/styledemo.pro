#-------------------------------------------------
#
# Project created by QtCreator 2017-02-19T12:55:42
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET          = styledemo
TEMPLATE        = app
MOC_DIR         = temp/moc
RCC_DIR         = temp/rcc
UI_DIR          = temp/ui
OBJECTS_DIR     = temp/obj
DESTDIR         = bin
win32:RC_FILE   = other/main.rc
PRECOMPILED_HEADER  = head.h

INCLUDEPATH     += $$PWD
CONFIG          += qt warn_off

SOURCES += main.cpp\
    quicreator.cpp     

HEADERS  += head.h\    
    quicreator.h     

FORMS    += \
    quicreator.ui

RESOURCES += \
    other/qss.qrc \
    other/main.qrc
