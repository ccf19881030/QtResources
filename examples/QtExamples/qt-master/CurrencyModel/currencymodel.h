#ifndef CURRENCYMODEL_H
#define CURRENCYMODEL_H

#include <QAbstractTableModel>
#include <QMap>

namespace Ui {
class CurrencyModel;
}

class CurrencyModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit CurrencyModel(QWidget *parent = 0);
    ~CurrencyModel();

    void setCurrencyMap(const QMap<QString, double> &map);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    QString currencyAt(int offset) const;

    QMap<QString, double> currencyMap;

private:
    Ui::CurrencyModel *ui;
};

#endif // CURRENCYMODEL_H
