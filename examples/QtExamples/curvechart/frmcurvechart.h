#ifndef FRMCURVECHART_H
#define FRMCURVECHART_H

#include <QWidget>

namespace Ui
{
class frmCurveChart;
}

class frmCurveChart : public QWidget
{
	Q_OBJECT

public:
	explicit frmCurveChart(QWidget *parent = 0);
	~frmCurveChart();

private:
	Ui::frmCurveChart *ui;
	QTimer *timer;

private slots:
	void initForm();
	void addData();
	void on_ckShowHLine_stateChanged(int arg1);
	void on_ckShowPoint_stateChanged(int arg1);
	void on_ckShowPointBg_stateChanged(int arg1);
	void on_btnSetData_clicked();
	void on_btnAddData_clicked();
	void on_btnClearData_clicked();
};

#endif // FRMCURVECHART_H
