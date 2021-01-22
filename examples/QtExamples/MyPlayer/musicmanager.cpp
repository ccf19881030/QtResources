#include "musicmanager.h"
#include "musicmodel.h"
#include "modelcreator.h"
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QCoreApplication>
#include <QFile>
#include <QTimer>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSignalMapper>


class MusicManagerPrivate
{
public:
    MusicManagerPrivate();
    QNetworkAccessManager *nam;
    QSignalMapper *mapper;
    QList<MusicModel*> musicList;
    QQmlListProperty<MusicModel> *listPro;
    QTimer delayedRequestTimer;
    QString localPath;
    int topX;//榜行榜 id 3=欧美 5=内地 6=港台 16=韩国 17=日本 18=民谣 19=摇滚 23=销量 26=热歌
    MusicManager::RequestType type;//0=排行榜 1=搜索
    QString keyword;
    bool isStart;
};

MusicManagerPrivate::MusicManagerPrivate() :
    nam(NULL),
    listPro(NULL),
    topX(5),
    type(MusicManager::Top),
    isStart(false),
    mapper(0)
{
    //delay 500ms to request
    delayedRequestTimer.setSingleShot(true);
    delayedRequestTimer.setInterval(500);

}


static void appendFunc(QQmlListProperty<MusicModel> *ptr, MusicModel *model){
    Q_UNUSED(ptr)
    Q_UNUSED(model)
}

static int countFunc(QQmlListProperty<MusicModel> *ptr){
    MusicManagerPrivate *d = static_cast<MusicManagerPrivate*>(ptr->data);
    return d->musicList.size();
}

static MusicModel* atFunc(QQmlListProperty<MusicModel> *ptr, int index){
    MusicManagerPrivate *d = static_cast<MusicManagerPrivate*>(ptr->data);
    return d->musicList.at(index);
}

static void clearFunc(QQmlListProperty<MusicModel> *ptr){
    MusicManagerPrivate *d = static_cast<MusicManagerPrivate*>(ptr->data);
    d->musicList.clear();
}

MusicManager::MusicManager(QObject *parent) :
    QObject(parent),
    d(new MusicManagerPrivate)
{
    d->listPro = new QQmlListProperty<MusicModel>(this, d,
                                                  appendFunc,
                                                  countFunc,
                                                  atFunc,
                                                  clearFunc);

    d->mapper = new QSignalMapper(this);
    connect(d->mapper, SIGNAL(mapped(QObject*)), this, SLOT(readData(QObject*)));
    d->nam = new QNetworkAccessManager(this);
    connect(&d->delayedRequestTimer, SIGNAL(timeout()),
            this, SLOT(request()));
}

QQmlListProperty<MusicModel> MusicManager::musicModelList() const
{
    return *d->listPro;
}

int MusicManager::musicCount() const
{
    return d->musicList.size();
}

QString MusicManager::localPath() const
{
    return d->localPath;
}

void MusicManager::setLocalPath(const QString &val)
{
    if(!d->musicList.size() > 0){
        qDeleteAll(d->musicList);
        d->musicList.clear();
    }
    d->localPath = val;
    ModelCreator::exportFromLocal(d->musicList, d->localPath);
    emit finished();
}


int MusicManager::topX() const
{
    return d->topX;
}

void MusicManager::setTopX(const int &val)
{
    d->topX = val;
    emit topXChanged();
}

MusicManager::RequestType MusicManager::type() const
{
    return d->type;
}


void MusicManager::setType(const RequestType &val)
{
    d->type = val;
    emit typeChanged();
}

QString MusicManager::keyword() const
{
    return d->keyword;
}

void MusicManager::setKeyword(const QString &val)
{

    d->keyword = val.trimmed();
    if(d->keyword.isEmpty())
        return;
    emit keywordChanged();
}

bool MusicManager::startRequest() const
{
    return d->isStart;
}

void MusicManager::setStartRequest(const bool &val)
{
    d->isStart = val;
    if(val)
        d->delayedRequestTimer.start();
   // qDebug() << "setStartRequest " << val;
}

void MusicManager::testJson()
{
    //    QFile file(qApp->applicationDirPath() + tr("/myjson.json"));
    //    if(!file.open(QIODevice::ReadOnly)){
    //        qDebug() << "file open error!";
    //        return;
    //    }
    //    parseJson(file.readAll());
    //    file.close();
    //    emit finished();
    //    for(int i = 0; i < d->musicList.size(); i++){
    //        qDebug() << d->musicList.at(i)->songname();
    //        qDebug() << d->musicList.at(i)->seconds();
    //        qDebug() << d->musicList.at(i)->albummid();
    //        qDebug() << d->musicList.at(i)->songid();
    //        qDebug() << d->musicList.at(i)->singerid();
    //        qDebug() << d->musicList.at(i)->albumpicBig();
    //        qDebug() << d->musicList.at(i)->albumpicSmall();
    //        qDebug() << d->musicList.at(i)->downUrl();
    //        qDebug() << d->musicList.at(i)->url();
    //        qDebug() << d->musicList.at(i)->singername();
    //        qDebug() << d->musicList.at(i)->albumid();
    //    }
}


void MusicManager::request()
{

   // qDebug() << "request()";

    QString urlString("http://ali-qqmusic.showapi.com/");
    QUrl url;
    QUrlQuery query;
    switch(d->type){
    case Top:     //top榜
        urlString += tr("top");
        url.setUrl(urlString);
        query.addQueryItem(tr("topid"), QString::number(d->topX));
        url.setQuery(query);
        break;
    case Search:
        urlString += tr("search");
        url.setUrl(urlString);
        query.addQueryItem(tr("keyword"),d->keyword);
        query.addQueryItem(tr("page"), QString::number(10)); //每页20条，每次搜索获取100条
        url.setQuery(query);
        break;
    default:
        return;
    }

    QNetworkRequest nr(url);
    nr.setRawHeader(QByteArray("Authorization"), QByteArray("APPCODE 5a162e10c0704db7bb29aa08b63e6e99"));
    QNetworkReply *reply = d->nam->get(nr);
    d->mapper->setMapping(reply, reply);
    connect(reply, SIGNAL(finished()),
            d->mapper, SLOT(map()));
}

void MusicManager::readData(QObject *reply)
{
    if(d->musicList.size() > 0){
        qDeleteAll(d->musicList);
        d->musicList.clear();
    }
    QNetworkReply *nReply = qobject_cast<QNetworkReply*>(reply);
    if(!nReply)
        return;

    QByteArray data(nReply->readAll());
  //  qDebug() << "readData" << data.size();
    switch(d->type){
    case Top:     //top
        ModelCreator::exportFromTop(d->musicList, data);
        break;
    case Search:     //search
        ModelCreator::exportFromSearch(d->musicList, data);
        break;
    default:
        return;
    }
    nReply->deleteLater();
    emit finished();
}

