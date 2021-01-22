#ifndef FRMIMAGECALENDAR_H
#define FRMIMAGECALENDAR_H

#include <QWidget>

namespace Ui {
class frmImageCalendar;
}

class frmImageCalendar : public QWidget
{
    Q_OBJECT

public:
    explicit frmImageCalendar(QWidget *parent = 0);
    ~frmImageCalendar();

private:
    Ui::frmImageCalendar *ui;
};

#endif // FRMIMAGECALENDAR_H
