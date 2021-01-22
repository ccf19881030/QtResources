#ifndef COORDINATESETTER_H
#define COORDINATESETTER_H

#include <QDialog>
#include <QTableWidget>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

namespace Ui {
class CoordinateSetter;
}

class CoordinateSetter : public QDialog
{
    Q_OBJECT

public:
    CoordinateSetter(QList<QPointF> *coords, QWidget *parent = 0);
    ~CoordinateSetter();

    void done(int result);

private slots:
    void addRow();

private:
    QTableWidget *tableWidget;
    QDialogButtonBox *buttonBox;
    QList<QPointF> *coordinates;

private:
    Ui::CoordinateSetter *ui;
};

#endif // COORDINATESETTER_H
