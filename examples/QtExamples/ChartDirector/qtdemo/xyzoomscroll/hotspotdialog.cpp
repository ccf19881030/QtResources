#include <QVBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include "hotspotdialog.h"

HotSpotDialog::HotSpotDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Hot Spot Parameters");
    resize(400, 360);

    m_ParamList = new QTableWidget(this);
    m_ParamList->verticalHeader()->setDefaultSectionSize(24);
    m_ParamList->horizontalHeader()->setStretchLastSection(true);

    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    verticalLayout->addWidget(m_ParamList);
}

void HotSpotDialog::setData(ImageMapHandler *hotSpotData)
{
    m_ParamList->setColumnCount(2);
    m_ParamList->setHorizontalHeaderLabels(QStringList() << "Param" << "Value");

    if (0!= hotSpotData)
    {
       for (int i = 0; 0 != hotSpotData->getKey(i); ++i)
        {
            m_ParamList->insertRow(i);
            
            QLabel *attr = new QLabel(QString::fromUtf8(hotSpotData->getKey(i)));
            attr->setMargin(5);
            m_ParamList->setCellWidget(i, 0, attr);
            
            QLabel *value = new QLabel(QString::fromUtf8(hotSpotData->getValue(i)));
            value->setMargin(5);
            m_ParamList->setCellWidget(i, 1, value);
        }
    }
}
