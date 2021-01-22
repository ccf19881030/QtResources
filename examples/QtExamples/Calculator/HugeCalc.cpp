#include"HugeCalc.h"
#include<QSettings>
#include<QMessageBox>
#include<QFileDialog>
#include<QTextStream>
#include<QRegExp>
#include <QMimeData>
#include<QTime>
#include<QUrl>
HugeCalc::HugeCalc(QWidget *parent):QWidget(parent)
{
    setupUi(this);
    //设置背景颜色
    setAutoFillBackground(true);
    QSettings settings;
    QPalette bgpal;
    int red,green,blue;
    red=settings.value("red/window",152).toInt();
    green=settings.value("green/window",204).toInt();
    blue=settings.value("blue/window",222).toInt();
    bgpal.setColor(QPalette::Background, QColor(red,green,blue));
    setPalette(bgpal);
    red=settings.value("red/textview",206).toInt();
    green=settings.value("green/textview",224).toInt();
    blue=settings.value("blue/textview",255).toInt();
    bgpal.setColor(QPalette::Base,QColor(red,green,blue));
    input_plainTextEdit->setPalette(bgpal);
    output_plainTextEdit->setPalette(bgpal);
    move(QPoint(350,250));
    input_plainTextEdit->installEventFilter(this);
    input_plainTextEdit->setAcceptDrops(false);   //拖放一个文本文件
    this->setAcceptDrops(true);
    isAssiged[0]=isAssiged[1]=isAssiged[2]=false;
}
void HugeCalc::closeEvent(QCloseEvent *event)
 {
    QMessageBox::StandardButton ret;
    ret = QMessageBox::question(this, tr("BigInteger Tool"),
                  tr("Are you sure you want to close this Window?"),
                  QMessageBox::Ok| QMessageBox::Cancel,QMessageBox::Cancel);
    if (ret == QMessageBox::Ok) {
         event->accept();
    } else {
         event->ignore();
    }
 }
