#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T11:19:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = imagecalendar
TEMPLATE    = app
DESTDIR     = $$PWD/../bin

SOURCES += main.cpp\
        frmimagecalendar.cpp \
    imagecalendar.cpp \
    lunarcalendarinfo.cpp

HEADERS  += frmimagecalendar.h \
    imagecalendar.h \
    lunarcalendarinfo.h

FORMS    += frmimagecalendar.ui

RESOURCES += \
    main.qrc
