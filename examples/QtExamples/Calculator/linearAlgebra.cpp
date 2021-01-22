#include"linearAlgebra.h"
#include<QMessageBox>
#include<QCloseEvent>
#include<QFile>
#include<QList>
#include<QUrl>
#include<QFileDialog>
#include<QTextStream>
#include<QPlainTextEdit>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QSettings>
#include<qmath.h>
#include <QMimeData>
LinearAlgebra::LinearAlgebra(QWidget *parent):QWidget(parent)
{
    setupUi(this);

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
    inputTableWidget->setPalette(bgpal);
    outputTableWidget->setPalette(bgpal);
    move(QPoint(350,250));
    inputTableWidget->setColumnWidth(0,colWidthSpinBox->value());
    outputTableWidget->setColumnWidth(0,colWidthSpinBox->value());
    inputTableWidget->installEventFilter(this);//调用installEventFilter（）注册需要管理的对象

    inputTableWidget->setAcceptDrops(false);   //拖放一个文本文件
    this->setAcceptDrops(true);

    isAssiged[0]=isAssiged[1]=isAssiged[2]=isAssiged[3]=false;
    isLadder[0]=isLadder[1]=isLadder[2]=isLadder[3]=false;
}
void LinearAlgebra::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton ret;
    ret = QMessageBox::question(this, tr("LinearAlgebra Tool"),
                  tr("Are you sure you want to close this Window?"),
                  QMessageBox::Ok| QMessageBox::Cancel,QMessageBox::Cancel);
    if (ret == QMessageBox::Ok) {
         event->accept();
    } else {
         event->ignore();
    }
}

void LinearAlgebra::changeRow(int row)
{
    inputTableWidget->setRowCount(row);
}
void LinearAlgebra::changeCol(int col)
{
    int colWidth=colWidthSpinBox->value();
    inputTableWidget->setColumnCount(col);
    for(int i=0;i<col;++i)
        inputTableWidget->setColumnWidth(i,colWidth);
}
void LinearAlgebra::changeColWidth(int colWidth)
{
    int columnCount1=inputTableWidget->columnCount();
    int columnCount2=outputTableWidget->columnCount();
    for(int i=0;i<columnCount1;++i)
        inputTableWidget->setColumnWidth(i,colWidth);
    for(int i=0;i<columnCount2;++i)
        outputTableWidget->setColumnWidth(i,colWidth);
}

