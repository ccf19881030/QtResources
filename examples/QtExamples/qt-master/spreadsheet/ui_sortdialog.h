/********************************************************************************
** Form generated from reading UI file 'sortdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SORTDIALOG_H
#define UI_SORTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SortDialog
{
public:
    QGridLayout *gridLayout;
    QGroupBox *primaryGroupBox;
    QGridLayout *gridLayout1;
    QLabel *primaryColumnLabel;
    QComboBox *primaryColumnCombo;
    QSpacerItem *spacerItem;
    QLabel *primaryOrderLabel;
    QComboBox *primaryOrderCombo;
    QVBoxLayout *vboxLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpacerItem *spacerItem1;
    QPushButton *moreButton;
    QSpacerItem *spacerItem2;
    QGroupBox *secondaryGroupBox;
    QGridLayout *gridLayout2;
    QLabel *secondaryColumnLabel;
    QComboBox *secondaryColumnCombo;
    QSpacerItem *spacerItem3;
    QLabel *secondaryOrderLabel;
    QComboBox *secondaryOrderCombo;
    QGroupBox *tertiaryGroupBox;
    QGridLayout *gridLayout3;
    QLabel *tertiaryColumnLabel;
    QComboBox *tertiaryColumnCombo;
    QSpacerItem *spacerItem4;
    QLabel *tertiaryOrderLabel;
    QComboBox *tertiaryOrderCombo;

    void setupUi(QDialog *SortDialog)
    {
        if (SortDialog->objectName().isEmpty())
            SortDialog->setObjectName(QStringLiteral("SortDialog"));
        SortDialog->resize(369, 398);
        gridLayout = new QGridLayout(SortDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        primaryGroupBox = new QGroupBox(SortDialog);
        primaryGroupBox->setObjectName(QStringLiteral("primaryGroupBox"));
        gridLayout1 = new QGridLayout(primaryGroupBox);
        gridLayout1->setObjectName(QStringLiteral("gridLayout1"));
        primaryColumnLabel = new QLabel(primaryGroupBox);
        primaryColumnLabel->setObjectName(QStringLiteral("primaryColumnLabel"));

        gridLayout1->addWidget(primaryColumnLabel, 0, 0, 1, 1);

        primaryColumnCombo = new QComboBox(primaryGroupBox);
        primaryColumnCombo->setObjectName(QStringLiteral("primaryColumnCombo"));

        gridLayout1->addWidget(primaryColumnCombo, 0, 1, 1, 1);

        spacerItem = new QSpacerItem(31, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout1->addItem(spacerItem, 0, 2, 1, 1);

        primaryOrderLabel = new QLabel(primaryGroupBox);
        primaryOrderLabel->setObjectName(QStringLiteral("primaryOrderLabel"));

        gridLayout1->addWidget(primaryOrderLabel, 1, 0, 1, 1);

        primaryOrderCombo = new QComboBox(primaryGroupBox);
        primaryOrderCombo->setObjectName(QStringLiteral("primaryOrderCombo"));

        gridLayout1->addWidget(primaryOrderCombo, 1, 1, 1, 2);


        gridLayout->addWidget(primaryGroupBox, 0, 0, 1, 1);

        vboxLayout = new QVBoxLayout();
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        okButton = new QPushButton(SortDialog);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setDefault(true);

        vboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(SortDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        vboxLayout->addWidget(cancelButton);

        spacerItem1 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem1);

        moreButton = new QPushButton(SortDialog);
        moreButton->setObjectName(QStringLiteral("moreButton"));
        moreButton->setCheckable(true);

        vboxLayout->addWidget(moreButton);


        gridLayout->addLayout(vboxLayout, 0, 1, 2, 1);

        spacerItem2 = new QSpacerItem(181, 31, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacerItem2, 1, 0, 1, 1);

        secondaryGroupBox = new QGroupBox(SortDialog);
        secondaryGroupBox->setObjectName(QStringLiteral("secondaryGroupBox"));
        gridLayout2 = new QGridLayout(secondaryGroupBox);
        gridLayout2->setObjectName(QStringLiteral("gridLayout2"));
        secondaryColumnLabel = new QLabel(secondaryGroupBox);
        secondaryColumnLabel->setObjectName(QStringLiteral("secondaryColumnLabel"));

        gridLayout2->addWidget(secondaryColumnLabel, 0, 0, 1, 1);

        secondaryColumnCombo = new QComboBox(secondaryGroupBox);
        secondaryColumnCombo->setObjectName(QStringLiteral("secondaryColumnCombo"));

        gridLayout2->addWidget(secondaryColumnCombo, 0, 1, 1, 1);

        spacerItem3 = new QSpacerItem(31, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout2->addItem(spacerItem3, 0, 2, 1, 1);

        secondaryOrderLabel = new QLabel(secondaryGroupBox);
        secondaryOrderLabel->setObjectName(QStringLiteral("secondaryOrderLabel"));

        gridLayout2->addWidget(secondaryOrderLabel, 1, 0, 1, 1);

        secondaryOrderCombo = new QComboBox(secondaryGroupBox);
        secondaryOrderCombo->setObjectName(QStringLiteral("secondaryOrderCombo"));

        gridLayout2->addWidget(secondaryOrderCombo, 1, 1, 1, 2);


        gridLayout->addWidget(secondaryGroupBox, 2, 0, 1, 1);

        tertiaryGroupBox = new QGroupBox(SortDialog);
        tertiaryGroupBox->setObjectName(QStringLiteral("tertiaryGroupBox"));
        gridLayout3 = new QGridLayout(tertiaryGroupBox);
        gridLayout3->setObjectName(QStringLiteral("gridLayout3"));
        tertiaryColumnLabel = new QLabel(tertiaryGroupBox);
        tertiaryColumnLabel->setObjectName(QStringLiteral("tertiaryColumnLabel"));

        gridLayout3->addWidget(tertiaryColumnLabel, 0, 0, 1, 1);

        tertiaryColumnCombo = new QComboBox(tertiaryGroupBox);
        tertiaryColumnCombo->setObjectName(QStringLiteral("tertiaryColumnCombo"));

        gridLayout3->addWidget(tertiaryColumnCombo, 0, 1, 1, 1);

        spacerItem4 = new QSpacerItem(31, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout3->addItem(spacerItem4, 0, 2, 1, 1);

        tertiaryOrderLabel = new QLabel(tertiaryGroupBox);
        tertiaryOrderLabel->setObjectName(QStringLiteral("tertiaryOrderLabel"));

        gridLayout3->addWidget(tertiaryOrderLabel, 1, 0, 1, 1);

        tertiaryOrderCombo = new QComboBox(tertiaryGroupBox);
        tertiaryOrderCombo->setObjectName(QStringLiteral("tertiaryOrderCombo"));

        gridLayout3->addWidget(tertiaryOrderCombo, 1, 1, 1, 2);


        gridLayout->addWidget(tertiaryGroupBox, 3, 0, 1, 1);

        QWidget::setTabOrder(primaryColumnCombo, primaryOrderCombo);
        QWidget::setTabOrder(primaryOrderCombo, secondaryColumnCombo);
        QWidget::setTabOrder(secondaryColumnCombo, secondaryOrderCombo);
        QWidget::setTabOrder(secondaryOrderCombo, tertiaryColumnCombo);
        QWidget::setTabOrder(tertiaryColumnCombo, tertiaryOrderCombo);
        QWidget::setTabOrder(tertiaryOrderCombo, okButton);
        QWidget::setTabOrder(okButton, cancelButton);
        QWidget::setTabOrder(cancelButton, moreButton);

        retranslateUi(SortDialog);
        QObject::connect(moreButton, SIGNAL(toggled(bool)), secondaryGroupBox, SLOT(setVisible(bool)));
        QObject::connect(moreButton, SIGNAL(toggled(bool)), tertiaryGroupBox, SLOT(setVisible(bool)));
        QObject::connect(okButton, SIGNAL(clicked()), SortDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), SortDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SortDialog);
    } // setupUi

    void retranslateUi(QDialog *SortDialog)
    {
        SortDialog->setWindowTitle(QApplication::translate("SortDialog", "Sort", 0));
        primaryGroupBox->setTitle(QApplication::translate("SortDialog", "&Primary Key", 0));
        primaryColumnLabel->setText(QApplication::translate("SortDialog", "<html><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\" white-space: pre-wrap; font-family:Sans Serif; font-weight:400; font-style:normal; text-decoration:none;\"><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Column:</p></body></html>", 0));
        primaryColumnCombo->clear();
        primaryColumnCombo->insertItems(0, QStringList()
         << QApplication::translate("SortDialog", "None", 0)
        );
        primaryOrderLabel->setText(QApplication::translate("SortDialog", "<html><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\" white-space: pre-wrap; font-family:Sans Serif; font-weight:400; font-style:normal; text-decoration:none;\"><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Order:</p></body></html>", 0));
        primaryOrderCombo->clear();
        primaryOrderCombo->insertItems(0, QStringList()
         << QApplication::translate("SortDialog", "Ascending", 0)
         << QApplication::translate("SortDialog", "Descending", 0)
        );
        okButton->setText(QApplication::translate("SortDialog", "OK", 0));
        cancelButton->setText(QApplication::translate("SortDialog", "Cancel", 0));
        moreButton->setText(QApplication::translate("SortDialog", "&More", 0));
        secondaryGroupBox->setTitle(QApplication::translate("SortDialog", "&Secondary Key", 0));
        secondaryColumnLabel->setText(QApplication::translate("SortDialog", "<html><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\" white-space: pre-wrap; font-family:Sans Serif; font-weight:400; font-style:normal; text-decoration:none;\"><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Column:</p></body></html>", 0));
        secondaryColumnCombo->clear();
        secondaryColumnCombo->insertItems(0, QStringList()
         << QApplication::translate("SortDialog", "None", 0)
        );
        secondaryOrderLabel->setText(QApplication::translate("SortDialog", "<html><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\" white-space: pre-wrap; font-family:Sans Serif; font-weight:400; font-style:normal; text-decoration:none;\"><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Order:</p></body></html>", 0));
        secondaryOrderCombo->clear();
        secondaryOrderCombo->insertItems(0, QStringList()
         << QApplication::translate("SortDialog", "Ascending", 0)
         << QApplication::translate("SortDialog", "Descending", 0)
        );
        tertiaryGroupBox->setTitle(QApplication::translate("SortDialog", "&Tertiary Key", 0));
        tertiaryColumnLabel->setText(QApplication::translate("SortDialog", "<html><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\" white-space: pre-wrap; font-family:Sans Serif; font-weight:400; font-style:normal; text-decoration:none;\"><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Column:</p></body></html>", 0));
        tertiaryColumnCombo->clear();
        tertiaryColumnCombo->insertItems(0, QStringList()
         << QApplication::translate("SortDialog", "None", 0)
        );
        tertiaryOrderLabel->setText(QApplication::translate("SortDialog", "<html><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\" white-space: pre-wrap; font-family:Sans Serif; font-weight:400; font-style:normal; text-decoration:none;\"><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Order:</p></body></html>", 0));
        tertiaryOrderCombo->clear();
        tertiaryOrderCombo->insertItems(0, QStringList()
         << QApplication::translate("SortDialog", "Ascending", 0)
         << QApplication::translate("SortDialog", "Descending", 0)
        );
    } // retranslateUi

};

namespace Ui {
    class SortDialog: public Ui_SortDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SORTDIALOG_H
