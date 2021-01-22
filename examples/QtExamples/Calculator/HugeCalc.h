#ifndef HUGECALC_H
#define HUGECALC_H
#include"ui_hugeCalc.h"
#include"BigInt.h"
class HugeCalc:public QWidget, public Ui_HugeCalc
{
    Q_OBJECT
public:
    HugeCalc(QWidget* parent=0);
protected:
    void closeEvent(QCloseEvent *event);
protected:
    bool eventFilter(QObject *target, QEvent *event);
protected:
      void dragEnterEvent(QDragEnterEvent *event);
      void dropEvent(QDropEvent *event);
private:
      bool readFile(const QString &fileName);
private :
    BigInt bigInt[3];
    QString num[3];
    bool isAssiged[3];
private slots:
    void on_input_pushButton_clicked();
    void on_fileInput_pushButton_clicked();
    void on_output_pushButton_clicked();
    void on_fileOutput_pushButton_clicked();
    void on_complexCalculator_pushButton_clicked();
    void on_simpleCalculator_pushButton_clicked();
    void on_space_checkBox_toggled();
    void on_section_checkBox_toggled();
    void on_digital_checkBox_toggled();
    void on_sign_checkBox_toggled();
    void on_input_comboBox_currentIndexChanged(int);
    void on_output_comboBox_currentIndexChanged(int);
};
#endif // HUGECALC_H