void LinearAlgebra::on_inputPushButton_clicked()
{
    int row,col;
    int Index=inputComboBox->currentIndex();
    QRegExp regExp("^(-?\\d+)(\\.\\d+)?(/\\d+(\\.\\d+)?)?$");
    if(fileInCheckBox->isChecked())
    {
        QFileDialog *fileDialog =new QFileDialog(this,
                         tr("Open File..."),";",tr("Text files (*.txt)"));
        fileDialog->show();
        QString fileName;
        if(fileDialog->exec()==QDialog::Accepted)
        {
            fileName=fileDialog->selectedFiles()[0];
            readFile(fileName);
        }
        return;
    }
    else
    {
        QList <QTableWidgetItem *> listItem=inputTableWidget->selectedItems();
        for(int i=0;i<listItem.length();i++)  //将选中的表格项取消选中
        {listItem[i]->setSelected(false);}

        row=inputTableWidget->rowCount();
        col=inputTableWidget->columnCount();
        matrix[Index]=new double*[row];      //分配空间
        for(int i=0;i<row;i++)
            matrix[Index][i]=new double[col];
        QTableWidgetItem *item;
        QString str;
        double filling;
        bool autoFilling=autoFillingCheckBox->isChecked();
        if(autoFilling)
            filling=autoFillingDoubleSpinBox->value();
        for(int i=0;i<row;i++)
        {
            for(int j=0;j<col;j++)
            {
                if(item=inputTableWidget->item(i,j))
                {
                    str=item->text();
                    if(str.isEmpty())
                        goto A;
                    if(regExp.indexIn(str)!=-1)
                    {
                        int ret=str.indexOf('/');
                        if(ret==-1)
                           matrix[Index][i][j]=str.toDouble();
                        else
                        {
                            double dl1,dl2;
                            dl1=str.left(ret).toDouble();
                            dl2=str.right(str.length()-ret-1).toDouble();
                            matrix[Index][i][j]=dl1/dl2;
                        }
                    }
                    else
                    {
                        if(str.contains('e'))
                        {
                            QRegExp r("^([+-]?\\d+)(\\.\\d+)?([e][+-]?\\d+)$");
                            if(r.indexIn(str)!=-1){
                                matrix[Index][i][j]=str.toDouble();
                                continue;
                            }
                        }
                        item->setSelected(true);
                        QMessageBox::warning(this, tr("LinearAlgebra Tool"),
                        tr("The item(%1 , %2)is illegal！\nPlease check whether there are abnormal characters or Spaces")
                                           .arg(i+1).arg(j+1),QMessageBox::Ok);
                        return ;
                    }
                }
                else
A:                {
                    if(autoFilling==false)
                    {
                        inputTableWidget->setItem(i,j,new QTableWidgetItem(""));
                        inputTableWidget->item(i,j)->setSelected(true);
                        QMessageBox::warning(this, tr("LinearAlgebra Tool"),
                        tr("The item(%1 , %2)is empty！\n if you want to fill automatically,Please check the 'Fill' box,"
                           "and choose the number that needs to be filled.").arg(i+1).arg(j+1),QMessageBox::Ok);
                        return ;
                    }
                    else
                    {
                        inputTableWidget->setItem(i,j,new QTableWidgetItem(QString().setNum(filling)));
                        matrix[Index][i][j]=filling;
                    }
                }
            }
        }
        isAssiged[Index]=true;
        matrixRow[Index]=row;matrixCol[Index]=col;
        isLadder[Index]=false;
    }
}
void LinearAlgebra::on_outputPushButton_clicked()
{
    int Index=outputComboBox->currentIndex();
    if(!isAssiged[Index])
    {
        QMessageBox::warning(this, tr("LinearAlgebra Tool"),
        tr("The matrix that will be outputed hasn't assigned！,please check!"),QMessageBox::Ok);
        return ;
    }
    int row=matrixRow[Index],col=matrixCol[Index];
    int precision=precisionSpinBox->value();
    const double eps=1e-5;
    QString str;
    if(fileOutCheckBox->isChecked())
    {
        QString fileName = QFileDialog::getSaveFileName(this,
             tr("Output to..."),".",tr("Text files (*.txt)"));
        if (!fileName.isEmpty()){
            QFile file(fileName);
            file.open(QFile::WriteOnly | QFile::Text);
            QTextStream out(&file);
            out<<row<<' '<<col<<endl;
            for(int i=0;i<row;i++)
            {
                for(int j=0;j<col;j++)
                {
                    if(qAbs(matrix[Index][i][j])<=eps)
                        str.setNum(0);
                    else
                        str.setNum(matrix[Index][i][j],'g',precision);
                    out<<str<<' ';
                }
                out<<endl;
            }
        }
    }
    else
    {
        rowLineEdit->setText(tr("%1").arg(row));
        colLineEdit->setText(tr("%1").arg(col));
        outputTableWidget->setRowCount(row);
        outputTableWidget->setColumnCount(col);
        int colWidth=colWidthSpinBox->value();
        for(int i=0;i<col;++i)
            outputTableWidget->setColumnWidth(i,colWidth);
        for(int i=0;i<row;i++)
        {
            for(int j=0;j<col;j++)
            {
                if(qAbs(matrix[Index][i][j])<=eps)
                    str.setNum(0);
                else
                    str.setNum(matrix[Index][i][j],'g',precision);
                outputTableWidget->setItem(i,j,new QTableWidgetItem(str));
            }
        }
    }
}
void LinearAlgebra::on_inputComboBox_activated(int Index)
{
    if(!isAssiged[Index])
    {
        inputTableWidget->clear();
        inputRowSpinBox->setValue(1);
        inputColSpinBox->setValue(1);
        inputTableWidget->setRowCount(1);
        inputTableWidget->setColumnCount(1);
    }
    else
    {
        int row=matrixRow[Index],col=matrixCol[Index];
        int precision=precisionSpinBox->value();
        QString str;
        inputTableWidget->clear();
        inputRowSpinBox->setValue(row);
        inputColSpinBox->setValue(col);
        inputTableWidget->setRowCount(row);
        inputTableWidget->setColumnCount(col);

        for(int i=0;i<row;i++)
        {
            for(int j=0;j<col;j++)
            {
                str.setNum(matrix[Index][i][j],'g',precision);
                inputTableWidget->setItem(i,j,new QTableWidgetItem(str));
            }
        }
    }
}
void LinearAlgebra::on_outputComboBox_activated(int Index)
{
    if(!isAssiged[Index])
    {
        outputTableWidget->clear();
        outputTableWidget->setRowCount(1);
        outputTableWidget->setColumnCount(1);
        return ;
    }
    int row=matrixRow[Index],col=matrixCol[Index];
    int precision=precisionSpinBox->value();
    QString str;
    rowLineEdit->setText(tr("%1").arg(row));
    colLineEdit->setText(tr("%1").arg(col));
    outputTableWidget->setRowCount(row);
    outputTableWidget->setColumnCount(col);
    int colWidth=colWidthSpinBox->value();
    for(int i=0;i<col;++i)
        outputTableWidget->setColumnWidth(i,colWidth);
    const double eps=1e-5;
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            if(qAbs(matrix[Index][i][j])<=eps)
                str.setNum(0);
            else
                str.setNum(matrix[Index][i][j],'g',precision);
            outputTableWidget->setItem(i,j,new QTableWidgetItem(str));
        }
    }
}
void LinearAlgebra::on_clearPushButton_clicked()
{
    inputTableWidget->clear();
    int Index=inputComboBox->currentIndex();
    isAssiged[Index]=false;
    isLadder[Index]=false;
}
void LinearAlgebra::on_Calc_pushButton_clicked()
{
    bool isLegal=false;
    if(assign_radioButton->isChecked())
    {
        int Index1=assignFirst_ComboBox->currentIndex();
        int Index2=assignSecond_ComboBox->currentIndex();
        if(!isAssiged[Index2])
        {
            QMessageBox::warning(this, tr("LinearAlgebra Tool"),
            tr("There is a matrix hasn't assigned,please check!"),QMessageBox::Ok);
            return;
        }
        assign(Index1,Index2);
        fileOutCheckBox->setChecked(false);
        outputComboBox->setCurrentIndex(Index1);
        on_outputPushButton_clicked();
        return ;
    }
    if(basicCalc_radioButton->isChecked())   //基本运算
    {
        int Index=basicFirst_ComboBox->currentIndex();
        int Index1=basicSecond_ComboBox->currentIndex();
        int Index2=basicFourth_ComboBox->currentIndex();
        if(!isAssiged[Index1]||!isAssiged[Index2])
        {
            QMessageBox::warning(this, tr("LinearAlgebra Tool"),
            tr("The matrix that will be Calculated hasn't assigned,please check!"),QMessageBox::Ok);
            return;
        }
        int ret=basicThird_ComboBox->currentIndex();
        if(ret==0)
            {isLegal=add(Index,Index1,Index2);}
        else if(ret==1)
            {isLegal=subtract(Index,Index1,Index2);}
        else
            {isLegal=multiply(Index,Index1,Index2);}
        if(isLegal&&autoShowResultCheckBox->isChecked())
        {
            fileOutCheckBox->setChecked(false);
            outputComboBox->setCurrentIndex(Index);
            on_outputPushButton_clicked();
        }
        return ;
    }
    if(power_radioButton->isChecked())
    {
        int Index1=powerFirst_ComboBox->currentIndex();
        int Index2=powerSecond_ComboBox->currentIndex();
        int n=power_SpinBox->value();
        if(!isAssiged[Index2])
        {
            QMessageBox::warning(this, tr("LinearAlgebra Tool"),
            tr("The matrix that will be Calculated hasn't assigned,please check!"),QMessageBox::Ok);
            return;
        }
        isLegal=power(Index1,Index2,n);
        if(isLegal&&autoShowResultCheckBox->isChecked())
        {
            fileOutCheckBox->setChecked(false);
            outputComboBox->setCurrentIndex(Index1);
            on_outputPushButton_clicked();
        }
        return ;
    }
    int Index=choiceComboBox->currentIndex();
    if(!isAssiged[Index])
    {
        QMessageBox::warning(this, tr("LinearAlgebra Tool"),
        tr("The matrix that will be Calculated hasn't assigned,please check!"),QMessageBox::Ok);
        return;
    }
    if(det_radioButton->isChecked())
        {det(Index,true);return;}
    else if(rank_radioButton->isChecked())
        {rank(Index);return;}
    else if(transpose_radioButton->isChecked())
        {isLegal=transpose(Index);}
    else if(adjoint_radioButton->isChecked())
        {isLegal=adjoint(Index);}
    else if(ladder_radioButton->isChecked())
        {isLegal=ladder(Index);}
    else if(inver_radioButton->isChecked())
        {isLegal=inver(Index);}
    else if(generInver_radioButton->isChecked())
        {isLegal=generInver(Index);}
    else if(matrixQR_radioButton->isChecked())
        {isLegal=matrixQR(Index);}
    else if(eigenvalue_radioButton->isChecked())
        {eigenValue(Index,true);return;}
    else if(eigenvector_radioButton->isChecked())
        {eigenVector(Index);return ;}
    else if(isOrthogonal_radioButton->isChecked())
        {isOrthogonal(Index);return;}
    else if(maxEigenValue_radioButton->isChecked())
        {maxEigenValue(Index);return;}
    else if(eigenpolyomial_radioButton->isChecked())
        {eigenPolyomial(Index);return ;}
    else if(homogen_radioButton->isChecked())
        {homogen(Index);return;}
    else if(inhomogen_radioButton->isChecked())
        {isLegal=inhomogen(Index);}
    if(isLegal&&autoShowResultCheckBox->isChecked())
    {
        fileOutCheckBox->setChecked(false);
        outputComboBox->setCurrentIndex(3);
        on_outputPushButton_clicked();
    }
}
bool LinearAlgebra::eventFilter(QObject *target, QEvent *event)
{
   if(target ==inputTableWidget)//此判断可以省略,此程序中必进入此判断，但是有此句判断让程序更加规范
   {
         if (event->type() == QEvent::KeyPress)
         {
             QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
             int code=keyEvent->key();
             if(code==Qt::Key_Return||code==Qt::Key_Enter)
             {

                 int row=inputTableWidget->currentRow();
                 int col=inputTableWidget->currentColumn();
                 int rowNum=inputRowSpinBox->value(),colNum=inputColSpinBox->value();
                 if(row+1==rowNum&&col+1==colNum)
                 {
                     inputTableWidget->setCurrentCell(0,0);
                     fileInCheckBox->setChecked(false);
                     on_inputPushButton_clicked();
                     return true;
                 }
                 else
                 {
                     if(col+1==colNum)
                     {inputTableWidget->setCurrentCell(row+1,0);}
                     else
                     {inputTableWidget->setCurrentCell(row,col+1);}
                     return true;
                 }
             }
             else
             {
                 return false;
             }
         }
         else
             return false;
   }
   return QObject::eventFilter(target, event);
}
void LinearAlgebra::dragEnterEvent(QDragEnterEvent *event)
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
void LinearAlgebra::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls=event->mimeData()->urls();
    if(urls.isEmpty()){return ;}
    QString fileName=urls.first().toLocalFile();
    if(fileName.isEmpty()){return ;}
    readFile(fileName);
    return ;
}
bool LinearAlgebra::readFile(const QString &fileName)
{
    QFile file(fileName);
    QTextStream in(&file);
    if(file.open(QIODevice::ReadOnly))//可以打开
    {
        int row,col;
        int Index=inputComboBox->currentIndex();
        in>>row>>col;
        if(row>100||col>100||row<1||col<1)
        {
            QMessageBox::warning(this, tr("LinearAlgebra Tool"),
            tr("The rows or cols are beyond range！"),QMessageBox::Ok);
            return 0;
        }
        matrix[Index]=new double*[row];      //分配空间
        for(int i=0;i<row;i++)
            matrix[Index][i]=new double[col];
        QRegExp regExp("^(-?\\d+)(\\.\\d+)?(/\\d+(\\.\\d+)?)?$");
        QString str;
        int ret;
        for(int i=0;i<row;i++)
            for(int j=0;j<col;j++){
                in>>str;
                if(regExp.indexIn(str)!=-1){
                    ret=str.indexOf('/');
                    if(ret==-1)
                       matrix[Index][i][j]=str.toDouble();
                    else
                    {
                        double dl1,dl2;
                        dl1=str.left(ret).toDouble();
                        dl2=str.right(str.length()-ret-1).toDouble();
                        matrix[Index][i][j]=dl1/dl2;
                    }
                }
                else
                {
                    if(str.contains('e'))
                    {
                        QRegExp r("^([+-]?\\d+)(\\.\\d+)?([e][+-]?\\d+)$");
                        if(r.indexIn(str)!=-1){
                            matrix[Index][i][j]=str.toDouble();
                            continue;
                        }
                    }
                    QMessageBox::warning(this, tr("LinearAlgebra Tool"),
                    tr("The item(%1 , %2)is illegal！\nPlease check whether there are abnormal characters or Spaces")
                                       .arg(i+1).arg(j+1),QMessageBox::Ok);
                    return false;
                }
            }
        file.close();
        inputRowSpinBox->setValue(row);
        inputColSpinBox->setValue(col);
        inputTableWidget->setRowCount(row);
        inputTableWidget->setColumnCount(col);
        for(int i=0;i<row;i++)
        {
            for(int j=0;j<col;j++)
            {
                str.setNum(matrix[Index][i][j],'g');
                inputTableWidget->setItem(i,j,new QTableWidgetItem(str));
            }
        }
        isAssiged[Index]=true;
        matrixRow[Index]=row;matrixCol[Index]=col;
        isLadder[Index]=false;
        return true;
    }
    return false;
}
void LinearAlgebra::assign(int Index1, int Index2)
{
    if(Index1==Index2)
        return ;
    int row=matrixRow[Index1]=matrixRow[Index2];
    int col=matrixCol[Index1]=matrixCol[Index2];
    isAssiged[Index1]=true;
    isLadder[Index1]=false;
    matrix[Index1]=new double*[row];      //分配空间
    for(int i=0;i<row;i++)
    {
        matrix[Index1][i]=new double[col];
        for(int j=0;j<col;j++)
            matrix[Index1][i][j]=matrix[Index2][i][j];
    }
}
void LinearAlgebra::assign(int Index, double **a, int row, int col)
{
    matrixRow[Index]=row;
    matrixCol[Index]=col;
    isAssiged[Index]=true;
    isLadder[Index]=false;
    matrix[Index]=new double*[row];      //分配空间
    for(int i=0;i<row;i++)
    {
        matrix[Index][i]=new double[col];
        for(int j=0;j<col;j++)
            matrix[Index][i][j]=a[i][j];
    }
}
bool LinearAlgebra::add(int Index,int Index1,int Index2)
{
    if(matrixRow[Index1]!=matrixRow[Index2]||matrixCol[Index1]!=matrixCol[Index2])
    {
        QMessageBox::warning(this, tr("LinearAlgebra Tool"),
        tr("It does not comply with the addition principle！"),QMessageBox::Ok);
        return 0;
    }
    int row=matrixRow[Index]=matrixRow[Index1];
    int col=matrixCol[Index]=matrixCol[Index1];
    isAssiged[Index]=true;
    isLadder[Index]=false;
    if(Index==Index1)
    {
        for(int i=0;i<row;i++)
        {
            for(int j=0;j<col;j++)
                matrix[Index][i][j]+=matrix[Index2][i][j];
        }
        return 1;
    }
    if(Index==Index2)
    {
        for(int i=0;i<row;i++)
        {
            for(int j=0;j<col;j++)
                matrix[Index][i][j]+=matrix[Index1][i][j];
        }
        return 1;
    }
    matrix[Index]=new double*[row];      //分配空间
    for(int i=0;i<row;i++)
    {
        matrix[Index][i]=new double[col];
        for(int j=0;j<col;j++)
            matrix[Index][i][j]=matrix[Index1][i][j]+matrix[Index2][i][j];
    }
    return 1;
}
bool LinearAlgebra::subtract(int Index, int Index1, int Index2)
{
    if(matrixRow[Index1]!=matrixRow[Index2]||matrixCol[Index1]!=matrixCol[Index2])
    {
        QMessageBox::warning(this, tr("LinearAlgebra Tool"),
        tr("It does not comply with the subtraction principle！"),QMessageBox::Ok);
        return 0;
    }
    int row=matrixRow[Index]=matrixRow[Index1];
    int col=matrixCol[Index]=matrixCol[Index1];
    isAssiged[Index]=true;
    isLadder[Index]=false;
    if(Index==Index1)
    {
        for(int i=0;i<row;i++)
        {
            for(int j=0;j<col;j++)
                matrix[Index][i][j]-=matrix[Index2][i][j];
        }
        return 1;
    }
    if(Index==Index2)
    {
        for(int i=0;i<row;i++)
        {
            for(int j=0;j<col;j++)
                matrix[Index][i][j]=matrix[Index1][i][j]-matrix[Index2][i][j];
        }
        return 1;
    }
    matrix[Index]=new double*[row];      //分配空间
    for(int i=0;i<row;i++)
    {
        matrix[Index][i]=new double[col];
        for(int j=0;j<col;j++)
            matrix[Index][i][j]=matrix[Index1][i][j]-matrix[Index2][i][j];
    }
    return 1;
}
bool LinearAlgebra::multiply(int Index, int Index1, int Index2)
{
    int i,j,k;
    if(matrixCol[Index1]!=matrixRow[Index2])
    {
        QMessageBox::warning(this, tr("LinearAlgebra Tool"),
        tr("It does not meet the multiplication principle！"),QMessageBox::Ok);
        return 0;
    }
    double **dl;
    int row=matrixRow[Index1];
    int col=matrixCol[Index2];
    int col_row=matrixCol[Index1];
    dl=new double *[row];
    for(i=0;i<row;i++)
    {
        dl[i]=new double[col];
    }
    for(i=0;i<row;i++)
        for(j=0;j<col;j++)
        {
            for(k=0,dl[i][j]=0;k<col_row;k++)
                dl[i][j]+=matrix[Index1][i][k]*matrix[Index2][k][j];
        }
    isAssiged[Index]=true;
    isLadder[Index]=false;
    matrix[Index]=new double*[row];
    matrixRow[Index]=row,matrixCol[Index]=col;
    for(i=0;i<row;i++)
    {
        matrix[Index][i]=new double[col];
        for(j=0;j<col;j++)
        {matrix[Index][i][j]=dl[i][j];}
        delete []dl[i];
    }
    delete []dl;
    return 1;
}
void LinearAlgebra::multiply(int Index1, double n, int Index2)
{
    int i,j;
    int row=matrixRow[Index2],col=matrixCol[Index1];
    isAssiged[Index1]=true;
    isLadder[Index1]=false;
    if(Index1==Index2)
    {
       isLadder[Index1]=false;
       for(i=0;i<row;++i)
           for(j=0;j<col;++j)
           {matrix[Index1][i][j]*=n;}
    }
    else
    {
        matrix[Index1]=new double*[row];
        matrixRow[Index1]=row,matrixCol[Index1]=col;
        for(i=0;i<row;i++)
        {
            matrix[Index1][i]=new double[col];
            for(j=0;j<col;j++)
            {matrix[Index1][i][j]=n*matrix[Index2][i][j];}
        }
    }
}
bool LinearAlgebra::power(int Index1, int Index2, int n)
{
    if(matrixCol[Index2]!=matrixRow[Index2])
    {
        QMessageBox::warning(this, tr("LinearAlgebra Tool"),
        tr("It does not meet the multiplication principle！"),QMessageBox::Ok);
        return 0;
    }
    assign(3,Index2);
    if(n&1)
        assign(Index1,Index2);
    else   //给矩阵Index1赋予单位矩阵
    {
        int row=matrixRow[Index1]=matrixRow[Index2];
        int col=matrixCol[Index1]=matrixCol[Index2];
        isAssiged[Index1]=true;
        isLadder[Index1]=false;
        matrix[Index1]=new double*[row];      //分配空间
        for(int i=0;i<row;i++)
        {
            matrix[Index1][i]=new double[col];
            for(int j=0;j<col;j++)
                matrix[Index1][i][j]=0;
            matrix[Index1][i][i]=1;
        }
    }
    n>>=1;
    for(;n>0;n>>=1)
    {
        multiply(3,3,3);
        if(n&1)
        multiply(Index1,Index1,3);
    }
    return true;
}
bool LinearAlgebra::transpose(int Index)
{
    int col=matrixCol[3]=matrixRow[Index];
    int row=matrixRow[3]=matrixCol[Index];
    isAssiged[3]=true;
    isLadder[3]=false;
    matrix[3]=new double*[row];
    for(int i=0;i<row;i++)
    {
        matrix[3][i]=new double[col];
        for(int j=0;j<col;j++)
        {matrix[3][i][j]=matrix[Index][j][i];}
    }
    return 1;
}
bool LinearAlgebra::adjoint(int Index)
{
    int row=matrixRow[Index],col=matrixCol[Index];
    if(row!=col)
    {
        QMessageBox::warning(this,tr("LinearAlgebra Tool"),
                   tr("Non-square matrix can not seek adjoint matrix！"),QMessageBox::Ok);
        return 0;
    }
    det(Index,false);
    if(Rank[Index]<row-1)
    {
        QMessageBox::information(this,tr("LinearAlgebra Tool"),tr("The adjoint matrix is zero matrix！"),QMessageBox::Ok);
        return 0;
    }
    else
    {     
        if(Rank[Index]==row)
        {
            inver(Index);
            multiply(3,Det[Index],3);
            return 1;
        }
        else
        {
            //将阶梯矩阵转化为等价标准型矩阵
            double ratio;
            int i,j,k;
            isLadder[Index]=false;           //阶梯矩阵改变之后将isLadder赋为false
            for(k=Rank[Index]-1;k>0;--k)
            {
                for(i=k-1;i>=0;i--)
                {
                    if(!ladderMatrix[Index][i][k])
                        continue;
                    ratio=ladderMatrix[Index][i][k]/ladderMatrix[Index][k][k];
                    for(j=k+1;j<col;++j)
                    {
                        ladderMatrix[Index][i][j]-=ratio*ladderMatrix[Index][k][j];
                    }
                    ladderMatrix[Index][i][k]=0;
                }
            }
            double *x,*y;
            x=new double [row];
            y=new double [row];
            x[0]=-ladderMatrix[Index][0][col-1]/ladderMatrix[Index][0][0];
            for(i=1;i<row-1;i++)
            {
                x[i]=-ladderMatrix[Index][i][col-1]/ladderMatrix[Index][i][i];
                x[i]/=x[0];
            }
            x[row-1]=1/x[0],x[0]=1;
            for(i=0;i<Rank[Index];i++)
            {
                if(pivcol[Index][i]!=i)
                {qSwap(x[i],x[pivcol[Index][i]]);}
            }
            matrixRow[3]=matrixCol[3]=row-1;
            matrix[3]=new double*[row-1];
            for(i=0;i<row-1;i++)
                matrix[3][i]=new double [col-1];
            for(i=0;i<row;i++)
            {
                int l=0;
                for(j=0;j<row;j++)
                {
                    if(j==i)continue;
                    for(k=1;k<col;k++)
                    {
                        matrix[3][l][k-1]=matrix[Index][j][k];
                    }
                    l++;
                }
                isLadder[3]=false;  det(3);
                if(i&1)
                    y[i]=-Det[3];
                else
                    y[i]=Det[3];
            }
            matrixRow[3]=matrixCol[3]=row;
            matrix[3]=new double*[row];
            for(i=0;i<row;i++){
                matrix[3][i]=new double [col];
                for(j=0;j<col;j++)
                    matrix[3][i][j]=x[i]*y[j];
            }
            isAssiged[3]=true;
            isLadder[3]=false;
            return 1;
        }
    }
}
bool LinearAlgebra::ladder(int Index)
{
    int i,j,k,*pivrow;
    int row=matrixRow[Index],col=matrixCol[Index];
    double ratio,pivot;         //pivot主元，ratio比值
    const double eps=1e-6;
    int min=row<col?row:col;    //rank(A)<=min(row,col)
    pivcol[Index]=new int[min];        //分配记录交换列数组的空间
    pivrow=new int[min];        //分配记录交换行数组的空间
    unsigned countcol=0;        //记录列变换的次数
    ladderSwapCount[Index]=0;

    ladderMatrix[Index]=new double*[row];
    for(i=0;i<row;++i)               //给阶梯矩阵初始化
    {
        ladderMatrix[Index][i]=new double[col];
        for(j=0;j<col;++j)
        ladderMatrix[Index][i][j]=matrix[Index][i][j];
    }

    for(k=0;k<min;++k)             //部分主元高斯消元
    {
        pivot=qAbs(ladderMatrix[Index][k][k]);
        pivrow[k]=k;               //记录行变换
        pivcol[Index][k]=k;               //记录列变换
        for(j=k;j<row;++j)         //在第k列中逐行寻找非零元素
        {
            if(qAbs(ladderMatrix[Index][j][k])>eps)
            {
                pivot=qAbs(ladderMatrix[Index][j][k]);
                pivrow[k]=j;
                break;
            }
        }
        if(j==row)         //在第k列中没找到非零元素
        {
            countcol++;   //列变换次数加1
            for(i=col-countcol;i>k;--i)     //选取非零的主元
            {//两个循环的顺序是为了减少列交换,且列序递减
                for(j=k;j<row;++j)
                {
                    if(qAbs(ladderMatrix[Index][j][i])>eps)
                    {
                        pivot=qAbs(ladderMatrix[Index][j][i]);
                        pivrow[k]=j;
                        pivcol[Index][k]=i;
                        break;
                    }
                }
                if(pivot>eps)
                   break;
            }
        }
        if(pivot<=eps)//若剩下元素全为零，则已经阶梯化
           break;
        if(pivrow[k]!=k)
        {
            ladderSwapCount[Index]++;
            for(j=k;j<col;++j)
            {
                qSwap(ladderMatrix[Index][pivrow[k]][j],
                      ladderMatrix[Index][k][j]);
            }
        }
        if(pivcol[Index][k]!=k)
        {
            ladderSwapCount[Index]++;
            for(j=0;j<row;++j)
            {
                qSwap(ladderMatrix[Index][j][pivcol[Index][k]],
                      ladderMatrix[Index][j][k]);
            }
        }
        for(i=k+1;i<row;++i)
        {
            if(!ladderMatrix[Index][i][k])
                continue;
            ratio=ladderMatrix[Index][i][k]/ladderMatrix[Index][k][k];
            for(j=k+1;j<col;++j)
            {
                ladderMatrix[Index][i][j]-=ratio*ladderMatrix[Index][k][j];
            }
            ladderMatrix[Index][i][k]=0;
        }
    }
    Rank[Index]=k;   //记录矩阵的秩
    isLadder[Index]=true;
    assign(3,ladderMatrix[Index],row,col);   //将阶梯矩阵赋给临时矩阵
    delete []pivrow;
    return true;
}
int  LinearAlgebra::augLadder()
{
    int i,j,k,*augPivrow;
    int row=matrixRow[3],col=matrixCol[3];
    double ratio,pivot;          //pivot主元，ratio比值
    const double eps=1e-6;
    int min=row<col?row:col;
    augPivcol=new int[min];      //分配记录交换列数组的空间
    augPivrow=new int[min];      //分配记录交换行数组的空间
    unsigned countcol=0;         //记录列变换的次数

    for(k=0;k<min;++k)           //部分主元高斯消元
    {
        pivot=qAbs(matrix[3][k][k]);
        augPivrow[k]=k;          //记录行变换
        augPivcol[k]=k;          //记录列变换
        for(j=k;j<row;++j)       //在第k列中逐行寻找非零元素
        {
            if(qAbs(matrix[3][j][k])>eps)
            {
                pivot=qAbs(matrix[3][j][k]);
                augPivrow[k]=j;
                break;
            }
        }
        if(j==row)                //在第k列中没找到非零元素
        {
            countcol++;           //列变换次数加1
            for(i=col-countcol;i>k;--i)//选取非零的主元
            {//两个循环的顺序是为了减少列交换,且列序递减
                for(j=k;j<row;++j)
                {
                    if(qAbs(matrix[3][j][i])>eps)
                    {
                        pivot=qAbs(matrix[3][j][i]);
                        augPivrow[k]=j;
                        augPivcol[k]=i;
                        break;
                    }
                }
                if(pivot>eps)
                   break;
            }
        }
        if(pivot<=eps)             //若剩下元素全为零，则已经阶梯化
           break;
        if(augPivrow[k]!=k)
        {
            for(j=k;j<=col;++j)
            {
                qSwap(matrix[3][augPivrow[k]][j],matrix[3][k][j]);
            }
        }
        if(augPivcol[k]!=k)
        {
            for(j=0;j<row;++j)
            {
                qSwap(matrix[3][j][augPivcol[k]],matrix[3][j][k]);
            }
        }
        for(i=k+1;i<row;++i)
        {
            if(!matrix[3][i][k])
                continue;
            ratio=matrix[3][i][k]/matrix[3][k][k];
            for(j=k+1;j<=col;++j)
            {
                matrix[3][i][j]-=ratio*matrix[3][k][j];
            }
            matrix[3][i][k]=0;
        }
    }
    Rank[3]=k;                      //记录矩阵的秩
    if(k<row&&qAbs(matrix[3][k][col])>eps) //检查常数k行是否为非零元素
    {k++;}
    delete []augPivrow;
    return k;                       //增广矩阵的秩
}
void LinearAlgebra::rank(int Index)
{
    if(!isLadder[Index])
        this->ladder(Index);
    QMessageBox::information(this, tr("LinearAlgebra Tool"),
    tr("The rank of the matrix is：%1").arg(Rank[Index]),QMessageBox::Ok);
     return ;
}
void LinearAlgebra::det(int Index,bool val)
{
    int row=matrixRow[Index],col=matrixCol[Index];
    if(row!=col)
    {
        QMessageBox::warning(this,tr("LinearAlgebra Tool"),
               tr("Non-square matrix can not seek determinant！"),QMessageBox::Ok);
        return ;
    }
    if(!this->isLadder[Index])
        {this->ladder(Index);}

    if(Rank[Index]<row)
    { Det[Index]=0;}
    else
    {
        Det[Index]=1;
        for(int i=0;i<row;i++)
        {Det[Index]*=ladderMatrix[Index][i][i];}
        if(this->ladderSwapCount[Index]&1)
            Det[Index]=-Det[Index];
        if(qAbs(Det[Index])<=1e-5&&qAbs(Det[Index])>0)
        {
            QMessageBox::information(this,tr("LinearAlgebra Tool"),
            tr("The value of the determinant is：%1\nBut it's an ill-conditioned matrix!").arg(Det[Index]),QMessageBox::Ok);
            return;
        }
    }
    if(val==true){
        QMessageBox::information(this, tr("LinearAlgebra Tool"),
        tr("The value of the determinant is：%1").arg(Det[Index]),QMessageBox::Ok);
    }
    return ;
}
bool LinearAlgebra::inver(int Index)
{
    int row=matrixRow[Index],col=matrixCol[Index];
    if(row!=col)
    {
        QMessageBox::warning(this,tr("LinearAlgebra Tool"),
          tr("Non-square matrix can not seek inverse matrix！"),QMessageBox::Ok);
        return 0;
    }
    int i,j,k;
    const double eps=1e-8;
    double ratio;                         //ratio比值
    double **reverse;                     //(A|E)
    reverse =new double*[row];
    for(i=0;i<row;++i)
        {reverse[i]=new double [2*col];}
    for(i=0;i<row;++i)
    {
        for(j=0;j<col;j++)                //原矩阵
        {reverse[i][j]=matrix[Index][i][j];}
        for(j=col;j<2*col;++j)            //单位矩阵
        {
            if(j-i==col)  reverse[i][j]=1;
            else   reverse[i][j]=0;
        }
    }
    for(k=0;k<row;++k)                    //主对角线元素
    {
        for(i=k;i<row;++i)                //在第k列中逐行寻找非零元素
        {
            if(qAbs(reverse[i][k])>eps)
            {
                if(i!=k)
                {
                    for(j=k;j<2*col;++j) //交换两行元素
                    {
                        qSwap(reverse[i][j],reverse[k][j]);
                    }
                }
                break;
            }
        }
        if(i==row)                        //当i==row时，行列式的值必为零
        {
            QMessageBox::warning(0,tr("LinearAlgebra Tool"),
                     tr("The determinant is zero, so there is no inverse matrix！"),QMessageBox::Ok);
            for(int i=0;i<row;i++)
            {delete [] reverse[i];}
            delete []reverse;
            return 0;
        }
        for(i=k+1;i<row;++i)
        {
            if(!reverse[i][k])
                continue;
            ratio=reverse[i][k]/reverse[k][k];
            for(j=k;j<2*col;++j)
            {reverse[i][j]-=ratio*reverse[k][j];}
        }
    }

    for(k=row-1;k>=0;--k)
    {
        for(j=col;j<2*col;++j)     //将主对角线元素化为1
        {reverse[k][j]/=reverse[k][k];}
         reverse[k][k]=1;
        for(i=k-1;i>=0;--i)
        {
            if(!reverse[i][k])
                continue;
            ratio=reverse[i][k];
            for(j=k;j<2*col;++j)
            {reverse[i][j]-=ratio*reverse[k][j];}
        }
    }

    matrixRow[3]=row,matrixCol[3]=col;
    isAssiged[3]=true;
    isLadder[3]=false;
    matrix[3]=new double*[row];
    for(int i=0;i<row;i++)
    {matrix[3][i]=new double[col];}
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++)
        {
            if(qAbs(reverse[i][j+col])>1e-5)
                matrix[3][i][j]=reverse[i][j+col];
            else
                matrix[3][i][j]=0;
        }
    }
    for(int i=0;i<row;i++)
    {delete [] reverse[i];}
    delete []reverse;
    return 1;
}
bool LinearAlgebra::generInver(int Index)
{
    double  **a, **u, **v, **aa;
    double  *s, *e, *w, fg[2], cs[2];
    double eps=1e-6;
    int m=matrixRow[Index],n=matrixCol[Index],i,j,k,l,ka;
    a = new double*[m];   //动态分配内存空间
    u = new double*[m];
    v = new double*[n];
    aa = new double*[n];
    for (i=0; i<m; i++)
    {
        a[i] = new double[n];
        u[i] = new double[m];
    }
    for (i=0; i<n; i++)
    {
        v[i] = new double[n];
        aa[i] = new double[m];
    }
    for (i=0; i<m; i++)
       for (j=0; j<n; j++)
           a[i][j]=matrix[Index][i][j];
    for (i=0; i<m; i++)
         for (j=0; j<m; j++)
              u[i][j] = 0;
    for (i=0; i<n; i++)
      for (j=0; j<n; j++)
          v[i][j] = 0;
    ka = m + 1;
    if (m < n)  ka = n + 1;
    s = new double[ka];
    e = new double[ka];
    w = new double[ka];
   /*----------以下均为奇异值分解---------*/
      int it,ll,kk,mm,nn,m1,ks;
      double d,dd,t,sm,sm1,em1,sk,ek,b,c,shh;
      it=60; k=n;
      if (m-1<n) k=m-1;
      l=m;
      if (n-2<m) l=n-2;
      if (l<0) l=0;
      ll=k;
      if (l>k) ll=l;
      if (ll>=1)
      {
          for (kk=1; kk<=ll; kk++)
          {
              if (kk<=k)
              {
                  d=0.0;
                  for (i=kk; i<=m; i++)
                      d=d+a[i-1][kk-1]*a[i-1][kk-1];
                  s[kk-1]=sqrt(d);
                  if (s[kk-1]!=0.0)
                  {
                      if (a[kk-1][kk-1]!=0.0)
                      {
                          s[kk-1]=qAbs(s[kk-1]);
                          if (a[kk-1][kk-1]<0.0)  s[kk-1]=-s[kk-1];
                      }
                      for (i=kk; i<=m; i++)
                      {
                          a[i-1][kk-1]=a[i-1][kk-1]/s[kk-1];
                      }
                      a[kk-1][kk-1]=1.0+a[kk-1][kk-1];
                  }
                  s[kk-1]=-s[kk-1];
              }
              if (n>=kk+1)
              {
                  for (j=kk+1; j<=n; j++)
                  {
                      if ((kk<=k)&&(s[kk-1]!=0.0))
                      {
                          d=0.0;
                          for (i=kk; i<=m; i++)
                          {
                              d=d+a[i-1][kk-1]*a[i-1][j-1];
                          }
                          d=-d/a[kk-1][kk-1];
                          for (i=kk; i<=m; i++)
                          {
                              a[i-1][j-1]=a[i-1][j-1]+d*a[i-1][kk-1];
                          }
                      }
                    e[j-1]=a[kk-1][j-1];
                  }
              }
              if (kk<=k)
              {
                  for (i=kk; i<=m; i++)
                  {
                      u[i-1][kk-1]=a[i-1][kk-1];
                  }
              }
              if (kk<=l)
              {
                  d=0.0;
                  for (i=kk+1; i<=n; i++)
                      d=d+e[i-1]*e[i-1];
                  e[kk-1]=sqrt(d);
                  if (e[kk-1]!=0.0)
                  {
                      if (e[kk]!=0.0)
                      {
                          e[kk-1]=qAbs(e[kk-1]);
                          if (e[kk]<0.0) e[kk-1]=-e[kk-1];
                      }
                      for (i=kk+1; i<=n; i++)
                          e[i-1]=e[i-1]/e[kk-1];
                      e[kk]=1.0+e[kk];
                  }
                  e[kk-1]=-e[kk-1];
                  if ((kk+1<=m)&&(e[kk-1]!=0.0))
                  {
                      for (i=kk+1; i<=m; i++) w[i-1]=0.0;
                      for (j=kk+1; j<=n; j++)
                      for (i=kk+1; i<=m; i++)
                           w[i-1]=w[i-1]+e[j-1]*a[i-1][j-1];
                      for (j=kk+1; j<=n; j++)
                      for (i=kk+1; i<=m; i++)
                      {
                          a[i-1][j-1]=a[i-1][j-1]-w[i-1]*e[j-1]/e[kk];
                      }
                  }
                  for (i=kk+1; i<=n; i++)
                       v[i-1][kk-1]=e[i-1];
              }
          }
      }
      mm=n;
      if (m+1<n) mm=m+1;
      if (k<n) s[k]=a[k][k];
      if (m<mm) s[mm-1]=0.0;
      if (l+1<mm) e[l]=a[l][mm-1];
      e[mm-1]=0.0;
      nn=m;
      if (m>n) nn=n;
      if (nn>=k+1)
      {
          for (j=k+1; j<=nn; j++)
          {
              for (i=1; i<=m; i++)   u[i-1][j-1]=0.0;
              u[j-1][j-1]=1.0;
          }
      }
      if (k>=1)
      {
          for (ll=1; ll<=k; ll++)
          {
              kk=k-ll+1;
              if (s[kk-1]!=0.0)
              {
                  if (nn>=kk+1)
                    for (j=kk+1; j<=nn; j++)
                    {
                        d=0.0;
                        for (i=kk; i<=m; i++)
                        {
                            d=d+u[i-1][kk-1]*u[i-1][j-1]/u[kk-1][kk-1];
                        }
                        d=-d;
                        for (i=kk; i<=m; i++)
                        {
                            u[i-1][j-1]=u[i-1][j-1]+d*u[i-1][kk-1];
                        }
                    }
                    for (i=kk; i<=m; i++)
                        u[i-1][kk-1]=-u[i-1][kk-1];
                    u[kk-1][kk-1]=1.0+u[kk-1][kk-1];
                    if (kk-1>=1)
                      for (i=1; i<=kk-1; i++)  u[i-1][kk-1]=0.0;
              }
              else
              {
                  for (i=1; i<=m; i++)  u[i-1][kk-1]=0.0;
                  u[kk-1][kk-1]=1.0;
              }
          }
      }
      for (ll=1; ll<=n; ll++)
      {
          kk=n-ll+1;
          if ((kk<=l)&&(e[kk-1]!=0.0))
          {
              for (j=kk+1; j<=n; j++)
              {
                  d=0.0;
                  for (i=kk+1; i<=n; i++)
                  {
                      d=d+v[i-1][kk-1]*v[i-1][j-1]/v[kk][kk-1];
                  }
                  d=-d;
                  for (i=kk+1; i<=n; i++)
                  {
                      v[i-1][j-1]=v[i-1][j-1]+d*v[i-1][kk-1];
                  }
              }
          }
          for (i=1; i<=n; i++)  v[i-1][kk-1]=0.0;
          v[kk-1][kk-1]=1.0;
      }
      for (i=1; i<=m; i++)
      for (j=1; j<=n; j++)  a[i-1][j-1]=0.0;
      m1=mm; it=60;
      while(1)
      {
          if (mm==0)
          {
              double d;
              if (m>=n) i=n;
              else i=m;
              for (j=1; j<=i-1; j++)
              {
                  a[j-1][j-1]=s[j-1];
                  a[j-1][j]=e[j-1];
              }
              a[i-1][i-1]=s[i-1];
              if (m<n) a[i-1][i]=e[i-1];
              for (i=1; i<=n-1; i++)
              for (j=i+1; j<=n; j++)
              {
                  d=v[i-1][j-1];
                  v[i-1][j-1]=v[j-1][i-1];
                  v[j-1][i-1]=d;
              }
              break;
          }
          if(it==0)
          {
              QMessageBox::warning(this,tr("LinearAlgebra Tool"),
                          tr("Verry sorry,the program fails！"),QMessageBox::Ok);
              return 0;
          }
          kk=mm-1;
          while ((kk!=0)&&(qAbs(e[kk-1])!=0.0))
          {
              d=qAbs(s[kk-1])+qAbs(s[kk]);
              dd=qAbs(e[kk-1]);
              if (dd>eps*d) kk=kk-1;
              else e[kk-1]=0.0;
          }
          if (kk==mm-1)
          {
              kk=kk+1;
              if (s[kk-1]<0.0)
              {
                  s[kk-1]=-s[kk-1];
                  for (i=1; i<=n; i++)
                     v[i-1][kk-1]=-v[i-1][kk-1];
              }
              while ((kk!=m1)&&(s[kk-1]<s[kk]))
              {
                  d=s[kk-1]; s[kk-1]=s[kk]; s[kk]=d;
                  if (kk<n)
                    for (i=1; i<=n; i++)
                    {
                        d=v[i-1][kk-1];
                        v[i-1][kk-1]=v[i-1][kk];
                        v[i-1][kk]=d;
                    }
                  if (kk<m)
                    for (i=1; i<=m; i++)
                    {
                        d=u[i-1][kk-1];
                        u[i-1][kk-1]=u[i-1][kk];
                        u[i-1][kk]=d;
                    }
                  kk=kk+1;
              }
              it=60;
              mm--;
          }
          else
          {
              ks=mm;
              while ((ks>kk)&&(qAbs(s[ks-1])!=0.0))
              {
                  d=0.0;
                  if (ks!=mm) d=d+qAbs(e[ks-1]);
                  if (ks!=kk+1) d=d+qAbs(e[ks-2]);
                  dd=qAbs(s[ks-1]);
                  if (dd>eps*d) ks=ks-1;
                  else s[ks-1]=0.0;
              }
              if (ks==kk)
              {
                  kk=kk+1;
                  d=qAbs(s[mm-1]);
                  t=qAbs(s[mm-2]);
                  if (t>d) d=t;
                  t=qAbs(e[mm-2]);
                  if (t>d) d=t;
                  t=qAbs(s[kk-1]);
                  if (t>d) d=t;
                  t=qAbs(e[kk-1]);
                  if (t>d) d=t;
                  sm=s[mm-1]/d; sm1=s[mm-2]/d;
                  em1=e[mm-2]/d;
                  sk=s[kk-1]/d; ek=e[kk-1]/d;
                  b=((sm1+sm)*(sm1-sm)+em1*em1)/2.0;
                  c=sm*em1; c=c*c; shh=0.0;
                  if ((b!=0.0)||(c!=0.0))
                  {
                      shh=sqrt(b*b+c);
                      if (b<0.0) shh=-shh;
                      shh=c/(b+shh);
                  }
                  fg[0]=(sk+sm)*(sk-sm)-shh;
                  fg[1]=sk*ek;
                  for (i=kk; i<=mm-1; i++)
                  {
                      sss(fg,cs);
                      if (i!=kk) e[i-2]=fg[0];
                      fg[0]=cs[0]*s[i-1]+cs[1]*e[i-1];
                      e[i-1]=cs[0]*e[i-1]-cs[1]*s[i-1];
                      fg[1]=cs[1]*s[i];
                      s[i]=cs[0]*s[i];
                      if ((cs[0]!=1.0)||(cs[1]!=0.0))
                        for (j=1; j<=n; j++)
                        {
                            d=cs[0]*v[j-1][i-1]+cs[1]*v[j-1][i];
                            v[j-1][i]=-cs[1]*v[j-1][i-1]+cs[0]*v[j-1][i];
                            v[j-1][i-1]=d;
                        }
                      sss(fg,cs);
                      s[i-1]=fg[0];
                      fg[0]=cs[0]*e[i-1]+cs[1]*s[i];
                      s[i]=-cs[1]*e[i-1]+cs[0]*s[i];
                      fg[1]=cs[1]*e[i];
                      e[i]=cs[0]*e[i];
                      if (i<m)
                        if ((cs[0]!=1.0)||(cs[1]!=0.0))
                          for (j=1; j<=m; j++)
                          {
                              d=cs[0]*u[j-1][i-1]+cs[1]*u[j-1][i];
                              u[j-1][i]=-cs[1]*u[j-1][i-1]+cs[0]*u[j-1][i];
                              u[j-1][i-1]=d;
                          }
                  }
                  e[mm-2]=fg[0];
                  it=it-1;
              }
              else
              {
                  if (ks==mm)
                  {
                      kk=kk+1;
                      fg[1]=e[mm-2]; e[mm-2]=0.0;
                      for (ll=kk; ll<=mm-1; ll++)
                      {
                          i=mm+kk-ll-1;
                          fg[0]=s[i-1];
                          sss(fg,cs);
                          s[i-1]=fg[0];
                          if (i!=kk)
                          {
                              fg[1]=-cs[1]*e[i-2];
                              e[i-2]=cs[0]*e[i-2];
                          }
                          if ((cs[0]!=1.0)||(cs[1]!=0.0))
                            for (j=1; j<=n; j++)
                            {
                                d=cs[0]*v[j-1][i-1]+cs[1]*v[j-1][mm-1];
                                v[j-1][mm-1]=-cs[1]*v[j-1][i-1]+cs[0]*v[j-1][mm-1];
                                v[j-1][i-1]=d;
                            }
                      }
                  }
                  else
                  {
                      kk=ks+1;
                      fg[1]=e[kk-2];
                      e[kk-2]=0.0;
                      for (i=kk; i<=mm; i++)
                      {
                          fg[0]=s[i-1];
                          sss(fg,cs);
                          s[i-1]=fg[0];
                          fg[1]=-cs[1]*e[i-1];
                          e[i-1]=cs[0]*e[i-1];
                          if ((cs[0]!=1.0)||(cs[1]!=0.0))
                            for (j=1; j<=m; j++)
                            {
                                d=cs[0]*u[j-1][i-1]+cs[1]*u[j-1][kk-2];
                                u[j-1][kk-2]=-cs[1]*u[j-1][i-1]+cs[0]*u[j-1][kk-2];
                                u[j-1][i-1]=d;
                            }
                      }
                  }
              }
          }
      }
    j=n;
    if (m<n) j=m;
    j--;
    k=0;
    while ((k<=j)&&(a[k][k]!=0.0))
        k++;
    k--;
    for (i=0; i<n; i++)
    for (j=0; j<m; j++)
    {
        aa[i][j]=0.0;
        for (l=0; l<=k; l++)
        {
            aa[i][j]+=v[l][i]*u[j][l]/a[l][l];
        }
    }
    assign(3,aa,n,m);
    for (i=0; i<m; i++) { delete [] a[i]; }
    delete [] a;
    for (i=0; i<m; i++) { delete [] u[i]; }
    delete [] u;
    for (i=0; i<n; i++) { delete [] v[i]; }
    delete [] v;
    for (i=0; i<n; i++) { delete [] aa[i]; }
    delete [] aa;
    delete [] s, e, w;
    return 1;
}
bool LinearAlgebra::matrixQR(int Index)
{
      int m=matrixRow[Index],n=matrixCol[Index];
      int i,j,k,nn,jj;
      double u,alpha,w,t;
      double **a,**q;
      if (m<n)
      {
          QMessageBox::information(this, tr("LinearAlgebra Tool"),
          tr("The number of rows is less than the number of columns,QR decomposition fails."),QMessageBox::Ok);
          return 0;
      }
      a=new double*[m];
      for(int i=0;i<m;i++)
      {
          a[i]=new double[n];
          for(int j=0;j<n;j++)
              a[i][j]=matrix[Index][i][j];
      }
      q = new double*[m];
      for (i=0; i<=m-1; i++)
      {
          q[i] = new double[m];
          for (j=0; j<=m-1; j++)
          {q[i][j]=0.0;}
          q[i][i]=1.0;
      }
      nn=n;
      if (m==n) nn=m-1;
      for (k=0; k<=nn-1; k++)
      {
          u=0.0;
          for (i=k; i<=m-1; i++)
          {
              w=qAbs(a[i][k]);
              if (w>u) u=w;
          }
          alpha=0.0;
          for (i=k; i<=m-1; i++)
          { t=a[i][k]/u; alpha=alpha+t*t; }
          if (a[k][k]>0.0) u=-u;
          alpha=u*sqrt(alpha);
          if (alpha==0)
          {
              QMessageBox::information(this, tr("LinearAlgebra Tool"),
              tr("QR decomposition fails"),QMessageBox::Ok);
              return 0;
          }
          u=sqrt(2.0*alpha*(alpha-a[k][k]));
          if ((u+1.0)!=1.0)
          {
              a[k][k]=(a[k][k]-alpha)/u;
              for (i=k+1; i<=m-1; i++) a[i][k]=a[i][k]/u;
              for (j=0; j<=m-1; j++)
              {
                  t=0.0;
                  for (jj=k; jj<=m-1; jj++)
                      t=t+a[jj][k]*q[jj][j];
                  for (i=k; i<=m-1; i++)
                      q[i][j]=q[i][j]-2.0*t*a[i][k];
              }
              for (j=k+1; j<=n-1; j++)
              {
                  t=0.0;
                  for (jj=k; jj<=m-1; jj++)
                      t=t+a[jj][k]*a[jj][j];
                  for (i=k; i<=m-1; i++)
                      a[i][j]=a[i][j]-2.0*t*a[i][k];
              }
              a[k][k]=alpha;
              for (i=k+1; i<=m-1; i++)  a[i][k]=0.0;
          }
      }
      for (i=0; i<=m-2; i++)
      for (j=i+1; j<=m-1;j++)
      {
          qSwap(q[i][j],q[j][i]);
      }
      assign(3,q,m,m);
      QString str;
      QDialog *dialog=new QDialog(this);
      dialog->setWindowTitle(tr("LinearAlgebra Tool"));
      QPlainTextEdit *textEdit=new QPlainTextEdit;
      textEdit->setReadOnly(true);
      textEdit->appendPlainText(tr("The Q matrix has been outputed in Mat T，and R matrix is displayed in dialog."));
      for (i=0; i<m; i++)
      {
           for (j=0; j<n; j++)
           {
              if(j<i)
                  str+="0 ";
              else
              {
                  if(qAbs(a[i][j])<=1e-5)
                     str+="0 ";
                  else
                     str+=QString(tr("%1 ")).arg(a[i][j]);
              }
           }
           str+='\n';
      }
      textEdit->appendPlainText(str);
      textEdit->appendPlainText(tr("PS:\n"
          "The above QR decomposition is unique in additon to "
          "the absolute value of the diagonal elements in the diagonal matrix are equal to one."));
      QVBoxLayout *layout=new QVBoxLayout(dialog);
      layout->addWidget(textEdit);
      dialog->show();
      for (i=0; i<m; i++)
      {
          delete [] q[i];
          delete [] a[i];
      }
      delete [] a;
      delete [] q;
      return 1;
}

