QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = example
TEMPLATE = app

SOURCES += main.cpp\
        wnd.cpp

HEADERS += wnd.h

RESOURCES += \
    example.qrc

CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/ -lnavbar
else:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/ -lnavbard

INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src

CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/libnavbar.a
else:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/libnavbard.a
