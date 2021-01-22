#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include <turing.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<Turing>("io.qt.turing", 1, 0, "Turning");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
