#ifndef MYFILE_H
#define MYFILE_H
#include <QThread>
#include <QSettings>
class MyFile : public QThread
{
    Q_OBJECT
public:
    MyFile(QObject * parent=0);
    void run();
    void readFile(QString path);
    void writeFile(QString path,QVariantList data);
signals:
    void getReadFile(QVariantList data);
    void getWriteResult(bool result);
private:
    bool m_running;
    int m_type;   //0 read 1 write
    QString m_path;
    QVariantList m_data;
private:
    void read();
    void write();
};

#endif // MYFILE_H
