#ifndef RECORD_H
#define RECORD_H

#include <QDialog>

namespace Ui {
class record;
}

class record : public QDialog
{
    Q_OBJECT
    
public:
    explicit record(QWidget *parent = 0);
    ~record();
    
private slots:
    void on_close_music_clicked();

    void on_exit_clicked();

private:
    Ui::record *ui;
};

#endif // RECORD_H
