TARGET = navbar
TEMPLATE = lib
CONFIG += staticlib
DESTDIR = ../lib
TARGET = $$qtLibraryTarget($$TARGET)
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += navbar.cpp \
    navbarpagelistwidget.cpp \
    navbarsplitter.cpp \
    navbaroptionsdialog.cpp \
    navbarheader.cpp

HEADERS += navbar.h \
    navbarpagelistwidget.h \
    navbarsplitter.h \
    navbaroptionsdialog.h \
    navbarpage.h \
    navbarheader.h

RESOURCES += \
    navbar.qrc

FORMS += \
    navbaroptionsdialog.ui
