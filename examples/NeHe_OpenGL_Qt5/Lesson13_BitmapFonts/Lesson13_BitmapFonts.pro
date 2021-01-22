#-------------------------------------------------
#
# Project created by QtCreator 2014-07-01T11:31:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

target.path = /home/pi/NeHe_OpenGL_Qt5
TARGET = Lesson13_BitmapFonts
INSTALLS += target
TEMPLATE = app

LIBS += libfreetype libz

SOURCES += main.cpp \
    openglwindow.cpp \
    fontwindow.cpp

HEADERS  += \
    openglwindow.h \
    fontwindow.h

RESOURCES += \
    src.qrc
