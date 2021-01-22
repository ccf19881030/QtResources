/********************************************************************************
** Form generated from reading UI file 'frmmain.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMMAIN_H
#define UI_FRMMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmMain
{
public:
    QGroupBox *groupBox;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QSlider *horizontalSlider;
    QPushButton *btn5;
    QTextEdit *txt;
    QPushButton *btn6;
    QPushButton *btn4;
    QPushButton *btn7;
    QPushButton *btn8;
    QPushButton *btn21;
    QPushButton *btn22;
    QPushButton *btn24;
    QPushButton *btn23;
    QPushButton *btn31;
    QPushButton *btn32;
    QPushButton *btn33;
    QPushButton *btn34;
    QPushButton *btn35;
    QPushButton *btn36;

    void setupUi(QWidget *frmMain)
    {
        if (frmMain->objectName().isEmpty())
            frmMain->setObjectName(QStringLiteral("frmMain"));
        frmMain->resize(521, 452);
        frmMain->setStyleSheet(QStringLiteral(""));
        groupBox = new QGroupBox(frmMain);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 501, 431));
        btn1 = new QPushButton(groupBox);
        btn1->setObjectName(QStringLiteral("btn1"));
        btn1->setGeometry(QRect(300, 20, 91, 31));
        btn1->setCursor(QCursor(Qt::PointingHandCursor));
        btn1->setStyleSheet(QStringLiteral(""));
        btn2 = new QPushButton(groupBox);
        btn2->setObjectName(QStringLiteral("btn2"));
        btn2->setGeometry(QRect(300, 60, 91, 31));
        btn2->setCursor(QCursor(Qt::PointingHandCursor));
        btn3 = new QPushButton(groupBox);
        btn3->setObjectName(QStringLiteral("btn3"));
        btn3->setGeometry(QRect(300, 100, 91, 31));
        btn3->setCursor(QCursor(Qt::PointingHandCursor));
        horizontalSlider = new QSlider(groupBox);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(10, 390, 481, 31));
        horizontalSlider->setTracking(true);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setTickPosition(QSlider::TicksBothSides);
        btn5 = new QPushButton(groupBox);
        btn5->setObjectName(QStringLiteral("btn5"));
        btn5->setGeometry(QRect(300, 180, 91, 31));
        btn5->setCursor(QCursor(Qt::PointingHandCursor));
        txt = new QTextEdit(groupBox);
        txt->setObjectName(QStringLiteral("txt"));
        txt->setGeometry(QRect(10, 20, 281, 351));
        txt->setReadOnly(true);
        btn6 = new QPushButton(groupBox);
        btn6->setObjectName(QStringLiteral("btn6"));
        btn6->setGeometry(QRect(300, 220, 91, 31));
        btn6->setCursor(QCursor(Qt::PointingHandCursor));
        btn4 = new QPushButton(groupBox);
        btn4->setObjectName(QStringLiteral("btn4"));
        btn4->setGeometry(QRect(300, 140, 91, 31));
        btn4->setCursor(QCursor(Qt::PointingHandCursor));
        btn7 = new QPushButton(groupBox);
        btn7->setObjectName(QStringLiteral("btn7"));
        btn7->setGeometry(QRect(300, 260, 91, 31));
        btn7->setCursor(QCursor(Qt::PointingHandCursor));
        btn8 = new QPushButton(groupBox);
        btn8->setObjectName(QStringLiteral("btn8"));
        btn8->setGeometry(QRect(300, 300, 91, 31));
        btn8->setCursor(QCursor(Qt::PointingHandCursor));
        btn21 = new QPushButton(groupBox);
        btn21->setObjectName(QStringLiteral("btn21"));
        btn21->setGeometry(QRect(400, 20, 91, 31));
        btn21->setCursor(QCursor(Qt::PointingHandCursor));
        btn22 = new QPushButton(groupBox);
        btn22->setObjectName(QStringLiteral("btn22"));
        btn22->setGeometry(QRect(400, 60, 91, 31));
        btn22->setCursor(QCursor(Qt::PointingHandCursor));
        btn24 = new QPushButton(groupBox);
        btn24->setObjectName(QStringLiteral("btn24"));
        btn24->setGeometry(QRect(400, 140, 91, 31));
        btn24->setCursor(QCursor(Qt::PointingHandCursor));
        btn23 = new QPushButton(groupBox);
        btn23->setObjectName(QStringLiteral("btn23"));
        btn23->setGeometry(QRect(400, 100, 91, 31));
        btn23->setCursor(QCursor(Qt::PointingHandCursor));
        btn31 = new QPushButton(groupBox);
        btn31->setObjectName(QStringLiteral("btn31"));
        btn31->setGeometry(QRect(400, 180, 91, 31));
        btn31->setCursor(QCursor(Qt::PointingHandCursor));
        btn32 = new QPushButton(groupBox);
        btn32->setObjectName(QStringLiteral("btn32"));
        btn32->setGeometry(QRect(400, 220, 91, 31));
        btn32->setCursor(QCursor(Qt::PointingHandCursor));
        btn33 = new QPushButton(groupBox);
        btn33->setObjectName(QStringLiteral("btn33"));
        btn33->setEnabled(false);
        btn33->setGeometry(QRect(400, 260, 91, 31));
        btn33->setCursor(QCursor(Qt::PointingHandCursor));
        btn33->setCheckable(false);
        btn34 = new QPushButton(groupBox);
        btn34->setObjectName(QStringLiteral("btn34"));
        btn34->setEnabled(false);
        btn34->setGeometry(QRect(400, 300, 91, 31));
        btn34->setCursor(QCursor(Qt::PointingHandCursor));
        btn34->setCheckable(false);
        btn35 = new QPushButton(groupBox);
        btn35->setObjectName(QStringLiteral("btn35"));
        btn35->setEnabled(true);
        btn35->setGeometry(QRect(300, 340, 91, 31));
        btn35->setCursor(QCursor(Qt::PointingHandCursor));
        btn35->setCheckable(false);
        btn36 = new QPushButton(groupBox);
        btn36->setObjectName(QStringLiteral("btn36"));
        btn36->setEnabled(true);
        btn36->setGeometry(QRect(400, 340, 91, 31));
        btn36->setCursor(QCursor(Qt::PointingHandCursor));
        btn36->setCheckable(false);

        retranslateUi(frmMain);

        QMetaObject::connectSlotsByName(frmMain);
    } // setupUi

    void retranslateUi(QWidget *frmMain)
    {
        frmMain->setWindowTitle(QApplication::translate("frmMain", "\351\235\231\346\200\201\347\261\273\345\272\223\347\244\272\344\276\213(\344\275\234\350\200\205:\345\210\230\345\205\270\346\255\246 QQ:517216493)", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("frmMain", "\346\265\213\350\257\225\346\240\267\345\274\217", Q_NULLPTR));
        btn1->setText(QApplication::translate("frmMain", "\344\270\255\346\226\207\345\257\271\350\257\235\346\241\206", Q_NULLPTR));
        btn2->setText(QApplication::translate("frmMain", "\351\200\211\346\213\251\346\226\207\344\273\266", Q_NULLPTR));
        btn3->setText(QApplication::translate("frmMain", "\346\211\223\345\274\200\350\256\260\344\272\213\346\234\254", Q_NULLPTR));
        btn5->setText(QApplication::translate("frmMain", "\351\200\211\346\213\251\346\226\207\344\273\266\345\244\271", Q_NULLPTR));
        btn6->setText(QApplication::translate("frmMain", "\350\216\267\345\217\226\345\275\223\345\211\215\350\267\257\345\276\204", Q_NULLPTR));
        btn4->setText(QApplication::translate("frmMain", "\346\211\223\345\274\200\350\256\241\347\256\227\345\231\250", Q_NULLPTR));
        btn7->setText(QApplication::translate("frmMain", "\345\273\266\346\227\266\346\230\276\347\244\272", Q_NULLPTR));
        btn8->setText(QApplication::translate("frmMain", "\345\210\244\346\226\255\351\227\260\345\271\264", Q_NULLPTR));
        btn21->setText(QApplication::translate("frmMain", "\345\210\233\345\273\272\346\226\207\344\273\266", Q_NULLPTR));
        btn22->setText(QApplication::translate("frmMain", "\345\210\244\346\226\255\346\226\207\344\273\266\345\255\230\345\234\250", Q_NULLPTR));
        btn24->setText(QApplication::translate("frmMain", "\345\210\244\346\226\255\346\226\207\344\273\266\345\244\271\345\255\230\345\234\250", Q_NULLPTR));
        btn23->setText(QApplication::translate("frmMain", "\345\210\233\345\273\272\346\226\207\344\273\266\345\244\271", Q_NULLPTR));
        btn31->setText(QApplication::translate("frmMain", "\347\252\227\344\275\223\351\200\217\346\230\216", Q_NULLPTR));
        btn32->setText(QApplication::translate("frmMain", "\347\252\227\344\275\223\344\270\215\351\200\217\346\230\216", Q_NULLPTR));
        btn33->setText(QApplication::translate("frmMain", "\347\252\227\344\275\223\346\234\200\345\211\215\347\253\257", Q_NULLPTR));
        btn34->setText(QApplication::translate("frmMain", "\347\252\227\344\275\223\346\234\200\345\220\216\347\253\257", Q_NULLPTR));
        btn35->setText(QApplication::translate("frmMain", "\345\272\224\347\224\250\346\240\267\345\274\217", Q_NULLPTR));
        btn36->setText(QApplication::translate("frmMain", "\345\275\223\345\211\215\345\210\206\350\276\250\347\216\207", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmMain: public Ui_frmMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMMAIN_H
