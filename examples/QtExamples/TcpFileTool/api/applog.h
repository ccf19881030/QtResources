#ifndef APPLOG_H
#define APPLOG_H

#include <QObject>

class AppLog : public QObject
{
    Q_OBJECT
public:
    explicit AppLog(QObject *parent = 0);

    void Load();

signals:

public slots:
};

#endif // APPLOG_H
