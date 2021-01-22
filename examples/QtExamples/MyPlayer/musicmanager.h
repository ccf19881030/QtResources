#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H


#include <QObject>

#include <QObject>
#include <QQmlListProperty>


class MusicModel;
class MusicManagerPrivate;
class QNetworkReply;

class MusicManager : public QObject
{
    Q_OBJECT
    Q_ENUMS(RequestType)
    Q_PROPERTY(QQmlListProperty<MusicModel> musicModelList READ musicModelList NOTIFY musicModelListChanged)
    Q_PROPERTY(int musicCount READ musicCount NOTIFY musicCountChanged)
    Q_PROPERTY(QString localPath READ localPath WRITE setLocalPath)
    Q_PROPERTY(int topX READ topX WRITE setTopX NOTIFY topXChanged)
    Q_PROPERTY(RequestType type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString keyword READ keyword WRITE setKeyword NOTIFY keywordChanged)
    Q_PROPERTY(bool startRequest READ startRequest WRITE setStartRequest)
public:
    MusicManager(QObject *parent = 0);
    //请求类型
    enum RequestType{
        Top, Search
    };
    QQmlListProperty<MusicModel> musicModelList() const;
    int musicCount() const;
    QString localPath() const;
    void setLocalPath(const QString &val);
    int topX() const;
    void setTopX(const int &val);
    RequestType type() const;
    void setType(const RequestType &val);
    QString keyword() const;
    void setKeyword(const QString &val);
    bool startRequest() const;
    void setStartRequest(const bool &val);
    void testJson();

signals:
    void musicModelListChanged();
    void finished();
    void musicCountChanged();
    void topXChanged();
    void typeChanged();
    void keywordChanged();
public slots:
    void request();
    void readData(QObject *reply);
private:
    MusicManagerPrivate *d;

};

#endif // MUSICMANAGER_H
