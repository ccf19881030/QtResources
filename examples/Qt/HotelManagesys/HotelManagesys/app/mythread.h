#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <QLabel>
#include <QTimer>

class Mythread : public QThread
{
    Q_OBJECT
public:
    explicit Mythread(QObject *parent = 0);

    void SetCurrentTime(QLabel*label);
public slots:
    void showTimesslot();

protected:
    void run();
private:
    QTimer *timer;
    QLabel *curlabel;
    
};

#endif // MYTHREAD_H
