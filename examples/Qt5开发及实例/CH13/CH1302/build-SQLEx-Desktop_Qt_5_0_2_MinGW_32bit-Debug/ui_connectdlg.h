/********************************************************************************
** Form generated from reading UI file 'connectdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTDLG_H
#define UI_CONNECTDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QSqlConnectionDialogUi
{
public:
    QVBoxLayout *vboxLayout;
    QGroupBox *connGroupBox;
    QGridLayout *gridLayout;
    QComboBox *comboDriver;
    QLabel *textLabel4;
    QLabel *textLabel2;
    QLineEdit *editDatabase;
    QSpinBox *portSpinBox;
    QLabel *textLabel3;
    QLineEdit *editPassword;
    QLineEdit *editUsername;
    QLineEdit *editHostname;
    QLabel *textLabel5;
    QLabel *textLabel5_2;
    QLabel *textLabel4_2;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QLabel *status_label;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *QSqlConnectionDialogUi)
    {
        if (QSqlConnectionDialogUi->objectName().isEmpty())
            QSqlConnectionDialogUi->setObjectName(QStringLiteral("QSqlConnectionDialogUi"));
        QSqlConnectionDialogUi->resize(320, 285);
        vboxLayout = new QVBoxLayout(QSqlConnectionDialogUi);
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout->setContentsMargins(9, 9, 9, 9);
#endif
        vboxLayout->setObjectName(QStringLiteral("vboxLayout"));
        connGroupBox = new QGroupBox(QSqlConnectionDialogUi);
        connGroupBox->setObjectName(QStringLiteral("connGroupBox"));
        gridLayout = new QGridLayout(connGroupBox);
#ifndef Q_OS_MAC
        gridLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        gridLayout->setContentsMargins(9, 9, 9, 9);
#endif
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        comboDriver = new QComboBox(connGroupBox);
        comboDriver->setObjectName(QStringLiteral("comboDriver"));

        gridLayout->addWidget(comboDriver, 0, 1, 1, 1);

        textLabel4 = new QLabel(connGroupBox);
        textLabel4->setObjectName(QStringLiteral("textLabel4"));

        gridLayout->addWidget(textLabel4, 2, 0, 1, 1);

        textLabel2 = new QLabel(connGroupBox);
        textLabel2->setObjectName(QStringLiteral("textLabel2"));

        gridLayout->addWidget(textLabel2, 0, 0, 1, 1);

        editDatabase = new QLineEdit(connGroupBox);
        editDatabase->setObjectName(QStringLiteral("editDatabase"));

        gridLayout->addWidget(editDatabase, 1, 1, 1, 1);

        portSpinBox = new QSpinBox(connGroupBox);
        portSpinBox->setObjectName(QStringLiteral("portSpinBox"));
        portSpinBox->setMaximum(65535);
        portSpinBox->setMinimum(-1);
        portSpinBox->setValue(-1);

        gridLayout->addWidget(portSpinBox, 5, 1, 1, 1);

        textLabel3 = new QLabel(connGroupBox);
        textLabel3->setObjectName(QStringLiteral("textLabel3"));

        gridLayout->addWidget(textLabel3, 1, 0, 1, 1);

        editPassword = new QLineEdit(connGroupBox);
        editPassword->setObjectName(QStringLiteral("editPassword"));
        editPassword->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(editPassword, 3, 1, 1, 1);

        editUsername = new QLineEdit(connGroupBox);
        editUsername->setObjectName(QStringLiteral("editUsername"));

        gridLayout->addWidget(editUsername, 2, 1, 1, 1);

        editHostname = new QLineEdit(connGroupBox);
        editHostname->setObjectName(QStringLiteral("editHostname"));

        gridLayout->addWidget(editHostname, 4, 1, 1, 1);

        textLabel5 = new QLabel(connGroupBox);
        textLabel5->setObjectName(QStringLiteral("textLabel5"));

        gridLayout->addWidget(textLabel5, 4, 0, 1, 1);

        textLabel5_2 = new QLabel(connGroupBox);
        textLabel5_2->setObjectName(QStringLiteral("textLabel5_2"));

        gridLayout->addWidget(textLabel5_2, 5, 0, 1, 1);

        textLabel4_2 = new QLabel(connGroupBox);
        textLabel4_2->setObjectName(QStringLiteral("textLabel4_2"));

        gridLayout->addWidget(textLabel4_2, 3, 0, 1, 1);


        vboxLayout->addWidget(connGroupBox);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        label = new QLabel(QSqlConnectionDialogUi);
        label->setObjectName(QStringLiteral("label"));

        hboxLayout->addWidget(label);

        status_label = new QLabel(QSqlConnectionDialogUi);
        status_label->setObjectName(QStringLiteral("status_label"));
        QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(0), static_cast<QSizePolicy::Policy>(0));
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(status_label->sizePolicy().hasHeightForWidth());
        status_label->setSizePolicy(sizePolicy);

        hboxLayout->addWidget(status_label);


        vboxLayout->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout1->setSpacing(6);
#endif
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName(QStringLiteral("hboxLayout1"));
        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem);

        okButton = new QPushButton(QSqlConnectionDialogUi);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setDefault(true);

        hboxLayout1->addWidget(okButton);

        cancelButton = new QPushButton(QSqlConnectionDialogUi);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        hboxLayout1->addWidget(cancelButton);


        vboxLayout->addLayout(hboxLayout1);

#ifndef QT_NO_SHORTCUT
        textLabel4->setBuddy(editUsername);
        textLabel2->setBuddy(comboDriver);
        textLabel3->setBuddy(editDatabase);
        textLabel5->setBuddy(editHostname);
        textLabel5_2->setBuddy(portSpinBox);
        textLabel4_2->setBuddy(editPassword);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(comboDriver, editDatabase);
        QWidget::setTabOrder(editDatabase, editUsername);
        QWidget::setTabOrder(editUsername, editPassword);
        QWidget::setTabOrder(editPassword, editHostname);
        QWidget::setTabOrder(editHostname, portSpinBox);
        QWidget::setTabOrder(portSpinBox, okButton);
        QWidget::setTabOrder(okButton, cancelButton);

        retranslateUi(QSqlConnectionDialogUi);

        QMetaObject::connectSlotsByName(QSqlConnectionDialogUi);
    } // setupUi

    void retranslateUi(QDialog *QSqlConnectionDialogUi)
    {
        QSqlConnectionDialogUi->setWindowTitle(QApplication::translate("QSqlConnectionDialogUi", "\346\225\260\346\215\256\345\272\223\350\277\236\346\216\245", 0));
        connGroupBox->setTitle(QApplication::translate("QSqlConnectionDialogUi", "\346\225\260\346\215\256\345\272\223\350\277\236\346\216\245\350\256\276\347\275\256", 0));
        textLabel4->setText(QApplication::translate("QSqlConnectionDialogUi", "\347\224\250\346\210\267\345\220\215\357\274\232", 0));
        textLabel2->setText(QApplication::translate("QSqlConnectionDialogUi", "\351\251\261\345\212\250:", 0));
        portSpinBox->setSpecialValueText(QApplication::translate("QSqlConnectionDialogUi", "Default", 0));
        textLabel3->setText(QApplication::translate("QSqlConnectionDialogUi", "\346\225\260\346\215\256\345\272\223\345\220\215\357\274\232", 0));
        textLabel5->setText(QApplication::translate("QSqlConnectionDialogUi", "\344\270\273\346\234\272\345\220\215\357\274\232", 0));
        textLabel5_2->setText(QApplication::translate("QSqlConnectionDialogUi", "\347\253\257\345\217\243\357\274\232", 0));
        textLabel4_2->setText(QApplication::translate("QSqlConnectionDialogUi", "\345\257\206\347\240\201\357\274\232", 0));
        label->setText(QApplication::translate("QSqlConnectionDialogUi", "\347\212\266\346\200\201\357\274\232", 0));
        status_label->setText(QString());
        okButton->setText(QApplication::translate("QSqlConnectionDialogUi", "\350\277\236\346\216\245", 0));
        cancelButton->setText(QApplication::translate("QSqlConnectionDialogUi", "\351\200\200\345\207\272", 0));
    } // retranslateUi

};

namespace Ui {
    class QSqlConnectionDialogUi: public Ui_QSqlConnectionDialogUi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTDLG_H