void LinearAlgebra::homogen(int Index)
{
    int col=matrixCol[Index];
    int i,j,k;
    const double eps=1e-8;
    if(!this->isLadder[Index])
        this->ladder(Index);
    if(Rank[Index]==col){
        QMessageBox::information(this, tr("LinearAlgebra Tool"),
        tr("The equations has only zero solution！"),QMessageBox::Ok);
    }
    else    //有无穷多组解
    {
        //将阶梯矩阵转化为等价标准型矩阵
        double ratio;
        isLadder[Index]=false;           //阶梯矩阵改变之后将isLadder赋为false
        for(k=Rank[Index]-1;k>0;--k)
        {
            for(i=k-1;i>=0;i--)
            {
                if(!ladderMatrix[Index][i][k])
                    continue;
                ratio=ladderMatrix[Index][i][k]/ladderMatrix[Index][k][k];
                for(j=k+1;j<col;++j)
                {
                    ladderMatrix[Index][i][j]-=ratio*ladderMatrix[Index][k][j];
                }
                ladderMatrix[Index][i][k]=0;
            }
        }
        unsigned r;
        int col_Rank=col-Rank[Index],s,*CONST;
        double **x;    //x解集
        x=new double *[col];
        for(i=0;i<col;++i)
        {x[i]=new double[col_Rank+1];}
        CONST=new int [col_Rank+1]; //记录任意常数的顺序
        for(i=Rank[Index];i<col;++i)
        {x[i][col_Rank]=1;}
        for(i=1;i<=col_Rank;i++)
        {CONST[i]=i;}       //记录任意常数的顺序
        for(i=0,s=0;i<Rank[Index];++i)
        {
            if(pivcol[Index][i]!=i)
            {
                x[i][col_Rank]=1;
                x[pivcol[Index][i]][col_Rank]=0;
                for(j=Rank[Index],r=0;j<col;++j,r++)  //还原x原来的解
                {x[pivcol[Index][i]][r]=-ladderMatrix[Index][i][j]/ladderMatrix[Index][i][i];}
                //改变任意常数的顺序
                CONST[col_Rank-s]=s+1;
                for(j=1;j<col_Rank-s;++j)
                {CONST[j]++;}
                ++s;
            }
            else
            {
                for(j=Rank[Index],r=0;j<col;++j,r++)  //还原x原来的解
                {x[i][r]=-ladderMatrix[Index][i][j]/ladderMatrix[Index][i][i];}
            }
        }
        QString str;
        QDialog *dialog=new QDialog(this);
        dialog->setWindowTitle(tr("LinearAlgebra Tool"));
        QPlainTextEdit *textEdit=new QPlainTextEdit;
        textEdit->setReadOnly(true);
        textEdit->appendPlainText(tr("The equations has infinitely many solutions:"));
        for(i=0,r=0;i<col;++i)
        {
            str.clear();
            str.append(tr("X%1 = ").arg(i+1));
            if(x[i][col_Rank]==1)
            {
                str.append(tr("C%1").arg(++r));
                textEdit->appendPlainText(str);
            }
            else
            {
                bool work=true;int s=1;
                for(j=0;j<col_Rank;++j,++s)
                {
                    if(!work&&x[i][j]>eps)
                        str.append(tr(" + "));
                    if(qAbs(x[i][j])>eps)
                    {
                        work=false;
                        str.append(tr("%1C%2").arg(x[i][j]).arg(CONST[s]));
                    }
                }
                if(work)str.append(tr("0"));
                textEdit->appendPlainText(str);
            }
        }
        for(i=0;i<col;i++)
        {delete []x[i];}
         delete []x;
       QVBoxLayout *mainlayout=new QVBoxLayout(dialog);
       mainlayout->addWidget(textEdit);
       dialog->show();
    }
    return ;
}

