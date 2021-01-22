#ifndef FRMBARRULER_H
#define FRMBARRULER_H

#include <QWidget>

namespace Ui
{
class frmBarRuler;
}

class frmBarRuler : public QWidget
{
	Q_OBJECT

public:
	explicit frmBarRuler(QWidget *parent = 0);
	~frmBarRuler();

private:
	Ui::frmBarRuler *ui;

private slots:
	void initForm();
    void updateValue();
};

#endif // FRMBARRULER_H
