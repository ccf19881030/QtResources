#-------------------------------------------------
#
# Project created by QtCreator 2015-07-29T08:16:12
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = csdn
TEMPLATE = app


SOURCES += main.cpp\
        cmainwindow.cpp \
    clogindialog.cpp \
    cgetintegral.cpp \
    chelp.cpp \
    cdownresource.cpp \
    cvalidatedialog.cpp \
    caboutdialog.cpp

HEADERS  += cmainwindow.h \
    clogindialog.h \
    cgetintegral.h \
    chelp.h \
    cdownresource.h \
    cvalidatedialog.h \
    caboutdialog.h \
    log_sys/log_sys.h

FORMS    += cmainwindow.ui \
    clogindialog.ui \
    cvalidatedialog.ui \
    caboutdialog.ui

RESOURCES += \
    resource.qrc

RC_FILE += myico.rc
