#ifndef MUSICLIST_H
#define MUSICLIST_H

#include <QStringList>
#include <QObject>
#include <QFileInfoList>
#include <QDir>
#include <QString>

class MusicList : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int musicCount READ musicCount)
public:
    MusicList();
    ~MusicList();

    Q_INVOKABLE int musicCount();
    Q_INVOKABLE void setPath(const QString path);
    Q_INVOKABLE QString getPath();
    Q_INVOKABLE QString getFileName(const int index);
    Q_INVOKABLE QString getFilePath(const int index);
    Q_INVOKABLE int getFileIndex(const QString file);
    Q_INVOKABLE QString getSinger(const int index);
    Q_INVOKABLE QString getSize(const int index);


protected:
    int m_count;
    QDir m_dir;
    QFileInfoList m_fileInfoList;
};

#endif // MUSICLIST_H
