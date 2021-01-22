/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWebKitWidgets/QWebView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout;
    QWebView *webView;
    QPushButton *btnLine;
    QPushButton *btnLinex;
    QPushButton *btnLiney;
    QPushButton *btnBar;
    QPushButton *btnBarx;
    QPushButton *btnBary;
    QPushButton *btnScatter;
    QPushButton *btnK;
    QPushButton *btnPie;
    QPushButton *btnRadar;
    QPushButton *btnChord;
    QPushButton *btnGauge;
    QPushButton *btnFunnel;
    QPushButton *btnData;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(736, 511);
        gridLayout = new QGridLayout(Widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        webView = new QWebView(Widget);
        webView->setObjectName(QStringLiteral("webView"));
        webView->setUrl(QUrl(QStringLiteral("about:blank")));

        gridLayout->addWidget(webView, 0, 0, 1, 7);

        btnLine = new QPushButton(Widget);
        btnLine->setObjectName(QStringLiteral("btnLine"));

        gridLayout->addWidget(btnLine, 1, 0, 1, 1);

        btnLinex = new QPushButton(Widget);
        btnLinex->setObjectName(QStringLiteral("btnLinex"));

        gridLayout->addWidget(btnLinex, 1, 1, 1, 1);

        btnLiney = new QPushButton(Widget);
        btnLiney->setObjectName(QStringLiteral("btnLiney"));

        gridLayout->addWidget(btnLiney, 1, 2, 1, 1);

        btnBar = new QPushButton(Widget);
        btnBar->setObjectName(QStringLiteral("btnBar"));

        gridLayout->addWidget(btnBar, 1, 3, 1, 1);

        btnBarx = new QPushButton(Widget);
        btnBarx->setObjectName(QStringLiteral("btnBarx"));

        gridLayout->addWidget(btnBarx, 1, 4, 1, 1);

        btnBary = new QPushButton(Widget);
        btnBary->setObjectName(QStringLiteral("btnBary"));

        gridLayout->addWidget(btnBary, 1, 5, 1, 1);

        btnScatter = new QPushButton(Widget);
        btnScatter->setObjectName(QStringLiteral("btnScatter"));

        gridLayout->addWidget(btnScatter, 1, 6, 1, 1);

        btnK = new QPushButton(Widget);
        btnK->setObjectName(QStringLiteral("btnK"));

        gridLayout->addWidget(btnK, 2, 0, 1, 1);

        btnPie = new QPushButton(Widget);
        btnPie->setObjectName(QStringLiteral("btnPie"));

        gridLayout->addWidget(btnPie, 2, 1, 1, 1);

        btnRadar = new QPushButton(Widget);
        btnRadar->setObjectName(QStringLiteral("btnRadar"));

        gridLayout->addWidget(btnRadar, 2, 2, 1, 1);

        btnChord = new QPushButton(Widget);
        btnChord->setObjectName(QStringLiteral("btnChord"));

        gridLayout->addWidget(btnChord, 2, 3, 1, 1);

        btnGauge = new QPushButton(Widget);
        btnGauge->setObjectName(QStringLiteral("btnGauge"));

        gridLayout->addWidget(btnGauge, 2, 4, 1, 1);

        btnFunnel = new QPushButton(Widget);
        btnFunnel->setObjectName(QStringLiteral("btnFunnel"));

        gridLayout->addWidget(btnFunnel, 2, 5, 1, 1);

        btnData = new QPushButton(Widget);
        btnData->setObjectName(QStringLiteral("btnData"));

        gridLayout->addWidget(btnData, 2, 6, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        btnLine->setText(QApplication::translate("Widget", "\346\212\230\347\272\277\345\233\276", 0));
        btnLinex->setText(QApplication::translate("Widget", "\346\212\230\347\272\277\351\235\242\347\247\257\345\233\276", 0));
        btnLiney->setText(QApplication::translate("Widget", "\345\217\214\346\225\260\345\200\274\346\212\230\347\272\277", 0));
        btnBar->setText(QApplication::translate("Widget", "\346\237\261\347\212\266\345\233\276", 0));
        btnBarx->setText(QApplication::translate("Widget", "\346\240\207\345\207\206\346\235\241\345\275\242\345\233\276", 0));
        btnBary->setText(QApplication::translate("Widget", "\345\275\251\350\231\271\346\237\261\347\212\266\345\233\276", 0));
        btnScatter->setText(QApplication::translate("Widget", "\346\225\243\347\202\271\345\233\276", 0));
        btnK->setText(QApplication::translate("Widget", "K\347\272\277\345\233\276", 0));
        btnPie->setText(QApplication::translate("Widget", "\351\245\274\345\233\276", 0));
        btnRadar->setText(QApplication::translate("Widget", "\351\233\267\350\276\276\345\233\276", 0));
        btnChord->setText(QApplication::translate("Widget", "\345\222\214\345\274\246\345\233\276", 0));
        btnGauge->setText(QApplication::translate("Widget", "\344\273\252\350\241\250\347\233\230", 0));
        btnFunnel->setText(QApplication::translate("Widget", "\346\274\217\346\226\227\345\233\276", 0));
        btnData->setText(QApplication::translate("Widget", "\345\212\250\346\200\201\346\225\260\346\215\256", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
