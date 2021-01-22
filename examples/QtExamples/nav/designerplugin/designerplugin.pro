TARGET = navbarplugin
TEMPLATE = lib

greaterThan(QT_MAJOR_VERSION, 4): QT += designer
lessThan(QT_MAJOR_VERSION, 5): CONFIG  += designer plugin

TARGET = $$qtLibraryTarget($$TARGET)
DESTDIR = $$[QT_INSTALL_PLUGINS]/designer

SOURCES += \
    navbarplugin.cpp \
    navbarcontainerextension.cpp \
    navbarextensionfactory.cpp

HEADERS += \
    navbarplugin.h \
    navbarcontainerextension.h \
    navbarextensionfactory.h

CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/ -lnavbar
else:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/ -lnavbard

INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src

CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/libnavbar.a
else:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lib/libnavbard.a
