#-------------------------------------------------
#
# Project created by QtCreator 2015-05-09T15:07:15
#
#-------------------------------------------------

QT       += core gui

qtHaveModule(printsupport): QT += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CH5_ImageProcessor
TEMPLATE = app


SOURCES += main.cpp\
        imgprocessor.cpp \
		showwidget.cpp

HEADERS  += imgprocessor.h \
		showwidget.h
