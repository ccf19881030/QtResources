/********************************************************************************
** Form generated from reading UI file 'uidemo10.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UIDEMO10_H
#define UI_UIDEMO10_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_UIDemo10
{
public:
    QGridLayout *gridLayout;
    QToolButton *btn1;
    QToolButton *btn2;
    QToolButton *btn3;
    QToolButton *btn4;
    QToolButton *btn5;
    QToolButton *btn6;

    void setupUi(QDialog *UIDemo10)
    {
        if (UIDemo10->objectName().isEmpty())
            UIDemo10->setObjectName(QStringLiteral("UIDemo10"));
        UIDemo10->resize(644, 342);
        gridLayout = new QGridLayout(UIDemo10);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        btn1 = new QToolButton(UIDemo10);
        btn1->setObjectName(QStringLiteral("btn1"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn1->sizePolicy().hasHeightForWidth());
        btn1->setSizePolicy(sizePolicy);
        btn1->setStyleSheet(QStringLiteral(""));
        btn1->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout->addWidget(btn1, 0, 0, 1, 1);

        btn2 = new QToolButton(UIDemo10);
        btn2->setObjectName(QStringLiteral("btn2"));
        sizePolicy.setHeightForWidth(btn2->sizePolicy().hasHeightForWidth());
        btn2->setSizePolicy(sizePolicy);
        btn2->setStyleSheet(QStringLiteral(""));
        btn2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout->addWidget(btn2, 0, 1, 1, 1);

        btn3 = new QToolButton(UIDemo10);
        btn3->setObjectName(QStringLiteral("btn3"));
        sizePolicy.setHeightForWidth(btn3->sizePolicy().hasHeightForWidth());
        btn3->setSizePolicy(sizePolicy);
        btn3->setStyleSheet(QStringLiteral(""));
        btn3->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout->addWidget(btn3, 0, 2, 1, 1);

        btn4 = new QToolButton(UIDemo10);
        btn4->setObjectName(QStringLiteral("btn4"));
        sizePolicy.setHeightForWidth(btn4->sizePolicy().hasHeightForWidth());
        btn4->setSizePolicy(sizePolicy);
        btn4->setStyleSheet(QStringLiteral(""));
        btn4->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout->addWidget(btn4, 1, 0, 1, 1);

        btn5 = new QToolButton(UIDemo10);
        btn5->setObjectName(QStringLiteral("btn5"));
        sizePolicy.setHeightForWidth(btn5->sizePolicy().hasHeightForWidth());
        btn5->setSizePolicy(sizePolicy);
        btn5->setStyleSheet(QStringLiteral(""));
        btn5->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout->addWidget(btn5, 1, 1, 1, 1);

        btn6 = new QToolButton(UIDemo10);
        btn6->setObjectName(QStringLiteral("btn6"));
        sizePolicy.setHeightForWidth(btn6->sizePolicy().hasHeightForWidth());
        btn6->setSizePolicy(sizePolicy);
        btn6->setStyleSheet(QStringLiteral(""));
        btn6->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout->addWidget(btn6, 1, 2, 1, 1);


        retranslateUi(UIDemo10);

        QMetaObject::connectSlotsByName(UIDemo10);
    } // setupUi

    void retranslateUi(QDialog *UIDemo10)
    {
        UIDemo10->setWindowTitle(QApplication::translate("UIDemo10", "Dialog", Q_NULLPTR));
        btn1->setText(QString());
        btn2->setText(QString());
        btn3->setText(QString());
        btn4->setText(QString());
        btn5->setText(QString());
        btn6->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class UIDemo10: public Ui_UIDemo10 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UIDEMO10_H
