#include "utils.h"
#include <QFile>

QString Utils::getQssContent(const QString &path)
{
    QFile file(path);
    QString qss;

    file.open(QIODevice::ReadOnly);
    qss = file.readAll();

    file.close();

    return qss;
}
