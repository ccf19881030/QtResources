#include "musiclist.h"
#include <QFile>
#include <QDir>
#include <QtMath>
#include <QDebug>

MusicList::MusicList()
    : m_count(0)
{

}

MusicList::~MusicList()
{

}

int MusicList::musicCount()
{
    return m_count;
}

void MusicList::setPath(QString path)
{

    m_dir.setPath(path);

    QStringList filters;
    filters << tr("*.mp3") << tr("*.wav");

    m_fileInfoList = m_dir.entryInfoList(filters,QDir::Files);

    m_count = m_fileInfoList.count();
}

QString MusicList::getPath()
{
    return m_dir.path();
}

QString MusicList::getFileName(const int index)
{
    if(index > -1 && index < m_count)
    {
        QString fn = m_fileInfoList.at(index).fileName();
        QString result;
         result = fn.mid(fn.indexOf("-") + 1, fn.lastIndexOf(".") - fn.indexOf("-") - 1);
         result = result.trimmed();
        if(result == "")
            result = fn.mid(0, fn.lastIndexOf("."));
        return result;
    }
    return QString();
}

QString MusicList::getFilePath(const int index)
{
    if(index > -1 && index < m_count)
    {
        return m_fileInfoList.at(index).absoluteFilePath();
    }
    return QString();
}

int MusicList::getFileIndex(const QString file)
{

    for(int i = 0; i < m_fileInfoList.count(); i++)
    {
        QString fn = m_fileInfoList.at(i).fileName();
        QString fnPre = fn.mid(0, fn.lastIndexOf("."));
        qDebug()<< fnPre;

        if(fnPre == file)
            return i;
    }
    return -1;
}

QString MusicList::getSinger(const int index)
{
    if(index > -1 && index < m_count)
    {
        QString fn = m_fileInfoList.at(index).fileName();
        QString result = fn.mid(0, fn.indexOf("-") - 1).trimmed();
        return result;
    }
    return QString();
}

QString MusicList::getSize(const int index)
{
    if(index > -1 && index < m_count)
    {
        int s = m_fileInfoList.at(index).size();
        QString result;
        if( s < 1024)
            result = tr("%1 Bytes").arg(s);
        else if (  (s / 1024.0) < 1024.0){
            result = tr("%1 KB").arg(qFloor(s / 1024.0 * 100) /100.0);
        }
        else if( (s / (1024.0 * 1024.0) ) < 1024.0)
            result = tr("%1 MB").arg( qFloor(s / (1024.0 * 1024.0) * 100) / 100.0);
        return result;
    }

    return 0;
}

