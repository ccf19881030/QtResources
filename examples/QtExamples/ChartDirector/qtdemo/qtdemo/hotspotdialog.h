#ifndef HOTSPOTDIALOG_H
#define HOTSPOTDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include "chartdir.h"

class HotSpotDialog : public QDialog {
    Q_OBJECT
public:
    HotSpotDialog(QWidget *parent = 0);
    void setData(ImageMapHandler *data);
private:
    QTableWidget *m_ParamList;
};

#endif // HOTSPOTDIALOG_H
