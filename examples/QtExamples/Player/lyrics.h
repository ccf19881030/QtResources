#ifndef LYRICS_H
#define LYRICS_H

#include <QObject>
#include <QString>
#include <QList>
#include <QStringList>

class Lyrics : public QObject
{
    Q_OBJECT
public:
    explicit Lyrics(QObject *parent = 0);
    ~Lyrics();
    Q_INVOKABLE QList<QString> getLyric(QString url);
    Q_INVOKABLE QList<double> getTime();

signals:

public slots:

private:
    QList<double> time;
    QList<QString> list;
};

#endif // LYRICS_H
