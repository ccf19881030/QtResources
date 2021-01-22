#-------------------------------------------------
#
# Project created by QtCreator 2016-09-19T13:33:20
#
#-------------------------------------------------

QT       += core gui network sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET              = NetTool
TEMPLATE            = app
MOC_DIR             = temp/moc
RCC_DIR             = temp/rcc
UI_DIR              = temp/ui
OBJECTS_DIR         = temp/obj
DESTDIR             = bin
win32:RC_FILE       = main.rc
PRECOMPILED_HEADER  = myhelper.h

SOURCES += main.cpp\
    frmnettool.cpp \
    tcpserver.cpp \
    app.cpp

HEADERS  +=\
    frmnettool.h \
    tcpserver.h \
    app.h \
    myhelper.h

FORMS    += frmnettool.ui

RESOURCES += \
    main.qrc

CONFIG += qt warn_off release

    src_file = $$PWD/send.txt
    dst_file = $$OUT_PWD/bin/send.txt
win32 {   
    src_file ~= s,/,\\,g
    dst_file ~= s,/,\\,g
    system(copy /y $$src_file $$dst_file)
}
unix {    
    system(cp -r -f $$src_file $$dst_file)
}
