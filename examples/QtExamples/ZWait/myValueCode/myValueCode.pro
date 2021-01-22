#-------------------------------------------------
#
# Project created by QtCreator 2011-12-01T23:07:29
#
#-------------------------------------------------

QT       += core gui sql widgets multimedia

TARGET = myValueCode
TEMPLATE = app


SOURCES += main.cpp\
        frmmain.cpp \
    mydatahelper.cpp \
    frmdata.cpp

HEADERS  += frmmain.h \
    myStaticClass.h \
    myinclude.h \
    mydatahelper.h \
    frmdata.h

FORMS    += frmmain.ui \
    frmdata.ui

MOC_DIR=temp/moc
RCC_DIR=temp/rcc
UI_DIR=temp/ui
OBJECTS_DIR=temp/obj

win32:RC_FILE=main.rc

RESOURCES += \
    myResource.qrc
