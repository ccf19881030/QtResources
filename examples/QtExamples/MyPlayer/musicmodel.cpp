#include "musicmodel.h"

MusicModel::MusicModel(QObject *parent) :
    QObject(parent),
    m_seconds(0)
{

}

MusicModel::MusicModel(const MusicModel &other) :
    QObject(0)
{
     m_songname = other.m_songname;
     m_seconds = other.m_seconds;
     m_albummid = other.m_albummid;
     m_songid = other.m_songid;
     m_singerid = other.m_singerid;
     m_albumpic_big = other.m_albumpic_big;
     m_albumpic_small = other.m_albumpic_small;
     m_downUrl = other.m_downUrl;
     m_url = other.m_url;
     m_singername = other.m_singername;
     m_albumid = other.m_albumid;
}

QString MusicModel::songname() const
{
    return m_songname;
}

void MusicModel::setSongname(const QString &val)
{
    m_songname = val;
}

int MusicModel::seconds() const
{
    return m_seconds;
}

void MusicModel::setSeconds(const int &val)
{
    m_seconds = val;
}

QString MusicModel::albummid() const
{
    return m_albummid;
}

void MusicModel::setAlbummid(const QString &val)
{
    m_albummid = val;
}

int MusicModel::songid() const
{
    return m_songid;
}

void MusicModel::setSongid(const int &val)
{
    m_songid = val;
}

int MusicModel::singerid() const
{
    return m_singerid;
}

void MusicModel::setSingerid(const int &val)
{
    m_singerid = val;
}

QString MusicModel::albumpicBig() const
{
    return m_albumpic_big;
}

void MusicModel::setalbumpicBig(const QString &val)
{
    m_albumpic_big = val;
}

QString MusicModel::albumpicSmall() const
{
    return m_albumpic_small;
}

void MusicModel::setalbumpicSmall(const QString &val)
{
    m_albumpic_small = val;
}

QString MusicModel::downUrl() const
{
    return m_downUrl;
}

void MusicModel::setDownUrl(const QString &val)
{
    m_downUrl = val;
}

QString MusicModel::url() const
{
    return m_url;
}

void MusicModel::setUrl(const QString &val)
{
    m_url = val;
}

QString MusicModel::singername() const
{
    return m_singername;
}

void MusicModel::setSingername(const QString &val)
{
    m_singername = val;
}

int MusicModel::albumid() const
{
    return m_albumid;
}

void MusicModel::setAlbumid(const int &val)
{
    m_albumid = val;
}

QString MusicModel::albumname() const
{
    return m_albumname;
}

void MusicModel::setAlbumname(const QString &val)
{
    m_albumname = val;
}
