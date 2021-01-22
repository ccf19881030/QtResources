#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#define QRBUFSIZ 20480

typedef bool (*fpGetQrStr)(const char*, char*, int);

class QLibrary;
namespace Ui {
class CMainWindow;
}

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CMainWindow(QWidget *parent = 0);
    ~CMainWindow();

private:
    Ui::CMainWindow *ui;
    QString m_fileName;
    fpGetQrStr GetQrStr;

private slots:
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
