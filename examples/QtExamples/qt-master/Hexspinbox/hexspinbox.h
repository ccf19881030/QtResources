#ifndef HEXSPINBOX_H
#define HEXSPINBOX_H

#include <QMainWindow>
#include <QSpinBox>
#include <QString>
#include <QDebug>

namespace Ui {
class Hexspinbox;
}

class Hexspinbox : public QSpinBox
{
    Q_OBJECT

public:
    explicit Hexspinbox(QWidget *parent = 0);
    ~Hexspinbox();

private:
    Ui::Hexspinbox *ui;
protected:
    QValidator::State validate(QString &text, int &pos) const;
    int valueFromText(const QString &text) const;
    QString textFromValue(int val) const;

private slots:
    void debug(int value);

private:
    QRegExpValidator *validator;
};

#endif // HEXSPINBOX_H
