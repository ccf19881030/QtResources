#include "combobox.h"
#include "qlistview.h"

ComboBox::ComboBox(QWidget *parent) : QComboBox(parent)
{
    this->setView(new QListView());
}

