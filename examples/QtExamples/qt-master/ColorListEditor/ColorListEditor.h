#ifndef COLORLISTEDITOR_H
#define COLORLISTEDITOR_H

#include <QComboBox>

class QColor;
class QWidget;

class ColorListEditor : public QComboBox
{
    Q_OBJECT
    //自定义QColor属性
    Q_PROPERTY(QColor color READ color WRITE setColor USER true)

public:
    ColorListEditor(QWidget *widget = 0);

public:
    QColor color() const;
    void setColor(QColor c);

private:
    void populateList();
};


#endif // COLORLISTEDITOR_H
