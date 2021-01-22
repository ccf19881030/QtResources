#ifndef CREATESHORTCUT_H
#define CREATESHORTCUT_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QGridLayout>
#include <QMessageBox>

using namespace std;
#include <iostream>

#include <stdio.h>
#include <windows.h>
#include <SHLOBJ.H>

class createShortcut : public QDialog
{
    Q_OBJECT

public:
    createShortcut(QWidget *parent = 0);
    ~createShortcut();
private:
    QLabel *shortcutLabel;
    QLineEdit *shortcutEdit;
    QLabel *destDirLabel;
    QLineEdit *destDirEdit;
    QLabel *showTypeLabel;
    QComboBox *showTypeCombo;
    QLabel *descLabel;
    QLineEdit *descEdit;
    QPushButton *okBtn;
    QPushButton *quitBtn;
    QGridLayout *layout;

    BOOL onCreateShortcut(LPCSTR lpszFileName, LPCSTR lpszLnkFileDir, LPCSTR lpszLnkFileName, LPCSTR lpszWorkDir, WORD wHotkey, LPCWSTR lpszDescription, int iShowCmd);

private slots:
    void onQuitBtn();
    void onOkBtn();
};

#endif // CREATESHORTCUT_H
