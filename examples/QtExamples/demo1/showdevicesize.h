#ifndef SHOWDEVICESIZE_H
#define SHOWDEVICESIZE_H

#include <QObject>
#include <QMutex>

class QTableWidget;
class QProcess;

class ShowDeviceSize : public QObject
{
    Q_OBJECT
public:
    explicit ShowDeviceSize(QObject *parent = 0);
    static ShowDeviceSize *Instance() {
        static QMutex mutex;
        if (!_instance) {
            QMutexLocker locker(&mutex);
            if (!_instance) {
                _instance = new ShowDeviceSize;
            }
        }
        return _instance;
    }

    void SetTableWidget(QTableWidget *tableWidget);
    void Load();

private:
    static ShowDeviceSize *_instance;
    QTableWidget *tableWidget;
    QProcess *process;

private slots:
    void ReadData();
    void CheckSize(QString result, QString name);
    void InsertSize(QString name, QString use, QString free, QString all, int percent);

signals:

public slots:
};

#endif // SHOWDEVICESIZE_H
