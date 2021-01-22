#include "musicmodel.h"
#include "modelcreator.h"
#include <QDir>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

ModelCreator::ModelCreator()
{

}

void ModelCreator::exportFromLocal(QList<MusicModel *> &musicList,const QString &path)
{
    QUrl url(path);
    if(url.isLocalFile()){
        QDir dir(url.toLocalFile());
        QStringList filters;
        filters << "*.mp3" << "*.wav";

        QFileInfoList fileList;
        fileList = dir.entryInfoList(filters, QDir::Files);
        foreach(QFileInfo info, fileList){
            MusicModel *song = new MusicModel();
            song->setSongname(info.fileName());
            song->setUrl(info.absoluteFilePath());
            musicList << song;
        }
    }

}

void ModelCreator::exportFromSearch(QList<MusicModel *> &musicList, QByteArray &js)
{
    QJsonDocument document = QJsonDocument::fromJson(js);
    if(document.isObject()){
        QJsonObject obj = document.object();
        QJsonValue val = obj.value(QLatin1String("showapi_res_body"));
        obj = val.toObject();
        val = obj.value(QLatin1String("pagebean"));
        obj = val.toObject();
        val = obj.value(QLatin1String("contentlist"));
        QJsonArray songlist = val.toArray();
        QJsonArray::ConstIterator it = songlist.constBegin();
        for(; it != songlist.end(); it++){
            val = *it;
            obj = val.toObject();
            MusicModel *song = new MusicModel();
            if(obj.contains(QLatin1String("albummid"))){
                val = obj.value(QLatin1String("albummid"));
                song->setAlbummid(val.toString());
            }
            if(obj.contains(QLatin1String("singerid"))){
                val = obj.value(QLatin1String("singerid"));
                song->setSingerid(val.toInt());
            }
            if(obj.contains(QLatin1String("albumpic_big"))){
                val = obj.value(QLatin1String("albumpic_big"));
                song->setalbumpicBig(val.toString());
            }
            if(obj.contains(QLatin1String("albumpic_small"))){
                val = obj.value(QLatin1String("albumpic_small"));
                song->setalbumpicSmall(val.toString());
            }
            if(obj.contains(QLatin1String("downUrl"))){
                val = obj.value(QLatin1String("downUrl"));
                song->setDownUrl(val.toString());
            }
            if(obj.contains(QLatin1String("m4a"))){
                val = obj.value(QLatin1String("m4a"));
                song->setUrl(val.toString());
            }
            if(obj.contains(QLatin1String("singername"))){
                val = obj.value(QLatin1String("singername"));
                song->setSingername(val.toString());
            }
            if(obj.contains(QLatin1String("songname"))){
                val = obj.value(QLatin1String("songname"));
                song->setSongname(val.toString());
            }
            if(obj.contains(QLatin1String("albumid"))){
                val = obj.value(QLatin1String("albumid"));
                song->setAlbumid(val.toInt());
            }
            if(obj.contains(QLatin1String("albumname"))){
                val = obj.value(QLatin1String("albumname"));
                song->setAlbumname(val.toString());
            }
            musicList << song;
        }
    }
}

void ModelCreator::exportFromTop(QList<MusicModel *> &musicList, QByteArray &js)
{
    QJsonDocument document = QJsonDocument::fromJson(js);
    if(document.isObject()){
        QJsonObject obj = document.object();
        QJsonValue val = obj.value(QLatin1String("showapi_res_body"));
        obj = val.toObject();
        val = obj.value(QLatin1String("pagebean"));
        obj = val.toObject();
        val = obj.value(QLatin1String("songlist"));
        QJsonArray songlist = val.toArray();
        QJsonArray::ConstIterator it = songlist.constBegin();
        for(; it != songlist.end(); it++){
            val = *it;
            obj = val.toObject();
            MusicModel *song = new MusicModel();
                if(obj.contains(QLatin1String("songname"))){
                    val = obj.value(QLatin1String("songname"));
                    song->setSongname(val.toString());
                }
            if(obj.contains(QLatin1String("seconds"))){
                val = obj.value(QLatin1String("seconds"));
                song->setSeconds(val.toInt());
            }
            if(obj.contains(QLatin1String("albummid"))){
                val = obj.value(QLatin1String("albummid"));
                song->setAlbummid(val.toString());
            }
            if(obj.contains(QLatin1String("songid"))){
                val = obj.value(QLatin1String("songid"));
                song->setSongid(val.toInt());
            }

            if(obj.contains(QLatin1String("singerid"))){
                val = obj.value(QLatin1String("singerid"));
                song->setSingerid(val.toInt());
            }
            if(obj.contains(QLatin1String("albumpic_big"))){
                val = obj.value(QLatin1String("albumpic_big"));
                song->setalbumpicBig(val.toString());
            }
            if(obj.contains(QLatin1String("albumpic_small"))){
                val = obj.value(QLatin1String("albumpic_small"));
                song->setalbumpicSmall(val.toString());
            }
            if(obj.contains(QLatin1String("downUrl"))){
                val = obj.value(QLatin1String("downUrl"));
                song->setDownUrl(val.toString());
            }
            if(obj.contains(QLatin1String("url"))){
                val = obj.value(QLatin1String("url"));
                song->setUrl(val.toString());
            }
            if(obj.contains(QLatin1String("singername"))){
                val = obj.value(QLatin1String("singername"));
                song->setSingername(val.toString());
            }
            if(obj.contains(QLatin1String("albumid"))){
                val = obj.value(QLatin1String("albumid"));
                song->setAlbumid(val.toInt());
            }
            musicList << song;

        }
    }
}
