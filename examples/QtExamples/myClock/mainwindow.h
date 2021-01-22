#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QMovie>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QWindow>
#include "MyFile.h"

class QLineEdit;
class QVBoxLayout;
class MyDialog;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWidget * cenWidget;
    QSystemTrayIcon *myTrayIcon;
    QMenu *myMenu;
    QAction *quitAction;
    QAction *setTimeAction;
    QAction *minAction;
    QAction *maxAction;
    QTimer * timer;
    QLabel * label1;
    QLabel * label2;
    QLabel * label3;
    QLabel * label4;
    QLabel * label5;
    QLabel * label6;
    QLabel * labelDot1;
    QLabel * labelDot2;
    QStringList listPath;
    bool shouldMove;
    QPoint formerMainPos;
    QPoint formerMousePos;
    int destopWidth;
    int destopHeight;
    int widgetWidth;
    int widgetHeight;
    QVariantList vList;
    QVariantMap vMap;
    QVBoxLayout * vLayout;
    QLabel * labelTip;
    double clockFlag;
    MyDialog * setDialog;
    MyFile * m_myFile;
    QLineEdit * time1;
    QLineEdit * tips1;
    QLineEdit * time2;
    QLineEdit * tips2;
private:
    void intiTime();
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void checkClock(QString str);
public slots:
    void updateTime();
    void exit();
    void setTime();
    void setMinWidget();
    void setMaxWidget();
    void addClock();
    void saveClockTime1(QString str);
    void saveClockTime2(QString str);
    void saveClockTips1(QString str);
    void saveClockTips2(QString str);
    void hideLabelTip();
    void onGetReadFile(QVariantList);
    void onGetWriteResult(bool);
};

#endif // MAINWINDOW_H
