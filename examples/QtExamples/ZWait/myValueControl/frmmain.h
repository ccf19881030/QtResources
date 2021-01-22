#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QWidget>

#include "mygauge1.h"
#include "mygauge2.h"
#include "mygauge3.h"
#include "mygauge4.h"
#include "mygauge5.h"
#include "mygauge6.h"
#include "mygauge7.h"
#include "myprogressbar.h"
#include "mybattery.h"
#include "mycoolbar.h"
#include "myindicator.h"
#include "myVolume.h"

#include "mychart1.h"
#include "myflashlist.h"
#include "mybuttonboard.h"
#include "mysliderbutton.h"
#include "myPhotoView.h"
#include "myaroundcircle.h"
#include "myprogressbar1.h"
#include "mynewled.h"
#include "mywave.h"
#include "mywave1.h"
#include "mywave2.h"

namespace Ui {
    class frmMain;
}

class frmMain : public QWidget
{
    Q_OBJECT

public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();

private:
    Ui::frmMain *ui;
    QVBoxLayout *mainLayout1;
    QHBoxLayout *layout1;

    QVBoxLayout *mainLayout2;
    QHBoxLayout *layout2;

    myGauge1 *gauge1;
    myGauge2 *gauge2;
    myGauge3 *gauge31;
    myGauge3 *gauge32;
    myGauge3 *gauge33;
    myGauge4 *gauge41;
    myGauge4 *gauge42;
    myGauge4 *gauge43;
    myGauge5 *gauge5;
    myGauge6 *gauge61;
    myGauge6 *gauge62;
    myGauge6 *gauge63;
    myGauge7 *gauge71;
    myGauge7 *gauge72;
    myGauge7 *gauge73;

    myProgressBar *myprogressbar1;
    myProgressBar *myprogressbar2;
    myProgressBar *myprogressbar3;

    myBattery *mybattery1;
    myBattery *mybattery2;
    myBattery *mybattery3;
    myBattery *mybattery4;

    myCoolBar *mycoolbar;

    myIndicator *myindicator1;
    myIndicator *myindicator2;
    myIndicator *myindicator3;
    myIndicator *myindicator4;
    myIndicator *myindicator5;

    myVolume *myvolume1;
    myVolume *myvolume2;
    myVolume *myvolume3;
    myVolume *myvolume4;
    myVolume *myvolume5;

    QTimer *updateTimer1;
    QTimer *updateTimer2;
    QTimer *updateTimer4;
    QTimer *updateTimer5;
    QTimer *updateTimer6;
    QTimer *updateTimer7;
    QTimer *updateTimer8;

    QTimer *updateTimer10;
    QTimer *updateTimer11;


    myChart1 *mychart1;
    myFlashList *myflashlist;
    myButtonBoard *mybuttonboard;
    mySliderButton *mysliderbutton1;
    mySliderButton *mysliderbutton2;
    mySliderButton *mysliderbutton3;

    myPhotoView *myphotoview;
    myAroundCircle *myaroundcircle;

    myProgressBar1 *myprogressbar11;
    myProgressBar1 *myprogressbar12;
    myProgressBar1 *myprogressbar13;

    myNewLed *mynewled;

    myWave *mywave;

    QVector<myWave1*> mywave1;

    QVector<myWave2*> mywave2;

    QTimer *updateTimer21;
    QTimer *updateTimer27;
    QTimer *updateTimer28;
    QTimer *updateTimer29;
    QTimer *updateTimer30;
    QTimer *updateTimer31;


private slots:
    void on_btnWave2_clicked();
    void on_btnWave1_clicked();
    void on_btnWave_clicked();
    void on_btnNewLed_clicked();
    void on_btnProgressBar1_clicked();
    void on_btnAroundCircle_clicked();
    void on_btnPhotoView_clicked();
    void on_btnSliderButton_clicked();
    void on_btnButtonBoard_clicked();
    void on_btnFlashList_clicked();
    void on_btnChart1_clicked();
    void on_btnVolume_clicked();
    void on_btnIndicator_clicked();
    void on_btnCoolBar_clicked();
    void on_btnBattery_clicked();
    void on_btnGauge7_clicked();
    void on_btnProgressBar_clicked();
    void on_btnGauge6_clicked();
    void on_btnGauge5_clicked();
    void on_btnGauge4_clicked();
    void on_btnGauge3_clicked();
    void on_btnGauge2_clicked();
    void on_btnGauge1_clicked();


    void UpdateData1();
    void UpdateData2();
    void UpdateData3(qreal value);
    void UpdateData4();
    void UpdateData5();
    void UpdateData6();
    void UpdateData7();
    void UpdateData8();
    void UpdateData9(int value);
    void UpdateData10();
    void UpdateData11();

    void InitTab1();
    void ChangeVisibleTab1(bool b);
    void InitTab2();
    void ChangeVisibleTab2(bool b);
    void TabChange(int index);


    void UpdateData21();
    void UpdateData22(QString txt);
    void UpdateData23(QString txt);
    void UpdateData24(QString txt);
    void UpdateData27();
    void UpdateData28();
    void UpdateData29();
    void UpdateData30();
    void UpdateData31();
};

#endif // FRMMAIN_H
