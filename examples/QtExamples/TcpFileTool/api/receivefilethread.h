#ifndef RECEIVEFILETHREAD_H
#define RECEIVEFILETHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QFile>

class ReceiveFileThread : public QThread
{
    Q_OBJECT
public:
    explicit ReceiveFileThread(int socketDescriptor, QObject *parent = 0);
    ~ReceiveFileThread();

    void proccessData(QByteArray &array);

protected:
    void run();

signals:
    void receiveFileName(QString name);
    void receiveFileSize(qint64 size);
    void message(QString msg);
    void receiveData(qint64 size);

private slots:
    void ReceiveData();
    void DisConnect();
    void displaySocketError(QAbstractSocket::SocketError);

private:
    QFile file;
    QString fileName;
    QTcpSocket *s;
    qint64 blockSize;
    qint64 blockNumber;

};

#endif // RECEIVEFILETHREAD_H
