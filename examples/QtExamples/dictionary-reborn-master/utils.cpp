#include "utils.h"
#include <QFile>

QString Utils::getQssFileContent(const QString &fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);

    return file.readAll();
}
