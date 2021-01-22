/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QStackedWidget *stackedWidget;
    QWidget *managePage;
    QLabel *label;
    QToolBox *toolBox;
    QWidget *page;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QComboBox *sellFactoryComboBox;
    QComboBox *sellBrandComboBox;
    QLineEdit *sellPriceLineEdit;
    QSpinBox *sellNumSpinBox;
    QLineEdit *sellSumLineEdit;
    QPushButton *sellOkBtn;
    QPushButton *sellCancelBtn;
    QLabel *label_7;
    QLabel *sellLastNumLabel;
    QLabel *label_9;
    QWidget *page_3;
    QListWidget *dailyList;
    QWidget *chartPage;
    QPushButton *updateBtn;
    QComboBox *factoryComboBox;
    QLabel *label_8;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(750, 500);
        stackedWidget = new QStackedWidget(Widget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(20, 60, 700, 410));
        managePage = new QWidget();
        managePage->setObjectName(QStringLiteral("managePage"));
        label = new QLabel(managePage);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 681, 31));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);
        label->setFrameShape(QFrame::StyledPanel);
        label->setAlignment(Qt::AlignCenter);
        toolBox = new QToolBox(managePage);
        toolBox->setObjectName(QStringLiteral("toolBox"));
        toolBox->setGeometry(QRect(10, 50, 331, 351));
        toolBox->setFrameShape(QFrame::WinPanel);
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setGeometry(QRect(0, 0, 327, 295));
        label_2 = new QLabel(page);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 20, 31, 16));
        label_3 = new QLabel(page);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 60, 31, 16));
        label_4 = new QLabel(page);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 100, 31, 16));
        label_5 = new QLabel(page);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 140, 31, 16));
        label_6 = new QLabel(page);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(30, 180, 31, 16));
        sellFactoryComboBox = new QComboBox(page);
        sellFactoryComboBox->setObjectName(QStringLiteral("sellFactoryComboBox"));
        sellFactoryComboBox->setGeometry(QRect(70, 20, 91, 22));
        sellBrandComboBox = new QComboBox(page);
        sellBrandComboBox->setObjectName(QStringLiteral("sellBrandComboBox"));
        sellBrandComboBox->setGeometry(QRect(70, 60, 71, 22));
        sellPriceLineEdit = new QLineEdit(page);
        sellPriceLineEdit->setObjectName(QStringLiteral("sellPriceLineEdit"));
        sellPriceLineEdit->setGeometry(QRect(70, 100, 91, 20));
        sellNumSpinBox = new QSpinBox(page);
        sellNumSpinBox->setObjectName(QStringLiteral("sellNumSpinBox"));
        sellNumSpinBox->setGeometry(QRect(70, 140, 42, 22));
        sellSumLineEdit = new QLineEdit(page);
        sellSumLineEdit->setObjectName(QStringLiteral("sellSumLineEdit"));
        sellSumLineEdit->setGeometry(QRect(70, 180, 113, 20));
        sellOkBtn = new QPushButton(page);
        sellOkBtn->setObjectName(QStringLiteral("sellOkBtn"));
        sellOkBtn->setGeometry(QRect(60, 240, 75, 23));
        sellCancelBtn = new QPushButton(page);
        sellCancelBtn->setObjectName(QStringLiteral("sellCancelBtn"));
        sellCancelBtn->setGeometry(QRect(190, 240, 75, 23));
        label_7 = new QLabel(page);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(170, 100, 16, 16));
        sellLastNumLabel = new QLabel(page);
        sellLastNumLabel->setObjectName(QStringLiteral("sellLastNumLabel"));
        sellLastNumLabel->setGeometry(QRect(130, 140, 81, 16));
        label_9 = new QLabel(page);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(190, 180, 16, 16));
        toolBox->addItem(page, QString::fromUtf8("\345\207\272\345\224\256\350\275\246\350\276\206"));
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        page_3->setGeometry(QRect(0, 0, 327, 295));
        toolBox->addItem(page_3, QString::fromUtf8("\345\267\262\346\234\211\346\226\260\350\275\246\345\205\245\345\272\223"));
        dailyList = new QListWidget(managePage);
        dailyList->setObjectName(QStringLiteral("dailyList"));
        dailyList->setGeometry(QRect(360, 50, 321, 351));
        stackedWidget->addWidget(managePage);
        chartPage = new QWidget();
        chartPage->setObjectName(QStringLiteral("chartPage"));
        updateBtn = new QPushButton(chartPage);
        updateBtn->setObjectName(QStringLiteral("updateBtn"));
        updateBtn->setGeometry(QRect(250, 60, 75, 23));
        factoryComboBox = new QComboBox(chartPage);
        factoryComboBox->setObjectName(QStringLiteral("factoryComboBox"));
        factoryComboBox->setGeometry(QRect(20, 60, 221, 22));
        label_8 = new QLabel(chartPage);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 10, 681, 31));
        label_8->setFont(font);
        label_8->setFrameShape(QFrame::StyledPanel);
        label_8->setAlignment(Qt::AlignCenter);
        stackedWidget->addWidget(chartPage);

        retranslateUi(Widget);

        stackedWidget->setCurrentIndex(0);
        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "\346\261\275\350\275\246\351\224\200\345\224\256\347\256\241\347\220\206\347\263\273\347\273\237", 0));
        label->setText(QApplication::translate("Widget", "\345\223\201\347\211\214\350\275\246\347\256\241\347\220\206", 0));
        label_2->setText(QApplication::translate("Widget", "\345\216\202\345\256\266\357\274\232", 0));
        label_3->setText(QApplication::translate("Widget", "\345\223\201\347\211\214\357\274\232", 0));
        label_4->setText(QApplication::translate("Widget", "\346\212\245\344\273\267\357\274\232", 0));
        label_5->setText(QApplication::translate("Widget", "\346\225\260\351\207\217\357\274\232", 0));
        label_6->setText(QApplication::translate("Widget", "\351\207\221\351\242\235\357\274\232", 0));
        sellOkBtn->setText(QApplication::translate("Widget", "\347\241\256\345\256\232", 0));
        sellCancelBtn->setText(QApplication::translate("Widget", "\345\217\226\346\266\210", 0));
        label_7->setText(QApplication::translate("Widget", "\344\270\207", 0));
        sellLastNumLabel->setText(QApplication::translate("Widget", "\345\211\251\344\275\231\346\225\260\351\207\217\357\274\232000", 0));
        label_9->setText(QApplication::translate("Widget", "\344\270\207", 0));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("Widget", "\345\207\272\345\224\256\350\275\246\350\276\206", 0));
        toolBox->setItemText(toolBox->indexOf(page_3), QApplication::translate("Widget", "\345\267\262\346\234\211\346\226\260\350\275\246\345\205\245\345\272\223", 0));
        updateBtn->setText(QApplication::translate("Widget", "\346\233\264\346\226\260\346\230\276\347\244\272", 0));
        label_8->setText(QApplication::translate("Widget", "\351\224\200\345\224\256\347\273\237\350\256\241", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
