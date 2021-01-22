#ifndef MUSICMODEL_H
#define MUSICMODEL_H

#include <QObject>

class MusicModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString songname READ songname WRITE setSongname NOTIFY songnameChanged)
    Q_PROPERTY(int seconds READ seconds WRITE setSeconds NOTIFY secondsChanged)
    Q_PROPERTY(QString albummid READ albummid WRITE setAlbummid NOTIFY albummidChanged)
    Q_PROPERTY(int songid READ songid WRITE setSongid NOTIFY songidChanged)
    Q_PROPERTY(int singerid READ singerid WRITE setSingerid NOTIFY singeridChanged)
    Q_PROPERTY(QString albumpicBig READ albumpicBig WRITE setalbumpicBig NOTIFY albumpicBigChanged)
    Q_PROPERTY(QString albumpicSmall READ albumpicSmall WRITE setalbumpicSmall NOTIFY albumpicSmallChanged)
    Q_PROPERTY(QString downUrl READ downUrl WRITE setDownUrl NOTIFY downUrlChanged)
    Q_PROPERTY(QString url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QString singername READ singername WRITE setSingername NOTIFY singernameChanged)
    Q_PROPERTY(int albumid READ albumid WRITE setAlbumid NOTIFY albumidChanged)
    Q_PROPERTY(QString albumname READ albumname WRITE setAlbumname NOTIFY albumnameChanged)
public:
    MusicModel(QObject *parent = 0);
    MusicModel(const MusicModel &other);
    QString songname() const;
    void setSongname(const QString &val);
    int seconds() const;
    void setSeconds(const int &val);
    QString albummid() const;
    void setAlbummid(const QString &val);
    int songid() const;
    void setSongid(const int &val);
    int singerid() const;
    void setSingerid(const int &val);
    QString albumpicBig() const;
    void setalbumpicBig(const QString &val);
    QString albumpicSmall() const;
    void setalbumpicSmall(const QString &val);
    QString downUrl() const;
    void setDownUrl(const QString &val);
    QString url() const;
    void setUrl(const QString &val);
    QString singername() const;
    void setSingername(const QString &val);
    int albumid() const;
    void setAlbumid(const int &val);
    QString albumname() const;
    void setAlbumname(const QString &val);
signals:
    void songnameChanged();
    void secondsChanged();
    void albummidChanged();
    void songidChanged();
    void singeridChanged();
    void albumpicBigChanged();
    void albumpicSmallChanged();
    void downUrlChanged();
    void urlChanged();
    void singernameChanged();
    void albumidChanged();
    void albumnameChanged();
private:
    QString m_songname;
    int m_seconds;
    QString m_albummid;
    int m_songid;
    int m_singerid;
    QString m_albumpic_big;
    QString m_albumpic_small;
    QString m_downUrl;
    QString m_url;
    QString m_singername;
    int m_albumid;
    QString m_albumname;
};

Q_DECLARE_METATYPE(MusicModel)


#endif // MUSICMODEL_H
