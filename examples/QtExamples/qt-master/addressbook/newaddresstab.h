#ifndef NEWADDRESSTAB_H
#define NEWADDRESSTAB_H

#include <QWidget>

class QLabel;
class QPushButton;
class QVBoxLayout;

//通知用户，地址簿为空（如果不为空，则不会显示出此界面）
class NewAddressTab : public QWidget
{
    Q_OBJECT

public:
    NewAddressTab(QWidget *parent = 0);

public slots:
    void addEntry();

signals:
    void sendDetails(QString name, QString address);

private:
    QLabel *descriptionLabel;
    QPushButton *addButton;
    QVBoxLayout *mainLayout;

};

#endif // NEWADDRESSTAB_H
