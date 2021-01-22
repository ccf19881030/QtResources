TEMPLATE = app

QT += qml quick core

SOURCES += main.cpp \
    lyrics.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES +=

HEADERS += \
    lyrics.h

RC_FILE = icon.rc