void HugeCalc::on_input_pushButton_clicked()
{
    int Index=input_comboBox->currentIndex();
    QString str=input_plainTextEdit->toPlainText();
    if(str.isEmpty())
    {
        QMessageBox::warning(this, tr("BigInteger Tool"),
        tr("The input is empty！"),QMessageBox::Ok);
        return ;
    }
    if(str.contains(' '))
        str.remove(' ');
    if(str.contains(','))
        str.remove(',');
    QRegExp regExp("^([-+]?)(\\d+)$");
    if(regExp.indexIn(str)==-1)
    {
        QMessageBox::warning(this, tr("BigInteger Tool"),
        tr("There are some illegal characters or strings！"),QMessageBox::Ok);
        return ;
    }
    num[Index]=str;
    bigInt[Index]=str;
    isAssiged[Index]=true;
    output_comboBox->setCurrentIndex(Index);
    on_output_pushButton_clicked();
}
void HugeCalc::on_fileInput_pushButton_clicked()
{
    //这个函数会弹出一个文件对话框，让用户选择一个文件，并且返回这个文件名——或者，
    //如果用户单击了Cancel按钮，这返回一个空字符串
    //这个函数的第一个参数是它的父窗口部件，对话框通常拥有自主权，但是如果它有父对象，
    //那么在默认情况下，它就会居中放到父对象上。一个子对话框也会共用它的父对象任务栏
    //第二个参数是这个对话框使用的标题，第三个参数告诉它应从哪一级目录开始，在这个例子中就是从当前目录
    //第四个参数指定了文件过滤器，文件过滤器由一个描述文本和一个通配符组成，多个过滤器之间用';;’分隔
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open File..."),";",tr("Text files (*.txt)"));
    if (!fileName.isEmpty())
    {readFile(fileName);}
}
void HugeCalc::on_output_pushButton_clicked()
{
    int Index=output_comboBox->currentIndex();
    output_plainTextEdit->clear();
    QString result(bigInt[Index].toQString());
    int len=result.length();
    int digital=len;
    int work=0;
    if(result[0]=='-')
    {digital=len-1;work=1;}
    else if(result[0].isDigit()&&sign_checkBox->isChecked())
    {result.prepend('+');len++;work=1;}
    if(space_checkBox->isChecked())
    {
        for(int i=len-3;i>work;i-=3)
        {result.insert(i,' ');}

    }
    else if(section_checkBox->isChecked())
    {
        for(int i=len-3;i>work;i-=3)
        {result.insert(i,',');}

    }
    output_plainTextEdit->appendPlainText(result);
    if(digital_checkBox->isChecked())
    {
        output_plainTextEdit->appendPlainText(tr("The BigInteger has %1 digit.").arg(digital));
    }
}
void HugeCalc::on_fileOutput_pushButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
         tr("Output to..."),".",tr("Text files (*.txt)"));
    if (!fileName.isEmpty()){
        QFile file(fileName);
        file.open(QFile::WriteOnly | QFile::Text);
        int Index=output_comboBox->currentIndex();
        QTextStream out(&file);
        if(!output_plainTextEdit->toPlainText().isEmpty ())
            out<<output_plainTextEdit->toPlainText();
        else
            out <<bigInt[Index].toQString();
    }
}
void HugeCalc::on_complexCalculator_pushButton_clicked()
{
    int Index1=0,Index2=0;
    QTime time;
    time.start();
    if(fourOper_radioButton->isChecked())
    {
        Index1=fourOperFirst_comboBox->currentIndex();
        Index2=fourOperSecond_comboBox->currentIndex();
        int Index3=fourOperThird_comboBox->currentIndex();
        int Index4=fourOperFourth_comboBox->currentIndex();
        if(!isAssiged[Index2]||!isAssiged[Index4])
        {
            QMessageBox::warning(this, tr("LinearAlgebra Tool"),
            tr("There is a BigInt hasn't assigned,please check!"),QMessageBox::Ok);
            return;
        }
        if(Index3==0)
            {bigInt[Index1]=bigInt[Index2]+bigInt[Index4];}
        else if(Index3==1)
            {bigInt[Index1]=bigInt[Index2]-bigInt[Index4];}
        else if(Index3==2)
            {bigInt[Index1]=bigInt[Index2]*bigInt[Index4];}
        else if(Index3==3)
            {bigInt[Index1]=bigInt[Index2]/bigInt[Index4];}
        else
            {bigInt[Index1]=bigInt[Index2]%bigInt[Index4];}
    }
    else if(power_radioButton->isChecked())
    {
        Index1=powerFirst_comboBox->currentIndex();
        Index2=powerSecond_comboBox->currentIndex();
        if(!isAssiged[Index2])
        {
            QMessageBox::warning(this, tr("LinearAlgebra Tool"),
            tr("There is a BigInt hasn't assigned,please check!"),QMessageBox::Ok);
            return;
        }
        bigInt[Index1]=bigInt[Index2]^power_spinBox->value();
    }
    else if(factorial_radioButton->isChecked())
    {
        Index1=factorialFirst_comboBox->currentIndex();
        int ret=factorialSecond_comboBox->currentIndex();
        if(ret==0)
             bigInt[Index1].Factorial(factorial_spinBox->value());
        else
             bigInt[Index1].Factorial(factorial_spinBox->value(),'0');
        if(bigInt[Index1].isLegal==false)
        {
            QMessageBox::warning(this, tr("BigInteger Tool"),
            tr("The data overflow or illegal！"),QMessageBox::Ok);
            bigInt[Index1].isLegal=true;
            return ;
        }
    }
    else
    {
        Index1=sqrtFirst_comboBox->currentIndex();
        Index2=sqrtSecond_comboBox->currentIndex();
        if(!isAssiged[Index2])
        {
            QMessageBox::warning(this, tr("LinearAlgebra Tool"),
            tr("There is a BigInt hasn't assigned,please check!"),QMessageBox::Ok);
            return;
        }
        bigInt[Index1]=bigInt[Index2].Sqrt();
    }
    isAssiged[Index1]=true;
    if(bigInt[Index2].isLegal==false)
    {
        QMessageBox::warning(this, tr("BigInteger Tool"),
        tr("The data overflow or illegal！"),QMessageBox::Ok);
        bigInt[Index2].isLegal=true;
        isAssiged[Index1]=false;
        return ;
    }
    if(autoOutput_checkBox->isChecked())
    {
        output_comboBox->setCurrentIndex(Index1);
        on_output_pushButton_clicked();
    }
    if(time_checkBox->isChecked())
    time_label->setText(tr("%1ms").arg(time.elapsed()));
}
void HugeCalc::on_simpleCalculator_pushButton_clicked()
{
    int Index1;
    if(shift_radioButton->isChecked())
    {
        Index1=shiftFirst_comboBox->currentIndex();
        int Index2=shiftSecond_comboBox->currentIndex();
        if(!isAssiged[Index1])
        {
            QMessageBox::warning(this, tr("LinearAlgebra Tool"),
            tr("There is a BigInt hasn't assigned,please check!"),QMessageBox::Ok);
            return;
        }
        if(Index2==0)
            bigInt[Index1]>>=(shift_spinBox->value());
        else if(Index2==1)
            bigInt[Index1]<<=(shift_spinBox->value());
        else
            bigInt[Index1].Shift(shift_spinBox->value());
    }
    else if(system_radioButton->isChecked())
    {
        QMessageBox::information(this,tr("BigInteger Tool"),
                     tr("Sorry,the system change hasn't achieved!"),QMessageBox::Ok);
        return ;
    }
    else
    {
        Index1=elseFirst_comboBox->currentIndex();
        int Index2=elseSecond_comboBox->currentIndex();
        int Index3=elseThird_comboBox->currentIndex();
        if(!isAssiged[Index1]||!isAssiged[Index3])
        {
            QMessageBox::warning(this, tr("LinearAlgebra Tool"),
            tr("There is a BigInt hasn't assigned,please check!"),QMessageBox::Ok);
            return;
        }
        if(Index2==0)
        {
            Swap(&bigInt[Index1],&bigInt[Index3]);
        }
        else
        {
            int ret=bigInt[Index1].Cmp(bigInt[Index3]);
            QString num1=elseFirst_comboBox->currentText();
            QString num2=elseThird_comboBox->currentText();
            if(ret==0)
            {
                QMessageBox::information(this,tr("BigInteger Tool"),
                        tr("%1 =%2").arg(num1,num2),QMessageBox::Ok);
            }
            else if(ret==1)
            {
                QMessageBox::information(this,tr("BigInteger Tool"),
                        tr("%1 >%2").arg(num1,num2),QMessageBox::Ok);
            }
            else
            {
                QMessageBox::information(this,tr("BigInteger Tool"),
                        tr("%1 <%2").arg(num1,num2),QMessageBox::Ok);
            }
        }
    }
    if(autoOutput_checkBox->isChecked())
    {
        output_comboBox->setCurrentIndex(Index1);
        on_output_pushButton_clicked();
    }
}
void HugeCalc::on_space_checkBox_toggled()
{
    if(space_checkBox->isChecked())
        section_checkBox->setChecked(true);
    on_output_pushButton_clicked();
}
void HugeCalc::on_section_checkBox_toggled()
{
    if(!section_checkBox->isChecked())
        {space_checkBox->setChecked(false);}
    on_output_pushButton_clicked();
}
void HugeCalc::on_digital_checkBox_toggled()
{ on_output_pushButton_clicked();}
void HugeCalc::on_sign_checkBox_toggled()
{on_output_pushButton_clicked();}
void HugeCalc::on_input_comboBox_currentIndexChanged(int Index)
{
    if(!num[Index].isEmpty())
    {input_plainTextEdit->setPlainText(num[Index]);}
}
void HugeCalc::on_output_comboBox_currentIndexChanged(int)
{ on_output_pushButton_clicked();}
void HugeCalc::dragEnterEvent(QDragEnterEvent *event)
{
     if(event->mimeData()->hasFormat("text/uri-list"));
     {
        event->acceptProposedAction();
     }
     //中调用 acceptProposeAction() 函数，我们就可以向用户暗示，你可以将拖动的对
     //象放在这个组件上。默认情况下，组件是不会接受拖放的。如果我们调用了这样的函数，那么
     //Qt会自动地以光标 来提示用户是否可以将对象放在组件上。在这里，我们希望告诉用户，
     //窗口可以接受拖放
}
void HugeCalc::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls=event->mimeData()->urls();
    if(urls.isEmpty()){return ;}
    QString fileName=urls.first().toLocalFile();
    if(fileName.isEmpty()){return ;}
    readFile(fileName);
    return ;
}
bool HugeCalc::readFile(const QString &fileName)
{
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly))//可以打开
    {
        QFile file(fileName);
        file.open(QFile::ReadOnly | QFile::Text);
        QTextStream in(&file);
        QString str;
        QRegExp regExp("^([-+]?)(\\d+)(\n*)$");
        #ifndef QT_NO_CURSOR
            QApplication::setOverrideCursor(Qt::WaitCursor);
        #endif
            str=in.readAll();
        #ifndef QT_NO_CURSOR
            QApplication::restoreOverrideCursor();
        #endif
        file.close();
        if(str.isEmpty())
        {
            QMessageBox::warning(this, tr("BigInteger Tool"),
            tr("The input is empty！"),QMessageBox::Ok);
            return false;
        }
        if(str.contains(' '))
            str.remove(' ');
        if(str.contains(','))
            str.remove(',');
        if(regExp.indexIn(str)==-1)
        {
            QMessageBox::warning(this, tr("BigInteger Tool"),
            tr("There are some illegal characters or strings！"),QMessageBox::Ok);
            return false;
        }
        str=str.simplified();
        int Index=input_comboBox->currentIndex();
        input_plainTextEdit->setPlainText(str);
        num[Index]=str;
        bigInt[Index]=str;
        isAssiged[Index]=true;
        output_comboBox->setCurrentIndex(Index);
        on_output_pushButton_clicked();
        return true;
    }
    return false;
}
bool HugeCalc::eventFilter(QObject *target, QEvent *event)
{
    if(target ==input_plainTextEdit)//此判断可以省略,此程序中必进入此判断，但是有此句判断让程序更加规范
    {
          if (event->type() == QEvent::KeyPress)
          {
              QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
              int code=keyEvent->key();
              if(code==Qt::Key_Return||code==Qt::Key_Enter)
              {
                  if(input_plainTextEdit->textCursor().atEnd())
                  {
                      on_input_pushButton_clicked();
                      return true;
                  }
              }
          }
          return false;
    }
    return QObject::eventFilter(target, event);
}
