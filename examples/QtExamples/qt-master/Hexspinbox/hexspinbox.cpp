#include "hexspinbox.h"
#include "ui_hexspinbox.h"

Hexspinbox::Hexspinbox(QWidget *parent) :
    QSpinBox(parent),
    ui(new Ui::Hexspinbox)
{
    setRange(0, 255);
    //接收1~8个字符，每个字符均为十六进制数字
    validator = new QRegExpValidator(QRegExp("[0-9A-Fa-f]{1,8}"), this);
}

//判断输入的结果是否有效
QValidator::State Hexspinbox::validate(QString &text, int &pos) const
{
    return validator->validate(text, pos);
}

//将数值转换为一个字符串
QString Hexspinbox::textFromValue(int value) const
{
    return QString::number(value, 16).toUpper();
}

//将字符串转换为数值
int Hexspinbox::valueFromText(const QString &text) const
{
    bool ok;
    return text.toInt(&ok, 16);
}

Hexspinbox::~Hexspinbox()
{
    delete ui;
}

void Hexspinbox::debug(int value)
{
    qDebug() << textFromValue(value);
}
