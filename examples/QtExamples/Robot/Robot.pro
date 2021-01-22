TEMPLATE = app

QT += qml quick network xml
CONFIG += c++11

SOURCES += main.cpp \
    turing.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    turing.h
