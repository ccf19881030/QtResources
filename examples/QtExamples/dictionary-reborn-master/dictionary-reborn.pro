#-------------------------------------------------
#
# Project created by QtCreator 2017-07-31T21:42:42
#
#-------------------------------------------------

QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dictionary-reborn
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        main_window.cpp \
    left_widget.cpp \
    right_widget.cpp \
    utils.cpp \
    home_page.cpp \
    translate_page.cpp \
    about_page.cpp \
    everyday_page.cpp \
    dict_page.cpp \
    youdao_api.cpp

HEADERS  += main_window.h \
    left_widget.h \
    right_widget.h \
    utils.h \
    home_page.h \
    translate_page.h \
    about_page.h \
    everyday_page.h \
    dict_page.h \
    youdao_api.h

RESOURCES += resources.qrc
