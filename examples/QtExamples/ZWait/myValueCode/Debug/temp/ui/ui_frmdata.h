/********************************************************************************
** Form generated from reading UI file 'frmdata.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMDATA_H
#define UI_FRMDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frmData
{
public:
    QTableView *tableView;
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;
    QPushButton *btnOpen;
    QPushButton *btn4;
    QPushButton *btn5;

    void setupUi(QWidget *frmData)
    {
        if (frmData->objectName().isEmpty())
            frmData->setObjectName(QStringLiteral("frmData"));
        frmData->resize(458, 349);
        tableView = new QTableView(frmData);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(10, 10, 341, 331));
        btn1 = new QPushButton(frmData);
        btn1->setObjectName(QStringLiteral("btn1"));
        btn1->setGeometry(QRect(360, 50, 91, 31));
        btn1->setCursor(QCursor(Qt::PointingHandCursor));
        btn2 = new QPushButton(frmData);
        btn2->setObjectName(QStringLiteral("btn2"));
        btn2->setGeometry(QRect(360, 90, 91, 31));
        btn2->setCursor(QCursor(Qt::PointingHandCursor));
        btn3 = new QPushButton(frmData);
        btn3->setObjectName(QStringLiteral("btn3"));
        btn3->setGeometry(QRect(360, 130, 91, 31));
        btn3->setCursor(QCursor(Qt::PointingHandCursor));
        btnOpen = new QPushButton(frmData);
        btnOpen->setObjectName(QStringLiteral("btnOpen"));
        btnOpen->setGeometry(QRect(360, 10, 91, 31));
        btnOpen->setCursor(QCursor(Qt::PointingHandCursor));
        btn4 = new QPushButton(frmData);
        btn4->setObjectName(QStringLiteral("btn4"));
        btn4->setGeometry(QRect(360, 170, 91, 31));
        btn4->setCursor(QCursor(Qt::PointingHandCursor));
        btn5 = new QPushButton(frmData);
        btn5->setObjectName(QStringLiteral("btn5"));
        btn5->setGeometry(QRect(360, 210, 91, 31));
        btn5->setCursor(QCursor(Qt::PointingHandCursor));

        retranslateUi(frmData);

        QMetaObject::connectSlotsByName(frmData);
    } // setupUi

    void retranslateUi(QWidget *frmData)
    {
        frmData->setWindowTitle(QApplication::translate("frmData", "\346\225\260\346\215\256\345\244\204\347\220\206\346\265\213\350\257\225", Q_NULLPTR));
        btn1->setText(QApplication::translate("frmData", "\345\212\240\350\275\275\346\225\260\346\215\256", Q_NULLPTR));
        btn2->setText(QApplication::translate("frmData", "\347\273\221\345\256\232\344\270\255\346\226\207\345\210\227\345\220\215", Q_NULLPTR));
        btn3->setText(QApplication::translate("frmData", "\346\211\271\351\207\217\346\211\247\350\241\214SQL", Q_NULLPTR));
        btnOpen->setText(QApplication::translate("frmData", "\346\211\223\345\274\200\346\225\260\346\215\256\345\272\223", Q_NULLPTR));
        btn4->setText(QApplication::translate("frmData", "\345\215\225\344\270\252\346\211\247\350\241\214SQL", Q_NULLPTR));
        btn5->setText(QApplication::translate("frmData", "\346\237\245\350\257\242\350\256\260\345\275\225", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class frmData: public Ui_frmData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMDATA_H
