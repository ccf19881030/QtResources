# -------------------------------------------------
# QT Project File
# -------------------------------------------------
TARGET = realtimeviewport

TEMPLATE = app
greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
} 

SOURCES += qchartviewer.cpp \
    realtimeviewport.cpp \
    randomwalk.cpp

HEADERS += qchartviewer.h \
    realtimeviewport.h \
    randomwalk.h \
    qdoublebufferedqueue.h

RESOURCES += realtimeviewport.qrc

INCLUDEPATH += ../../include

DEFINES += CHARTDIR_HIDE_OBSOLETE _CRT_SECURE_NO_WARNINGS

win32:contains(QMAKE_HOST.arch, x86_64) {
  LIBS += ../../lib64/chartdir60.lib
  QMAKE_POST_LINK = copy /Y ..\\..\\lib64\\chartdir60.dll $(DESTDIR)
} else {
  LIBS += ../../lib32/chartdir60.lib
  QMAKE_POST_LINK = copy /Y ..\\..\\lib32\\chartdir60.dll $(DESTDIR)
}

macx:LIBS += -L../../lib -lchartdir
macx:QMAKE_POST_LINK += mkdir -p \"`dirname $(TARGET)`/../Frameworks\";
macx:QMAKE_POST_LINK += cp ../../lib/libchartdir.6.dylib \"`dirname $(TARGET)`/../Frameworks\";
macx:QMAKE_POST_LINK += install_name_tool -change libchartdir.6.dylib \
     \@loader_path/../Frameworks/libchartdir.6.dylib \"$(TARGET)\";

unix:!macx:LIBS += -L../../lib -lchartdir
unix:!macx:QMAKE_RPATHDIR += ../../lib

