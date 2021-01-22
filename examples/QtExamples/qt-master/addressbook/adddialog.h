#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>

class QLabel;
class QPushButton;
class QTextEdit;
class QLineEdit;

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    AddDialog(QWidget *parent = 0);
    QLineEdit *nameText;
    QTextEdit *addressText;

private:
    QLabel *nameLabel;
    QLabel *addressLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // ADDDIALOG_H