bool LinearAlgebra::inhomogen(int Index)
{
    int i,j,k;
    int row=matrixRow[3]=matrixRow[Index];
    int col=matrixCol[3]=matrixCol[Index]-1;
    if(col<1)
    {
        QMessageBox::warning(this, tr("LinearAlgebra Tool"),
        tr("Solving the non-homogeneous linear equations needs two columns at least！"),QMessageBox::Ok);
        return 0;
    }
    const double eps=1e-8;
    matrix[3]=new double*[row];      //分配阶梯矩阵的空间
    isAssiged[3]=true;
    for(i=0;i<row;++i)               //给阶梯矩阵初始化
    {
        matrix[3][i]=new double[col+1];
        for(j=0;j<=col;++j)
        {
            matrix[3][i][j]=matrix[Index][i][j];
        }
    }
    int augRank=augLadder();
    if(Rank[3]!=augRank)
    {
        QMessageBox::information(this, tr("LinearAlgebra Tool"),
        tr("The equations without solutions！"),QMessageBox::Ok);
        matrixCol[3]++;
        return 1;
    }
    double ratio;
    for(k=Rank[3]-1;k>0;--k)       //将阶梯矩阵标准化
    {
        for(i=k-1;i>=0;i--)
        {
            if(!matrix[3][i][k])
                continue;
            ratio=matrix[3][i][k]/matrix[3][k][k];
            for(j=k+1;j<=col;++j)
            {
                matrix[3][i][j]-=ratio*matrix[3][k][j];
            }
            matrix[3][i][k]=0;
        }
    }
    QDialog *dialog=new QDialog(this);
    dialog->setWindowTitle(tr("LinearAlgebra Tool"));
    QPlainTextEdit *textEdit=new QPlainTextEdit;
    textEdit->setReadOnly(true);
    if(Rank[3]==col)
    {
        textEdit->setPlainText(tr("The equation has a unique solution:"));
        double *x;
        x=new double [col];
        for(i=0;i<col;i++)
            x[i]=matrix[3][i][col]/matrix[3][i][i];
        for(i=0;i<col;++i)
        {
            if(qAbs(x[i])>eps)
                textEdit->appendPlainText(tr("X%1 = %2").arg(i+1).arg(x[i]));
            else
                textEdit->appendPlainText(tr("X%1 = 0").arg(i+1));
        }
        delete []x;
    }
    else
    {
        textEdit->setPlainText(tr("The equations has infinitely many solutions:"));
        int r,s;
        int col_Rank=col-augRank,*CONST;
        double **x;    //x解集
        x=new double *[col];
        for(i=0;i<col;++i)
        {x[i]=new double[col_Rank+2];}

        CONST=new int [col_Rank+1]; //记录任意常数的顺序
        for(i=augRank;i<col;++i)
        {x[i][col_Rank+1]=1;}
        for(i=1;i<=col_Rank;i++)
        {CONST[i]=i;}       //记录任意常数的顺序
        for(i=0,s=0;i<augRank;++i)
        {
            if(augPivcol[i]!=i)
            {
                x[i][col_Rank+1]=1;
                x[augPivcol[i]][col_Rank+1]=0;
                for(j=augRank,r=0;j<col;++j,r++)  //还原x原来的解
                {
                    x[augPivcol[i]][r]=-matrix[3][i][j]/matrix[3][i][i];
                }
                x[augPivcol[i]][r]=matrix[3][i][j]/matrix[3][i][i];
                //改变任意常数的顺序
                CONST[col_Rank-s]=s+1;
                for(j=1;j<col_Rank-s;++j)
                {CONST[j]++;}
                ++s;
            }
            else
            {
                for(j=augRank,r=0;j<col;++j,r++)  //还原x原来的解
                {
                    x[i][r]=-matrix[3][i][j]/matrix[3][i][i];
                }
                x[i][r]=matrix[3][i][j]/matrix[3][i][i];
            }
        }
        QString str;
        for(i=0,r=0;i<col;++i)
        {
            str.clear();
            str.append(tr("X%1 = ").arg(i+1));
            if(x[i][col_Rank+1]==1)
            {str.append(tr("C%1").arg(++r));}
            else
            {
                bool work=true;
                for(j=0,s=1;j<=col_Rank;++j,++s)
                {
                    if(!work&&x[i][j]>eps)
                        str.append(tr(" + "));
                    if(qAbs(x[i][j])>eps)
                    {
                        work=false;
                        if(j!=col_Rank)
                            str.append(tr("%1C%2").arg(x[i][j]).arg(CONST[s]));
                        else
                            str.append(tr("%1").arg(x[i][j]));
                    }
                }
                    if(work)
                        str.append(tr("0"));
            }
            textEdit->appendPlainText(str);
        }
        for(i=0;i<augRank;i++)
        {delete []x[i];}
        delete []x;
    }
    matrixCol[3]++;
    QVBoxLayout *mainlayout=new QVBoxLayout(dialog);
    mainlayout->addWidget(textEdit);
    dialog->show();
    return 1;
}

