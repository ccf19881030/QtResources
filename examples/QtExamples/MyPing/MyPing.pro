#-------------------------------------------------
#
# Project created by QtCreator 2016-12-25T21:47:13
#
#-------------------------------------------------

QT       += core gui\
            network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyPing
TEMPLATE = app


SOURCES += main.cpp\
        maindialog.cpp \
    qicmp.cpp

HEADERS  += maindialog.h \
    qicmp.h

FORMS    += maindialog.ui \
    detail.ui

win32: LIBS += -L$$PWD/../../Qt/Qt5.6.2/Tools/mingw492_32/i686-w64-mingw32/lib/ -lws2_32

INCLUDEPATH += $$PWD/../../Qt/Qt5.6.2/Tools/mingw492_32/i686-w64-mingw32/include
DEPENDPATH += $$PWD/../../Qt/Qt5.6.2/Tools/mingw492_32/i686-w64-mingw32/include
