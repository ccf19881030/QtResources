#ifndef MODELCREATOR_H
#define MODELCREATOR_H


#include <QObject>
#include <QFileInfoList>

class MusicModel;

class ModelCreator
{
public:
    ModelCreator();
    static void exportFromLocal(QList<MusicModel*> &musicList, const QString &path);
    static void exportFromSearch(QList<MusicModel*> &musicList, QByteArray &js);
    static void exportFromTop(QList<MusicModel*> &musicList, QByteArray &js);
};


#endif // MODELCREATOR_H
