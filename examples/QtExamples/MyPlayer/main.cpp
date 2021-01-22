#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "musicmanager.h"
#include "musicmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QGuiApplication::addLibraryPath("./plugins");
    qmlRegisterType<MusicModel>("MusicInfo", 1, 0, "MusicModel");
    qmlRegisterType<MusicManager>("MusicInfo", 1, 0, "MusicManager");
    qRegisterMetaType<MusicModel>();
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
