#ifndef FRMCPUMEMORYLABEL_H
#define FRMCPUMEMORYLABEL_H

#include <QWidget>

namespace Ui
{
class frmCpuMemoryLabel;
}

class frmCpuMemoryLabel : public QWidget
{
	Q_OBJECT

public:
	explicit frmCpuMemoryLabel(QWidget *parent = 0);
	~frmCpuMemoryLabel();

private:
	Ui::frmCpuMemoryLabel *ui;

private slots:
	void initForm();
};

#endif // FRMCPUMEMORYLABEL_H
