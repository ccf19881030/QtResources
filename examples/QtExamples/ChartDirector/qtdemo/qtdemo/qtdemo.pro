# -------------------------------------------------
# QT Project File
# -------------------------------------------------
TARGET = qtdemo

TEMPLATE = app
greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
} 

SOURCES += qchartviewer.cpp \
    hotspotdialog.cpp \
    qtdemo.cpp \
    democharts.cpp
    
HEADERS += qchartviewer.h \
    hotspotdialog.h \
    qtdemo.h \
    democharts.h

INCLUDEPATH += ../../include

DEFINES += CHARTDIR_HIDE_OBSOLETE _CRT_SECURE_NO_WARNINGS

win32:DESTDIR = $$PWD
win32:contains(QMAKE_HOST.arch, x86_64) {
  LIBS += ../../lib64/chartdir60.lib
  QMAKE_POST_LINK = copy /Y ..\\..\\lib64\\chartdir60.dll $(DESTDIR)
} else {
  LIBS += ../../lib32/chartdir60.lib
  QMAKE_POST_LINK = copy /Y ..\\..\\lib32\\chartdir60.dll $(DESTDIR)
}

macx:CONFIG -= app_bundle
macx:DESTDIR = $$PWD
macx:LIBS += -L../../lib -lchartdir
macx:QMAKE_POST_LINK += cp ../../lib/libchartdir.6.dylib \"$(DESTDIR)\"

unix:!macx:DESTDIR = $$PWD
unix:!macx:LIBS += -L../../lib -lchartdir
unix:!macx:QMAKE_RPATHDIR += ../../lib

