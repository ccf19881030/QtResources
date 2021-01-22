#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QItemEditorFactory>
#include <QItemEditorCreatorBase>
#include <QColor>
#include <QStandardItemEditorCreator>
#include <QTableWidget>
#include <ColorListEditor.h>
#include <QGridLayout>

namespace Ui {
class Window;
}

class Window : public QWidget
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

private:
    void createGUI();

private:
    Ui::Window *ui;
};

#endif // WINDOW_H
