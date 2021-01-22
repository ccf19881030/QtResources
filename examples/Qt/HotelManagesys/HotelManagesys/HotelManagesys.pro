#-------------------------------------------------
#
# Project created by QtCreator 2014-12-21T13:21:57
#
#-------------------------------------------------

QT       += core gui
QT       +=sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HotelManagesys
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    app/iconhelper.cpp \
    app/frmmessagebox.cpp \
    logindialog.cpp \
    registerdialog.cpp \
    app/mysqlapi.cpp \
    promanage.cpp \
    app/myapp.cpp \
    app/myhelper.cpp \
    app/mythread.cpp \
    costomerregisterinfodialog.cpp \
    customerwindget.cpp \
    romminfo.cpp \
    modiftroomprice.cpp \
    checkcutomdialog.cpp \
    logblogdialog.cpp \
    modifypwddialog.cpp \
    roompicdialog.cpp \
    backupdatanasedialog.cpp \
    checkoutdialog.cpp

HEADERS  += widget.h \
    app/iconhelper.h \
    app/frmmessagebox.h \
    logindialog.h \
    registerdialog.h \
    app/Connection.h \
    app/mysqlapi.h \
    promanage.h \
    app/myapp.h \
    app/myhelper.h \
    app/mythread.h \
    costomerregisterinfodialog.h \
    customerwindget.h \
    romminfo.h \
    modiftroomprice.h \
    checkcutomdialog.h \
    logblogdialog.h \
    modifypwddialog.h \
    roompicdialog.h \
    backupdatanasedialog.h \
    checkoutdialog.h

FORMS    += widget.ui \
    app/frmmessagebox.ui \
    logindialog.ui \
    registerdialog.ui \
    promanage.ui \
    costomerregisterinfodialog.ui \
    customerwindget.ui \
    romminfo.ui \
    modiftroomprice.ui \
    checkcutomdialog.ui \
    logblogdialog.ui \
    modifypwddialog.ui \
    roompicdialog.ui \
    backupdatanasedialog.ui \
    checkoutdialog.ui

MOC_DIR=temp/moc
RCC_DIR=temp/rcc
UI_DIR=temp/ui
OBJECTS_DIR=temp/obj
DESTDIR=bin

win32:RC_FILE=main.rc

RESOURCES += \
    image.qrc
