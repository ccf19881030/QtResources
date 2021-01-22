#ifndef FRMLEDNUMBER_H
#define FRMLEDNUMBER_H

#include <QWidget>

namespace Ui
{
class frmLedNumber;
}

class frmLedNumber : public QWidget
{
	Q_OBJECT

public:
	explicit frmLedNumber(QWidget *parent = 0);
	~frmLedNumber();

private:
	Ui::frmLedNumber *ui;

private slots:
	void initForm();
    void updateValue();
};

#endif // FRMLEDNUMBER_H