void LinearAlgebra::eigenValue(int Index,bool val)
{
    int row=matrixRow[Index],col=matrixCol[Index];
    if(row!=col)
    {
        QMessageBox::warning(this,tr("LinearAlgebra Tool"),
                    tr("The non-square matrix can not seek eigenvalues！"),QMessageBox::Ok);
        return ;
    }

    int i,j,k;
    double d,t;
    assign(3,Index);      //为临时矩阵赋值
    for (k=1;k<=row-2;k++)//执行初等相似变换
    {
         for (j=k,d=0;j<=row-1;j++)
         {
             t=matrix[3][j][k-1];
             if (qAbs(t)>qAbs(d))
             {d=t; i=j;}
         }
         if (d!=0)
         {
             if (i!=k)
             {
                 for (j=k-1; j<=row-1; j++)
                 {
                     qSwap(matrix[3][i][j],matrix[3][k][j]);
                 }
                 for (j=0; j<=row-1; j++)
                 {
                     qSwap(matrix[3][j][i],matrix[3][j][k]);
                 }
             }
             for (i=k+1; i<=row-1; i++)
             {
                 t=matrix[3][i][k-1]/d; matrix[3][i][k-1]=0;
                 for (j=k; j<=row-1; j++)
                     matrix[3][i][j]-=t*matrix[3][k][j];
                 for (j=0; j<=row-1; j++)
                     matrix[3][j][k]+=t*matrix[3][j][i];
             }
         }
     }
    int m,n,it,l;
    double b,c,w,g,xy,p,q,r,x,s,e,f,z,y;
    const double eps=1e-6;
    it=0; m=n=row;
    eigen_Value_Real[Index]=new double[n];
    eigen_Value_Comp[Index]=new double[n];
    while (m!=0)         //用QR方法计算全部特征值
    {
          l=m-1;
          while ((l>0)&&(qAbs(matrix[3][l][l-1])>eps*
                (qAbs(matrix[3][l-1][l-1])+qAbs(matrix[3][l][l])))) l--;
          if (l==m-1)
          {
              eigen_Value_Real[Index][m-1]=matrix[3][m-1][m-1];
              eigen_Value_Comp[Index][m-1]=0.0;
              m=m-1; it=0;
          }
          else if (l==m-2)
          {
              b=-(matrix[3][m-1][m-1]+matrix[3][m-2][m-2]);
              c=matrix[3][m-1][m-1]*matrix[3][m-2][m-2]-matrix[3][m-1][m-2]*matrix[3][m-2][m-1];
              w=b*b-4.0*c;
              y=qSqrt(qAbs(w));
              if (w>0.0)
              {
                  xy=1.0;
                  if (b<0.0) xy=-1.0;
                  eigen_Value_Real[Index][m-1]=(-b-xy*y)/2.0;
                  eigen_Value_Real[Index][m-2]=c/eigen_Value_Real[Index][m-1];
                  eigen_Value_Comp[Index][m-1]=0.0;
                  eigen_Value_Comp[Index][m-2]=0.0;
              }
              else
              {
                  eigen_Value_Real[Index][m-1]=-b/2.0;
                  eigen_Value_Real[Index][m-2]=eigen_Value_Real[Index][m-1];
                  eigen_Value_Comp[Index][m-1]=y/2.0;
                  eigen_Value_Comp[Index][m-2]=-eigen_Value_Comp[Index][m-1];
              }
              m=m-2; it=0;
          }
          else
          {
              if (it>=100)
              {
                  QMessageBox::warning(this,tr("LinearAlgebra Tool"),
                              tr("Verry sorry,the program fails！"),QMessageBox::Ok);
                  return ;
              }
              it=it+1;
              for (j=l+2; j<=m-1; j++)  matrix[3][j][j-2]=0.0;
              for (j=l+3; j<=m-1; j++)  matrix[3][j][j-3]=0.0;
              for (k=l; k<=m-2; k++)
              {
                  if (k!=l)
                  {
                      p=matrix[3][k][k-1]; q=matrix[3][k+1][k-1];
                      r=0.0;
                      if (k!=m-2)  r=matrix[3][k+2][k-1];
                  }
                  else
                  {
                      x=matrix[3][m-1][m-1]+matrix[3][m-2][m-2];
                      y=matrix[3][m-2][m-2]*matrix[3][m-1][m-1]-matrix[3][m-2][m-1]*matrix[3][m-1][m-2];
                      p=matrix[3][l][l]*(matrix[3][l][l]-x)+matrix[3][l][l+1]*matrix[3][l+1][l]+y;
                      q=matrix[3][l+1][l]*(matrix[3][l][l]+matrix[3][l+1][l+1]-x);
                      r=matrix[3][l+1][l]*matrix[3][l+2][l+1];
                  }
                  if(p||q||r)
                  {
                      xy=1.0;
                      if (p<0.0) xy=-1.0;
                      s=xy*sqrt(p*p+q*q+r*r);
                      if (k!=l) matrix[3][k][k-1]=-s;
                      e=-q/s; f=-r/s; x=-p/s;
                      y=-x-f*r/(p+s);
                      g=e*r/(p+s);
                      z=-x-e*q/(p+s);
                      for (j=k; j<=m-1; j++)
                      {
                          p=x*matrix[3][k][j]+e*matrix[3][k+1][j];
                          q=e*matrix[3][k][j]+y*matrix[3][k+1][j];
                          r=f*matrix[3][k][j]+g*matrix[3][k+1][j];
                          if (k!=m-2)
                          {
                              p+=f*matrix[3][k+2][j];
                              q+=g*matrix[3][k+2][j];
                              r+=z*matrix[3][k+2][j]; matrix[3][k+2][j]=r;
                          }
                          matrix[3][k+1][j]=q; matrix[3][k][j]=p;
                      }
                      j=k+3;
                      if (j>=m-1) j=m-1;
                      for (i=l; i<=j; i++)
                      {
                          p=x*matrix[3][i][k]+e*matrix[3][i][k+1];
                          q=e*matrix[3][i][k]+y*matrix[3][i][k+1];
                          r=f*matrix[3][i][k]+g*matrix[3][i][k+1];
                          if (k!=m-2)
                          {
                              p+=f*matrix[3][i][k+2];
                              q+=g*matrix[3][i][k+2];
                              r+=z*matrix[3][i][k+2];
                              matrix[3][i][k+2]=r;
                          }
                          matrix[3][i][k+1]=q; matrix[3][i][k]=p;
                      }
                  }
              }
          }
    }
    if(val==true)        //输出特征值
    {
        QString str;
        QDialog *dialog=new QDialog(this);
        dialog->setWindowTitle(tr("LinearAlgebra Tool"));
        QPlainTextEdit *textEdit=new QPlainTextEdit;
        textEdit->setReadOnly(true);
        textEdit->appendPlainText(tr("The eigenvalues of the matrix are:"));
        for(i=0;i<n;++i)
        {
            if(qAbs(eigen_Value_Comp[Index][i])<=1e-5)
            {
                if(qAbs(eigen_Value_Real[Index][i])<=1e-5)
                    str+=QString(tr("0\n"));
                else
                    str+=QString(tr("%1\n").arg(eigen_Value_Real[Index][i]));

            }
            else
            {
                if(qAbs(eigen_Value_Real[Index][i])<=1e-5)
                    str+=QString(tr("%1i\n").arg(eigen_Value_Comp[Index][i]));
                else if(eigen_Value_Comp[Index][i]>0)
                    str+=QString(tr("%1+%2i\n").arg(eigen_Value_Real[Index][i]).arg(eigen_Value_Comp[Index][i]));
                else
                    str+=QString(tr("%1%2i\n").arg(eigen_Value_Real[Index][i]).arg(eigen_Value_Comp[Index][i]));
            }
        }
        textEdit->appendPlainText(str);
        QVBoxLayout *layout=new QVBoxLayout(dialog);
        layout->addWidget(textEdit);
        dialog->show();
    }
}
void LinearAlgebra::maxEigenValue(int Index)
{
    int row=matrixRow[Index],col=matrixCol[Index];
    if(row!=col)
    {
        QMessageBox::warning(this,tr("LinearAlgebra Tool"),
                    tr("The non-square matrix can not seek eigenvalues！"),QMessageBox::Ok);
        return ;
    }
    const double eps=1e-6;
    double sum,lambda_new,lambda_old;
    unsigned iteration=0;
    double *z=new double [row],*y=new double [row],*z_old=new double[row];
    double error1=1,error2=1,max;
    int i,j;
    for(i=0;i<row;++i)
    {z[i]=1;}
    do
    {
        iteration++;
        if(iteration>2000)
        {
            QMessageBox::warning(this,tr("LinearAlgebra Tool"),
                tr("The program can not seek the largest eigenvalue,"
                "possible causes are the largest absolute eigenvalue is more than one or the largest eigenvalue is too small！"),QMessageBox::Ok);
            return ;
        }
        for(i=0;i<row;++i)
        {
            sum=0;
            for(j=0;j<row;++j)
            {sum+=matrix[Index][i][j]*z[j];}
            y[i]=sum;
        }
        for(i=0,sum=0;i<row;++i)
        sum+=y[i]*y[i];
        lambda_new=qSqrt(sum);
        for(i=0;i<row;++i)
        {z[i]=y[i]/lambda_new;}
        if(iteration>1)
        {
            error1=qAbs(lambda_new-lambda_old);
            max=qAbs(qAbs(z[0])-qAbs(z_old[0]));
            if(error1<eps)
            {
                for(i=1;i<row;++i)
                {
                    //z[i]与z_old[i]有可能绝对值相近，但符号相反
                    if(qAbs(qAbs(z[i])-qAbs(z_old[i]))>max)
                        max=qAbs(qAbs(z[i])-qAbs(z_old[i]));
                }
                error2=max;
            }
        }
        lambda_old=lambda_new;
        for(i=0;i<row;++i)
        {z_old[i]=z[i];}
    }while(error1>eps||error2>eps);

    //判断lambda_new符号
    sum=(matrix[Index][0][0]-lambda_new)*z[0];
    for(i=1;i<row;i++)
    {sum+=matrix[Index][0][i]*z[i];}
    if(qAbs(sum)>0.01)
        lambda_new=-lambda_new;
    QString str(tr("The largest absolute eigenvalue is: %1").arg(lambda_new));
    QDialog *dialog=new QDialog(this);
    dialog->setWindowTitle(tr("LinearAlgebra Tool"));
    QPlainTextEdit *textEdit=new QPlainTextEdit;
    textEdit->setReadOnly(true);
    textEdit->appendPlainText(str);
    textEdit->appendPlainText(tr("And the corresponding eigenvector is:\n"));
    for(j=row-1;j>=0;j--)
        if(qAbs(z[j])>eps)
            break;
    for(i=0;i<=j;i++)
    {z[i]/=z[j];}
    str="[";
    for(i=0;i<row-1;++i)
    {
        if(qAbs(z[i])<=eps)
            str.append(tr("0 "));
        else
            str.append(tr("%1 ").arg(z[i]));
    }
    str.append(tr("%1]").arg(z[i]));
    textEdit->appendPlainText(str);
    QVBoxLayout *layout=new QVBoxLayout(dialog);
    layout->addWidget(textEdit);
    dialog->show();
    delete []z;
    delete[]y;
    delete []z_old;
}
void LinearAlgebra::eigenVector(int Index)
{
    int row=matrixRow[Index],col=matrixCol[Index];
    if(row!=col)
    {
        QMessageBox::warning(this,tr("LinearAlgebra Tool"),
                    tr("The non-square matrix can not seek eigenvalues or eigenvectors！"),QMessageBox::Ok);
        return ;
    }
    eigenValue(Index);      //求特征值
    for(int i=0;i<row;i++)
    {
        if(qAbs(eigen_Value_Comp[Index][i])>1e-5)
        {
            QMessageBox::warning(this,tr("LinearAlgebra Tool"),
                        tr("There some imaginary roots, the program can not handle！"),QMessageBox::Ok);
            return ;
        }
    }
    qSort(eigen_Value_Real[Index],eigen_Value_Real[Index]+row);
    int i,j,k;
    double *eigen_Vector;
    eigen_Vector=new double [row];
    matrix[3]=new double *[row];
    matrixRow[3]=matrixCol[3]=row;
    for(i=0;i<row;++i)
    {
      matrix[3][i]=new double [row];
    }
    QString str;
    QDialog *dialog=new QDialog(this);
    dialog->setMinimumSize(250,200);
    dialog->setWindowTitle(tr("LinearAlgebra Tool"));
    QPlainTextEdit *textEdit=new QPlainTextEdit;
    textEdit->setReadOnly(true);
    textEdit->appendPlainText(tr("The eigenvalues of the matrix are:"));
    for(i=0;i<row;++i)
    {
        if(qAbs(eigen_Value_Real[Index][i])<=1e-5)
        {
            eigen_Value_Real[Index][i]=0;
            str+=QString(tr("0 "));
        }
        else
            str+=QString(tr("%1 ").arg(eigen_Value_Real[Index][i]));
    }
    textEdit->appendPlainText(str);
    for(i=0;i<row;++i)
    {
        if(i>0&&qAbs(eigen_Value_Real[Index][i]-eigen_Value_Real[Index][i-1])<1e-3)
        {continue;}
        for(j=0;j<row;++j){
            for(k=0;k<col;++k)
            {
               matrix[3][j][k]=matrix[Index][j][k];
            }
            matrix[3][j][j]-=eigen_Value_Real[Index][i];
        }
        ladder(3);    //将临时矩阵阶梯化
        double ratio;
        for(k=Rank[3]-1;k>0;--k)
        {
            for(int li=k-1;li>=0;li--)
            {
                if(!matrix[3][li][k])
                    continue;
                ratio=matrix[3][li][k]/matrix[3][k][k];
                for(j=k+1;j<col;++j)
                {
                    matrix[3][li][j]-=ratio*matrix[3][k][j];
                }
                matrix[3][li][k]=0;
            }
        }
        int row_Rank=row-Rank[3];
        const double eps=1e-5;
        textEdit->appendPlainText(tr("The eigenvalue %1 corresponding eigenvector is:").arg(eigen_Value_Real[Index][i]));
        for(j=0;j<row_Rank;++j)
        {
            for(k=0;k<Rank[3];++k)
            {
                eigen_Vector[k]=-matrix[3][k][col-j-1]/matrix[3][k][k];
                if(qAbs(eigen_Vector[k])<=eps)
                    eigen_Vector[k]=0;
            }
            for(;k<row;++k)
                eigen_Vector[k]=0;
            eigen_Vector[col-j-1]=1;
            for(k=0;k<Rank[3];k++)
            {
                if(pivcol[3][k]!=k)
                {qSwap(eigen_Vector[k],eigen_Vector[pivcol[3][k]]);}
            }
            str="[";
            for(k=0;k<row-1;++k)
                str.append(tr("%1 ").arg(eigen_Vector[k]));
            str.append(tr("%1]").arg(eigen_Vector[row-1]));
            textEdit->appendPlainText(str);
        }
    }
    QVBoxLayout *layout=new QVBoxLayout(dialog);
    layout->addWidget(textEdit);
    dialog->show();
}
void LinearAlgebra::eigenPolyomial(int Index)
{
    int row=matrixRow[Index],col=matrixCol[Index];
    if(row!=col)
    {
        QMessageBox::warning(this,tr("LinearAlgebra Tool"),
                    tr("The non-square matrix can not seek characteristic equation！"),QMessageBox::Ok);
        return ;
    }
    double **b,**c,*eigenModulous;
    int i,j,k,l;
    b=new double*[row];
    c=new double*[row];
    eigenModulous=new double[row+1];
    for(i=0;i<row;++i)
    {
        b[i]=new double[col];
        c[i]=new double[col];
    }
    for(i=0;i<row;++i)
        for(j=0;j<col;++j)
        {b[i][j]=matrix[Index][i][j];}
    eigenModulous[0]=1;
    eigenModulous[1]=-trace(Index);
    for(k=2;k<=row;++k)            //先求特征方程的系数
    {
        for(i=0;i<row;++i)
        for(j=0;j<row;++j)
        {
            if(i==j)
            {c[i][i]=b[i][i]+eigenModulous[k-1];}
            else
            {c[i][j]=b[i][j];}
        }
        for(i=0;i<row;++i)         //矩阵相乘
        for(j=0;j<col;++j)
        {
            for(l=0,b[i][j]=0;l<row;++l)
            {b[i][j]+=matrix[Index][i][l]*c[l][j];}
        }
        eigenModulous[k]=-trace(b,row)/k;
    }
    //输出特征方程
    const double eps=1e-5;
    QString str;
    QDialog *dialog=new QDialog(this);
    dialog->setWindowTitle(tr("LinearAlgebra Tool"));
    QPlainTextEdit *textEdit=new QPlainTextEdit;
    textEdit->setReadOnly(true);
    textEdit->appendPlainText(tr("The eigenpolynomial is:"));
    str.append(tr("x^%1").arg(row));
    for(i=1;i<row;++i)
    {
        if(eigenModulous[i]>eps)
            str.append(tr(" + %1x^%2").arg(eigenModulous[i]).arg(row-i));
        else if(eigenModulous[i]<-eps)
            str.append(tr(" - %1x^%2").arg(-eigenModulous[i]).arg(row-i));
    }
    if(eigenModulous[row]>eps)
        str.append(tr(" + %1 = 0").arg(eigenModulous[row]));
    else if(eigenModulous[row]<-eps)
        str.append(tr(" - %1 = 0").arg(-eigenModulous[row]));
    else
        str.append(tr(" = 0"));
    textEdit->appendPlainText(str);
    QVBoxLayout *layout=new QVBoxLayout(dialog);
    layout->addWidget(textEdit);
    dialog->show();
}
void LinearAlgebra::isOrthogonal(int Index)
{
    int row=matrixRow[Index],col=matrixCol[Index];
    if(row!=col)
    {
        QMessageBox::warning(this,tr("LinearAlgebra Tool"),
                    tr("Non-square matrix can not whether an orthogonal matrix！"),QMessageBox::Ok);
        return ;
    }
    double dl;
    const double eps=1e-5;
    int i,j,k;
    for(i=0;i<col;++i)
    {
        for(j=0,dl=0.0;j<row;++j)
        {
            dl+=matrix[Index][i][j]*matrix[Index][i][j];
        }
        if(qAbs(dl-1.0)>eps)
        {
            QMessageBox::information(this,tr("LinearAlgebra Tool"),
                        tr("The matrix isn't orthogonal matrix！"),QMessageBox::Ok);
            return ;
        }
    }
    for(i=0;i<col-1;++i)
    {
        for(j=i+1;j<col;++j)
        {
            for(k=0,dl=0.0;k<row;++k)
            {
                dl+=matrix[Index][i][k]*matrix[Index][j][k];
            }
            if(qAbs(dl)>eps)
            {
                QMessageBox::information(this,tr("LinearAlgebra Tool"),
                            tr("The matrix isn't orthogonal matrix！"),QMessageBox::Ok);
                return ;
            }
        }
    }
    QMessageBox::information(this,tr("LinearAlgebra Tool"),
                tr("The matrix is orthogonal matrix！"),QMessageBox::Ok);
    return ;
}
double LinearAlgebra::trace(int Index)
{
    int i,row=matrixRow[Index];
    double sum=0;
    for(i=0;i<row;i++)
    {sum+=matrix[Index][i][i];}
    return sum;
}
double LinearAlgebra::trace(double **a,int n)
{
    int i;
    double sum=0;
    for(i=0;i<n;i++)
    {sum+=a[i][i];}
    return sum;
}
void sss(double fg[],double cs[])
{
      double r,d;
      if ((qAbs(fg[0])+qAbs(fg[1]))==0.0)
      {
          cs[0]=1.0; cs[1]=0.0; d=0.0;
      }
      else
      {
          d=sqrt(fg[0]*fg[0]+fg[1]*fg[1]);
          if (qAbs(fg[0])>qAbs(fg[1]))
          {
              d=qAbs(d);
              if (fg[0]<0.0) d=-d;
          }
          if (qAbs(fg[1])>=qAbs(fg[0]))
          {
              d=qAbs(d);
              if (fg[1]<0.0) d=-d;
          }
          cs[0]=fg[0]/d; cs[1]=fg[1]/d;
      }
      r=1.0;
      if (qAbs(fg[0])>qAbs(fg[1])) r=cs[1];
      else
          if (cs[0]!=0.0) r=1.0/cs[0];
      fg[0]=d; fg[1]=r;
}
