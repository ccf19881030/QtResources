/********************************************************************************
** Form generated from reading UI file 'iconeditor.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ICONEDITOR_H
#define UI_ICONEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IconEditor
{
public:

    void setupUi(QWidget *IconEditor)
    {
        if (IconEditor->objectName().isEmpty())
            IconEditor->setObjectName(QStringLiteral("IconEditor"));
        IconEditor->resize(400, 300);

        retranslateUi(IconEditor);

        QMetaObject::connectSlotsByName(IconEditor);
    } // setupUi

    void retranslateUi(QWidget *IconEditor)
    {
        IconEditor->setWindowTitle(QApplication::translate("IconEditor", "IconEditor", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class IconEditor: public Ui_IconEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ICONEDITOR_H
