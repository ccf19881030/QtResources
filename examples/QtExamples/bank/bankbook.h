#ifndef BANKBOOK_H
#define BANKBOOK_H

#include <QDialog>

namespace Ui {
class bankbook;
}

class bankbook : public QDialog
{
    Q_OBJECT
    
public:
    explicit bankbook(QWidget *parent = 0);
    ~bankbook();
    
private slots:
    void on_close_music_clicked();

    void on_exit_clicked();

private:
    Ui::bankbook *ui;
};

#endif // BANKBOOK_H
