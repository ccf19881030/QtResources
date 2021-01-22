#include<QFileDialog>
#include<QMessageBox>
#include<QTextStream>
#include<QSettings>
#include<QHBoxLayout>
#include<QListWidget>
#include<QVBoxLayout>
#include<QSettings>
#include<QProcess>
#include<QDesktopServices>
#include<QUrl>
#include<QColorDialog>
#include<QFontDialog>
#include"Calculator.h"
#include"Calc.h"
#include"HugeCalc.h"
#include"linearAlgebra.h"
#include"nonLinearAlgebra.h"
Calculator::Calculator( QWidget * parent):QMainWindow(parent)
{
    setupUi(this);
    readSettings();
    //默认的进制为十进制
    oldSystem=10;newSystem=10;
    isChangeSystem=false;
}
void Calculator::closeEvent(QCloseEvent *event)
{
    writeSettings();  
    event->accept();
}
void Calculator::readSettings()
{
    QSettings settings;
    //The QSettings constructor takes arguments that identify your company and the name of the product.
    //This ensures that the settings for different applications are kept separately.
    //调整窗口的位置
    QPoint pos = settings.value("pos", QPoint(350, 200)).toPoint();
    move(pos);
    //设置主窗口是否置顶
    if(settings.value("TopHint").toBool())
    {
        topHintAction->setChecked(true);
        setWindowFlags(Qt::WindowStaysOnTopHint);
    }
    if(settings.value("language").toBool())
    {
        actionChinese->setChecked(false);
        actionEnglish->setChecked(true);
    }
    //设置背景颜色
    isChangeColor=false;
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
    express_lineEdit->setPalette(bgpal);
    result_lineEdit->setPalette(bgpal);
    memory_lineEdit->setPalette(bgpal);
    //设置字体的大小
    isChangeFont=false;
    QFont font;
    QString sizeStr;
    font.fromString(settings.value("Font","Arial,20,-1,5,50,0,0,0,0,0").toString());
    sizeStr=QString("font-size : %1px").arg(font.pointSize());
    express_lineEdit->setFont(font);
    result_lineEdit->setFont(font);
    memory_lineEdit->setFont(font);
    express_lineEdit->setStyleSheet(sizeStr);
    result_lineEdit->setStyleSheet(sizeStr);
    memory_lineEdit->setStyleSheet(sizeStr);
    //设置变量
    settings.setValue("Variable_X_Bool",false);
    settings.setValue("Variable_Y_Bool",false);
    settings.setValue("Variable_Z_Bool",false);
    //设置历史记录
    QStringList historyRecord = settings.value("historyRecord").toStringList();
    historyIndex=historyRecord.size()-1;
    if(historyIndex>=0)
    {
        undo_pushButton->setEnabled(true);
        redo_pushButton->setEnabled(true);
    }
    else
    {
        undo_pushButton->setEnabled(false);
        redo_pushButton->setEnabled(false);
    }
}
void Calculator::writeSettings()
{
    //保存窗口位置
    QSettings settings;
    settings.setValue("pos", pos());
    settings.setValue("TopHint",topHintAction->isChecked());
    if(isChangeColor)
    {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::question(this,"Calculator/2012/08",tr("Background color,do you want to save it?"),
                              QMessageBox::Save| QMessageBox::Cancel);
        if (ret != QMessageBox::Save){
             settings.setValue("red/window",152);
             settings.setValue("green/window",204);
             settings.setValue("blue/window",222);
             settings.setValue("red/textview",206);
             settings.setValue("green/textview",224);
             settings.setValue("blue/textview",255);
        }
    }
    if(isChangeFont)
    {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::question(this,"Calculator/2012/08",tr("Font has been changes,do you want to save it?"),
                              QMessageBox::Save| QMessageBox::Cancel);
        if (ret != QMessageBox::Save){
             QFont font("Arial",20);
             settings.setValue("Font",font.toString());
        }
    }
}

void Calculator::changeLanguage(bool isChange)
{
    if(isChange==false)
        return ;
    else
    {
        int ret=QMessageBox::information(this,tr("Language setting"),
        tr("Changes to the language setting will not take effect until the environment is restarted！"),
        QMessageBox::Cancel|QMessageBox::Ok);
        QSettings settings;
        bool isEnglish=settings.value("language").toBool();
        if (ret == QMessageBox::Ok) {
            if(isEnglish==true)
                actionEnglish->setChecked(false);
            else
                actionChinese->setChecked(false);
            settings.setValue("language",!isEnglish);
        }
        else
        {
            if(isEnglish)
                actionChinese->setChecked(false);
            else
                actionEnglish->setChecked(false);
        }
    }
}
void Calculator::changePrecision()
{
    if(!express_lineEdit->text().isEmpty())
    {getResult();}
}
void Calculator::decSystem()
{
    numA_pushButton->setEnabled(false);
    numB_pushButton->setEnabled(false);
    numC_pushButton->setEnabled(false);
    numD_pushButton->setEnabled(false);
    numE_pushButton->setEnabled(false);
    numF_pushButton->setEnabled(false);

    numTwo_pushButton->setEnabled(true);
    numThree_pushButton->setEnabled(true);
    numFour_pushButton->setEnabled(true);
    numFive_pushButton->setEnabled(true);
    numSix_pushButton->setEnabled(true);
    numSeven_pushButton->setEnabled(true);
    numEight_pushButton->setEnabled(true);
    numNine_pushButton->setEnabled(true);
    checkBox_2->setEnabled(true);
    spinBox->setEnabled(true);

    isChangeSystem=true;
    newSystem=10;
    if(!express_lineEdit->text().isEmpty())
        {getResult();}
    isChangeSystem=false;
    oldSystem=10;
}
void Calculator::binSystem()
{
    numA_pushButton->setEnabled(false);
    numB_pushButton->setEnabled(false);
    numC_pushButton->setEnabled(false);
    numD_pushButton->setEnabled(false);
    numE_pushButton->setEnabled(false);
    numF_pushButton->setEnabled(false);

    numTwo_pushButton->setEnabled(false);
    numThree_pushButton->setEnabled(false);
    numFour_pushButton->setEnabled(false);
    numFive_pushButton->setEnabled(false);
    numSix_pushButton->setEnabled(false);
    numSeven_pushButton->setEnabled(false);
    numEight_pushButton->setEnabled(false);
    numNine_pushButton->setEnabled(false);
    checkBox_2->setEnabled(false);
    spinBox->setEnabled(false);

    isChangeSystem=true;
    newSystem=2;
    if(!express_lineEdit->text().isEmpty())
        {getResult();}
    isChangeSystem=false;
    oldSystem=2;
}
void Calculator::octSystem()
{
    numA_pushButton->setEnabled(false);
    numB_pushButton->setEnabled(false);
    numC_pushButton->setEnabled(false);
    numD_pushButton->setEnabled(false);
    numE_pushButton->setEnabled(false);
    numF_pushButton->setEnabled(false);

    numTwo_pushButton->setEnabled(true);
    numThree_pushButton->setEnabled(true);
    numFour_pushButton->setEnabled(true);
    numFive_pushButton->setEnabled(true);
    numSix_pushButton->setEnabled(true);
    numSeven_pushButton->setEnabled(true);
    numEight_pushButton->setEnabled(false);
    numNine_pushButton->setEnabled(false);
    checkBox_2->setEnabled(false);
    spinBox->setEnabled(false);

    isChangeSystem=true;
    newSystem=8;
    if(!express_lineEdit->text().isEmpty())
        {getResult();}
    isChangeSystem=false;
    oldSystem=8;
}
void Calculator::hexSystem()
{
    numA_pushButton->setEnabled(true);
    numB_pushButton->setEnabled(true);
    numC_pushButton->setEnabled(true);
    numD_pushButton->setEnabled(true);
    numE_pushButton->setEnabled(true);
    numF_pushButton->setEnabled(true);
    numTwo_pushButton->setEnabled(true);
    numThree_pushButton->setEnabled(true);
    numFour_pushButton->setEnabled(true);
    numFive_pushButton->setEnabled(true);
    numSix_pushButton->setEnabled(true);
    numSeven_pushButton->setEnabled(true);
    numEight_pushButton->setEnabled(true);
    numNine_pushButton->setEnabled(true);
    checkBox_2->setEnabled(false);
    spinBox->setEnabled(false);

    isChangeSystem=true;
    newSystem=16;
    if(!express_lineEdit->text().isEmpty())
        {getResult();}
    isChangeSystem=false;
    oldSystem=16;
}

void Calculator::realSystem()
{
    fun_Lg_pushButton->setEnabled(true);
    fun_Ln_pushButton->setEnabled(true);
    fun_Log_pushButton->setEnabled(true);
    fun_Arcsin_pushButton->setEnabled(true);
    fun_Sin_pushButton->setEnabled(true);
    fun_Cos_pushButton->setEnabled(true);
    fun_Tan_pushButton->setEnabled(true);
    fun_Cot_pushButton->setEnabled(true);
    fun_Arccos_pushButton->setEnabled(true);
    fun_Arctan_pushButton->setEnabled(true);
    fun_Arccot_pushButton->setEnabled(true);
    fun_Pow_pushButton->setEnabled(true);
    fun_Gcd_pushButton->setEnabled(true);
    fun_Lcm_pushButton->setEnabled(true);
    operPercent_pushButton->setEnabled(true);
    operMod_pushButton->setEnabled(true);
    operFact_pushButton->setEnabled(true);
    operDiv_pushButton->setEnabled(true);
    operPercent_pushButton->setText(tr("%"));
    operPercent_pushButton->setStatusTip(tr("Percent"));
    operComb_pushButton->setText(tr("nad"));
    operComb_pushButton->setStatusTip(tr("Combinatorial number"));

    checkBox_1->setEnabled(true);
    checkBox_2->setEnabled(true);
    groupBox_3->setEnabled(true);
    if(!Deg_radioButton->isChecked())
    {
        Deg_radioButton->setChecked(true);
    }
    numEi_pushButton->setEnabled(false);
    NumI_pushButton->setEnabled(false);
}
void Calculator::complexSystem()
{
    fun_Lg_pushButton->setEnabled(false);
    fun_Ln_pushButton->setEnabled(false);
    fun_Log_pushButton->setEnabled(false);
    fun_Arcsin_pushButton->setEnabled(false);
    fun_Sin_pushButton->setEnabled(false);
    fun_Cos_pushButton->setEnabled(false);
    fun_Tan_pushButton->setEnabled(false);
    fun_Cot_pushButton->setEnabled(false);
    fun_Arccos_pushButton->setEnabled(false);
    fun_Arctan_pushButton->setEnabled(false);
    fun_Arccot_pushButton->setEnabled(false);
    fun_Pow_pushButton->setEnabled(false);
    fun_Gcd_pushButton->setEnabled(false);
    fun_Lcm_pushButton->setEnabled(false);
    operMod_pushButton->setEnabled(false);
    operFact_pushButton->setEnabled(false);
    operDiv_pushButton->setEnabled(false);
    checkBox_1->setEnabled(false);
    operPercent_pushButton->setText(tr("AE"));
    operPercent_pushButton->setStatusTip(tr("Show complex number in exponent."));
    operComb_pushButton->setText(tr("conj"));
    operComb_pushButton->setStatusTip(tr("Conjugate complex number"));

    if(!Dec_radioButton->isChecked())
    {
        Dec_radioButton->setChecked(true);
        decSystem();
    }
    if(!Rad_radioButton->isChecked())
    {
        Rad_radioButton->setChecked(true);
    }
    checkBox_2->setEnabled(false);
    checkBox_2->setChecked(false);
    groupBox_3->setEnabled(false);

    numEi_pushButton->setEnabled(true);
    NumI_pushButton->setEnabled(true);
}

void Calculator::hyperbolicSystem()
{
    if(checkBox_1->isChecked())
    {
    fun_Sin_pushButton->setText(tr("sinh"));
    fun_Cos_pushButton->setText(tr("cosh"));
    fun_Tan_pushButton->setText(tr("tanh"));
    fun_Cot_pushButton->setText(tr("coth"));
    fun_Arcsin_pushButton->setText(tr("arcsinh"));
    fun_Arccos_pushButton->setText(tr("arccosh"));
    fun_Arctan_pushButton->setText(tr("arctanh"));
    fun_Arccot_pushButton->setText(tr("arccoth"));
    }
    else
    {
    fun_Sin_pushButton->setText(tr("sin"));
    fun_Cos_pushButton->setText(tr("cos"));
    fun_Tan_pushButton->setText(tr("tan"));
    fun_Cot_pushButton->setText(tr("cot"));
    fun_Arcsin_pushButton->setText(tr("arcsin"));
    fun_Arccos_pushButton->setText(tr("arccos"));
    fun_Arctan_pushButton->setText(tr("arctan"));
    fun_Arccot_pushButton->setText(tr("arccot"));
    }
}

void Calculator::inputNumOne()
{express_lineEdit->insert(tr("1"));}
void Calculator::inputNumTwo()
{express_lineEdit->insert(tr("2"));}
void Calculator::inputNumThree()
{express_lineEdit->insert(tr("3"));}
void Calculator::inputNumFour()
{express_lineEdit->insert(tr("4"));}
void Calculator::inputNumFive()
{express_lineEdit->insert(tr("5"));}
void Calculator::inputNumSix()
{express_lineEdit->insert(tr("6"));}
void Calculator::inputNumSeven()
{express_lineEdit->insert(tr("7"));}
void Calculator::inputNumEight()
{express_lineEdit->insert(tr("8"));}
void Calculator::inputNumNine()
{express_lineEdit->insert(tr("9"));}
void Calculator::inputNumZero()
{express_lineEdit->insert(tr("0"));}

//十六进制字母
void Calculator::inputNumA()
{express_lineEdit->insert(tr("A"));}
void Calculator::inputNumB()
{express_lineEdit->insert(tr("B"));}
void Calculator::inputNumC()
{express_lineEdit->insert(tr("C"));}
void Calculator::inputNumD()
{express_lineEdit->insert(tr("D"));}
void Calculator::inputNumE()
{express_lineEdit->insert(tr("E"));}
void Calculator::inputNumF()
{express_lineEdit->insert(tr("F"));}

void Calculator::inputNumI()
{express_lineEdit->insert(tr("i"));}
void Calculator::inputNumEi()
{express_lineEdit->insert(tr("$e^i"));}

void Calculator::inputPoint()
{
    QString str=express_lineEdit->text();
    int curPos=express_lineEdit->cursorPosition();
    if(curPos==0)
        express_lineEdit->insert(tr("0."));
    else if(!str[curPos-1].isDigit())
        express_lineEdit->insert(tr("0."));
    else
        express_lineEdit->insert(tr("."));
}
void Calculator::inputOperAdd()
{express_lineEdit->insert(tr("+"));}
void Calculator::inputOperSubtract()
{express_lineEdit->insert(tr("-"));}
void Calculator::inputOperMultiply()
{express_lineEdit->insert(tr("*"));}
void Calculator::inputOperDivide()
{express_lineEdit->insert(tr("/"));}
void Calculator::inputOperMod()
{express_lineEdit->insert(tr(" mod "));}
void Calculator::inputOperDiv()
{express_lineEdit->insert(tr(" div "));}
void Calculator::inputOperPercent()
{
    if(!Complex_radioButton->isChecked())
        express_lineEdit->insert(tr("%"));
    else
    {
        getResult();
        if(isCorrect)
        {
            QString result;
            Complex CompNumber;
            CompNumber.setComplex(result_lineEdit->text());
            result=CompNumber.toExponential(Deg_radioButton->isChecked(),spinBox->value());
            result_lineEdit->setText(result);
        }
    }
}
void Calculator::inputOperFact()
{express_lineEdit->insert(tr("!"));}
void Calculator::inputOperComb()
{
    if(!Complex_radioButton->isChecked())
        express_lineEdit->insert(tr(" nad "));
    else
    {
        express_lineEdit->insert(tr("conj()"));
        express_lineEdit->cursorBackward(0,1);
    }
}
void Calculator::inputOperPower()
{express_lineEdit->insert(tr("^"));}
void Calculator::inputOperSqr()
{express_lineEdit->insert(tr("^2"));}
void Calculator::inputOperCub()
{express_lineEdit->insert(tr("^3"));}
void Calculator::inputOperExpE()
{express_lineEdit->insert(tr("$e^"));}
void Calculator::inputOperExp10()
{express_lineEdit->insert(tr("10^"));}
void Calculator::inputOperSqrt()
{express_lineEdit->insert(tr("^(1/2)"));}
void Calculator::inputOperCur()
{express_lineEdit->insert(tr("^(1/3)"));}
void Calculator::inputOperXYsqrt()
{
    express_lineEdit->insert(tr("^(1/)"));
    express_lineEdit->cursorBackward(0,1);
}
void Calculator::inputLeftBack()
{express_lineEdit->insert(tr("("));}
void Calculator::inputRightBack()
{express_lineEdit->insert(tr(")"));}
void Calculator::inputConst_e()
{express_lineEdit->insert(tr("$e"));}
void Calculator::inputConst_g()
{express_lineEdit->insert(tr("$g"));}
void Calculator::inputConst_pi()
{express_lineEdit->insert(tr("$pi"));}
void Calculator::inputConstant()
{
    int row;
    QList<QTableWidgetItem*>items=constantDialog->tableWidget->selectedItems();
    row=constantDialog->tableWidget->row(items.at(0));
    char str[][6]=
            {"$pi","$e","$g","$c","$eps0","$mi0",
             "$en","$mu","$me","$mp","$mn","$k","$h"};
    express_lineEdit->insert(str[row]);
}

void Calculator::inputFunSin()
{
    if(checkBox_1->isChecked())
    express_lineEdit->insert(tr("sinh()"));
    else
    express_lineEdit->insert(tr("sin()"));
    express_lineEdit->cursorBackward(0,1);
}
void Calculator::inputFunCos()
{
    if(checkBox_1->isChecked())
    express_lineEdit->insert(tr("cosh()"));
    else
    express_lineEdit->insert(tr("cos()"));
    express_lineEdit->cursorBackward(0,1);
}
void Calculator::inputFunTan()
{
    if(checkBox_1->isChecked())
    express_lineEdit->insert(tr("tanh()"));
    else
    express_lineEdit->insert(tr("tan()"));
    express_lineEdit->cursorBackward(0,1);
}
void Calculator::inputFunCot()
{
    if(checkBox_1->isChecked())
    express_lineEdit->insert(tr("coth()"));
    else
    express_lineEdit->insert(tr("cot()"));
    express_lineEdit->cursorBackward(0,1);
}
void Calculator::inputFunArcSin()
{
    if(checkBox_1->isChecked())
    express_lineEdit->insert(tr("arcsinh()"));
    else
    express_lineEdit->insert(tr("arcsin()"));
    express_lineEdit->cursorBackward(0,1);
}
void Calculator::inputFunArcCos()
{
    if(checkBox_1->isChecked())
    express_lineEdit->insert(tr("arccosh()"));
    else
    express_lineEdit->insert(tr("arccos()"));
    express_lineEdit->cursorBackward(0,1);
}
void Calculator::inputFunArcTan()
{
    if(checkBox_1->isChecked())
    express_lineEdit->insert(tr("arctanh()"));
    else
    express_lineEdit->insert(tr("arctan()"));
    express_lineEdit->cursorBackward(0,1);
}
void Calculator::inputFunArcCot()
{
    if(checkBox_1->isChecked())
    express_lineEdit->insert(tr("arccoth()"));
    else
    express_lineEdit->insert(tr("arccot()"));
    express_lineEdit->cursorBackward(0,1);
}
void Calculator::inputFunLg()
{
    express_lineEdit->insert(tr("lg()"));
    express_lineEdit->cursorBackward(0,1);
}
void Calculator::inputFunLn()
{
    express_lineEdit->insert(tr("ln()"));
    express_lineEdit->cursorBackward(0,1);
}
void Calculator::inputFunLog()
{
    express_lineEdit->insert(tr("log( , )"));
    express_lineEdit->cursorBackward(0,3);
}
void Calculator::inputFunAbs()
{
    express_lineEdit->insert(tr("abs()"));
    express_lineEdit->cursorBackward(0,1);
}
void Calculator::inputFunPow()
{
    express_lineEdit->insert(tr("pow( , )"));
    express_lineEdit->cursorBackward(0,3);
}
void Calculator::inputFunGcd()
{
    express_lineEdit->insert(tr("gcd( , )"));
    express_lineEdit->cursorBackward(0,3);
}
void Calculator::inputFunLcm()
{
    express_lineEdit->insert(tr("lcm( , )"));
    express_lineEdit->cursorBackward(0,3);
}

void Calculator::clearExpress()
{
    express_lineEdit->clear();
    result_lineEdit->clear();
}
void Calculator::backspace()
{
    if(express_lineEdit->cursorPosition()>0)
    express_lineEdit->backspace();
    else
    express_lineEdit->setFocus();
}
void Calculator::undo()
{
    QSettings settings;
    QStringList historyRecord = settings.value("historyRecord").toStringList();
    if(historyIndex>0)
        historyIndex--;
    QString express=historyRecord[historyIndex];
    int index=express.indexOf("=");
    result_lineEdit->setText(express.right(express.length()-index-1));
    express.truncate(index);
    express_lineEdit->setText(express);
    express_lineEdit->selectAll();
}
void Calculator::redo()
{
    QSettings settings;
    QStringList historyRecord = settings.value("historyRecord").toStringList();
    if(historyIndex<historyRecord.size()-1)
        historyIndex++;
    QString express=historyRecord[historyIndex];
    int index=express.indexOf("=");
    result_lineEdit->setText(express.right(express.length()-index-1));
    express.truncate(index);
    express_lineEdit->setText(express);
    express_lineEdit->selectAll();
}
void Calculator::fold()
{
     if(fold_pushButton->isChecked())
     {
         fold_pushButton->setIcon(QIcon(":images/unfold.png"));
         function_groupBox->setVisible(false);
         number_groupBox->setVisible(false);
         statusBar()->setVisible(false);
         setMinimumSize(660,200);
         setMaximumSize(660,200);
     }
     else
     {
         fold_pushButton->setIcon(QIcon(":images/fold.png"));
         function_groupBox->setVisible(true);
         number_groupBox->setVisible(true);
         statusBar()->setVisible(true);
         setMinimumSize(660,380);
         setMaximumSize(660,380);
     }
}
void Calculator::insertNewResult()
{
    QString newResult=result_lineEdit->text();
    if(newResult.isEmpty()||isCorrect==false)
        express_lineEdit->insert("0");
    else{
        express_lineEdit->clear();
        if(Complex_radioButton->isChecked()){
            if(newResult.contains('i')){
                newResult.prepend('(');
                newResult.append(')');
            }
        }
        express_lineEdit->insert(newResult);
    }
}
void Calculator::insertMemorySystem()
{
    QString newResult=result_lineEdit->text();
    if(newResult.isEmpty()||isCorrect==false)
        memory_lineEdit->setText("0");
    else
        memory_lineEdit->setText(newResult);
}
void Calculator::insertMemoryResult()
{
    QString newResult=memory_lineEdit->text();
    if(Complex_radioButton->isChecked()){
        if(newResult.contains('i')){
            newResult.prepend('(');
            newResult.append(')');
        }
    }
    express_lineEdit->insert(newResult);
}

void Calculator::getResult()
{
    QSettings settings;
    QString express=express_lineEdit->text();
    QPalette *pal=new QPalette;
    int red,green,blue;
    red=settings.value("red/textview",206).toInt();
    green=settings.value("green/textview",224).toInt();
    blue=settings.value("blue/textview",255).toInt();
    pal->setColor(QPalette::Base,QColor(red,green,blue));
    pal->setColor(QPalette::Text,QColor(0,0,0));
    result_lineEdit->setPalette(*pal);
    if(express.isEmpty())
    {
        result_lineEdit->setText(tr("0"));
        express_lineEdit->setFocus();
        return ;
    }
   unsigned short precision=spinBox->value();           //小数点精度
   bool isDeg=Deg_radioButton->isChecked();             //是否使用角度制
   bool isFraction=checkBox_2->isChecked();             //是否使用分数制
   bool isComplex=Complex_radioButton->isChecked();     //是否使用复数制
   CCalculator *ccalculator=new CCalculator;
   QString result;
   int ret=ccalculator->Calc(result,express,precision,isDeg,isFraction,
                        isComplex,isChangeSystem,oldSystem,newSystem);
   express_lineEdit->setText(express);
   if(ret==RET_CORRECT)
   {
       isCorrect=true;
       result_lineEdit->setText(result);
       express_lineEdit->selectAll();
       express_lineEdit->setFocus();
       QString record=express;
       record.append(" = "),record.append(result);

       QStringList historyRecord = settings.value("historyRecord").toStringList();
       historyRecord.removeAll(record);
       historyRecord.append(record);
       settings.setValue("historyRecord",historyRecord);

       historyIndex=historyRecord.size()-1;
       undo_pushButton->setEnabled(true);
       redo_pushButton->setEnabled(true);
    }
   else
   {
       isCorrect=false;
       pal->setColor(QPalette::Text,QColor(255,0,0));
       result_lineEdit->setPalette(*pal);
       switch(ret)
       {
       case RET_WRONG:
           express_lineEdit->setSelection(ccalculator->ERRORBEGIN,1);
           result_lineEdit->setText(tr("There are some abnormal characters."));break;
       case RET_WRONGSTR:
           express_lineEdit->setSelection(ccalculator->ERRORBEGIN,ccalculator->ERRORLENGTH);
           if(ccalculator->ERRORLENGTH==1)
               result_lineEdit->setText(tr("There are some undeclared characters."));
           else
               result_lineEdit->setText(tr("There are some undeclared strings."));break;
       case RET_UPPERLETTER:
           express_lineEdit->setSelection(ccalculator->ERRORBEGIN,1);
           result_lineEdit->setText(tr("The capital letter can't be used here."));
           break;
       case RET_BACK :
           express_lineEdit->setSelection(ccalculator->ERRORBEGIN,1);
           result_lineEdit->setText(tr("There are some unmatched parentheses."));break;
       case RET_POINT :
           express_lineEdit->setSelection(ccalculator->ERRORBEGIN,1);
           result_lineEdit->setText(tr("There are some redundant points."));break;
       case RET_OPER:
           express_lineEdit->setSelection(ccalculator->ERRORBEGIN,ccalculator->ERRORLENGTH);
           result_lineEdit->setText(tr("There are two operators was used in conjunction."));break;
       case RET_START:
           express_lineEdit->setSelection(ccalculator->ERRORBEGIN,1);
           result_lineEdit->setText(tr("The beginning of the expression is illegal."));break;
       case RET_LAST:
           express_lineEdit->setSelection(ccalculator->ERRORBEGIN,1);
           result_lineEdit->setText(tr("The ending of the expression is illegal."));break;
       case RET_BACKEMPTY:
           express_lineEdit->setSelection(ccalculator->ERRORBEGIN,ccalculator->ERRORLENGTH);
           result_lineEdit->setText(tr("There is nothing in the brackets."));break;
       case RET_COMMA:
           express_lineEdit->setSelection(ccalculator->ERRORBEGIN,1);
           result_lineEdit->setText(tr("The comma was used illegally."));break;
       case RET_INT: 
           result_lineEdit->setText(tr("Operator "));
           result_lineEdit->insert(result);
           result_lineEdit->insert(tr(" can only be used for integers."));break;
       case RET_NONGINT:
           result_lineEdit->setText(tr("Operator "));
           result_lineEdit->insert(result);
           result_lineEdit->insert(tr(" can only be used for non-negative integers."));break;
       case RET_ZERO:
           result_lineEdit->setText(tr("In the operator "));
           result_lineEdit->insert(result);
           result_lineEdit->insert(tr(", divisor cannot be zero."));break;
       case RET_OPERNUMBER:
           result_lineEdit->setText(tr("Operator "));
           result_lineEdit->insert(result);
           result_lineEdit->insert(tr("lacks operand number."));break;
       case RET_NEGSQRT:
           result_lineEdit->setText(tr("Negative number can't seek square root."));break;
       case RET_ARGUMENT:
           result_lineEdit->setText(tr("Function "));
           result_lineEdit->insert(result);
           result_lineEdit->insert(tr("()'s argument is illegal."));break;
       case RET_FUNNUMBER:
           result_lineEdit->setText(tr("Function "));
           result_lineEdit->insert(result);
           result_lineEdit->insert(tr("()lacks parameter."));break;
       case RET_GCDLCM:
           result_lineEdit->setText(tr("Function "));
           result_lineEdit->insert(result);
           result_lineEdit->insert(tr("()'s arguments must be integers."));break;
       case RET_INF:
           result_lineEdit->setText(tr("Data overflow！"));break;
       case RET_COMPLEX:
           result_lineEdit->setText(tr("The program can't deal with these operations in Complex."));break;
       case RET_NUMBER:
           if(newSystem==2)
               result_lineEdit->setText(tr("In binary system,the numbers must be 0 or 1."));
           else
               result_lineEdit->setText(tr("In octonary system,the numbers must be 0~7."));
           break;
       case RET_VARIABLE:
           result_lineEdit->setText(tr("Please input variable's value."));
           this->showVariable();
           break;
       case RET_USEINCOMP:
           result_lineEdit->setText(tr("This function can only be used in Complex."));break;
       case RET_SCIENTIFIC:
           express_lineEdit->setSelection(ccalculator->ERRORBEGIN,1);
           result_lineEdit->setText(tr("Scientific notation wrong."));
           break;
       default:
           express_lineEdit->selectAll();
           result_lineEdit->setText(tr("The program meet a unknown error!"));break;
       }
       express_lineEdit->setFocus();
   }
   return ;
}

void Calculator::showHistory()
{
    historyDialog=new History(this);
    connect(historyDialog->usePushButton,SIGNAL(clicked()),this,SLOT(setData()));
    connect(historyDialog->clearPushButton,SIGNAL(clicked()),this,SLOT(setHistoryIndex()));
    connect(historyDialog->deletePushButton,SIGNAL(clicked()),this,SLOT(setHistoryIndex()));
    QSettings settings;
    QStringList historyRecord = settings.value("historyRecord").toStringList();
    int numRecords=historyRecord.size();
    historyDialog->plainTextEdit->clear();
    for(int i=0;i<numRecords;++i)
    {
        QString record=historyRecord[i];
        historyDialog->plainTextEdit->appendPlainText(record);
    }
    historyDialog->show();
}
void Calculator::showVariable()
{
    //此对象为单实例模式
    Variable *variableDialog = Variable::getInstance(this);
    connect(variableDialog->calcButton,SIGNAL(clicked()),this,SLOT(getResult()));
    variableDialog->show();
}
void Calculator::showConstant()
{
    constantDialog = new Constant(this);
    connect(constantDialog->usePushButton,SIGNAL(clicked()),this,SLOT(inputConstant()));
    constantDialog->show();
}

void Calculator::setData()
{
    QSettings settings;
    QPalette *pal=new QPalette;
    int red,green,blue;
    red=settings.value("red/textview",206).toInt();
    green=settings.value("green/textview",224).toInt();
    blue=settings.value("blue/textview",255).toInt();
    pal->setColor(QPalette::Base,QColor(red,green,blue));
    pal->setColor(QPalette::Text,QColor(0,0,0));
    result_lineEdit->setPalette(*pal);
    QString express=historyDialog->lineEdit->text();
    int index=express.indexOf("=");
    result_lineEdit->setText(express.right(express.length()-index-1));
    express.truncate(index);
    express_lineEdit->setText(express);
    express_lineEdit->selectAll();
}
void Calculator::setHistoryIndex()
{
    QSettings settings;
    QStringList historyRecord = settings.value("historyRecord").toStringList();
    historyIndex=historyRecord.size()-1;
    if(historyIndex==-1)
    {
        undo_pushButton->setEnabled(false);
        redo_pushButton->setEnabled(false);
    }
}
void Calculator::setTopHint()
{
    QSettings settings;
    if(topHintAction->isChecked()){
        settings.setValue("TopHint",1);
        setWindowFlags(Qt::WindowStaysOnTopHint);
        show();
    }
    else
    {
        settings.setValue("TopHint",0);
        setWindowFlags(Qt::Widget);
        show();
    }
}
void Calculator::showWindowColorDialog()
{
    QColorDialog *colorDialog=new QColorDialog(this);
    colorDialog->setWindowTitle(tr("Choose Window's background color"));
    QSettings settings;
    QPalette bgpal;
    int red,green,blue;
    red=settings.value("red/window",152).toInt();
    green=settings.value("green/window",204).toInt();
    blue=settings.value("blue/window",222).toInt();
    bgpal.setColor(QPalette::Background, QColor(red,green,blue));
    colorDialog->setPalette(bgpal);
    red=settings.value("red/window",152).toInt();
    green=settings.value("green/window",204).toInt();
    blue=settings.value("blue/window",222).toInt();
    colorDialog->setCurrentColor(QColor(red,green,blue));
    connect(colorDialog,SIGNAL(colorSelected(QColor)),this,SLOT(windowColorChange(QColor)));
    colorDialog->exec();
}
void Calculator::showTextViewColorDialog()
{
    QColorDialog *colorDialog=new QColorDialog(this);
    colorDialog->setWindowTitle(tr("Choose TextView's background color"));
    QSettings settings;
    QPalette bgpal;
    int red,green,blue;
    red=settings.value("red/window",152).toInt();
    green=settings.value("green/window",204).toInt();
    blue=settings.value("blue/window",222).toInt();
    bgpal.setColor(QPalette::Background, QColor(red,green,blue));
    colorDialog->setPalette(bgpal);
    red=settings.value("red/textview",206).toInt();
    green=settings.value("green/textview",224).toInt();
    blue=settings.value("blue/textview",255).toInt();
    colorDialog->setCurrentColor(QColor(red,green,blue));
    connect(colorDialog,SIGNAL(colorSelected(QColor)),this,SLOT(textviewColorChange(QColor)));
    colorDialog->exec();
}
void Calculator::windowColorChange(QColor color)
{
    isChangeColor=true;
    QPalette bgpal;
    bgpal.setColor(QPalette::Background,color);
    setPalette(bgpal);
    QSettings settings;
    settings.setValue("red/window",color.red());
    settings.setValue("green/window",color.green());
    settings.setValue("blue/window",color.blue());
}
void Calculator::textviewColorChange(QColor color)
{
    isChangeColor=true;
    QPalette bgpal;
    bgpal.setColor(QPalette::Base,color);
    express_lineEdit->setPalette(bgpal);
    result_lineEdit->setPalette(bgpal);
    memory_lineEdit->setPalette(bgpal);
    QSettings settings;
    settings.setValue("red/textview",color.red());
    settings.setValue("green/textview",color.green());
    settings.setValue("blue/textview",color.blue());
}
void Calculator::showFontDialog()
{
    QFontDialog *fontDialog = new QFontDialog(this);
    fontDialog->setWindowTitle(tr("Choose expression's font style"));
    QSettings settings;
    QPalette bgpal;
    int red,green,blue;
    red=settings.value("red/window",152).toInt();
    green=settings.value("green/window",204).toInt();
    blue=settings.value("blue/window",222).toInt();
    bgpal.setColor(QPalette::Background, QColor(red,green,blue));
    fontDialog->setPalette(bgpal);
    QFont font;
    font.fromString(settings.value("Font").toString());
    fontDialog->setCurrentFont(font);
    connect(fontDialog,SIGNAL(fontSelected(QFont)),this,SLOT(expressionFontChange(QFont)));
    fontDialog->exec();
}
void Calculator::expressionFontChange(QFont font)
{
    isChangeFont=true;
    QString sizeStr;
    sizeStr=QString("font-size : %1px").arg(font.pointSize());
    express_lineEdit->setFont(font);
    result_lineEdit->setFont(font);
    memory_lineEdit->setFont(font);
    express_lineEdit->setStyleSheet(sizeStr);
    result_lineEdit->setStyleSheet(sizeStr);
    memory_lineEdit->setStyleSheet(sizeStr);
    QSettings settings;
    settings.setValue("Font",font.toString());
}
void Calculator::defaultSettings()
{
    QSettings settings;
    //恢复背景色
    isChangeColor=false;
    QPalette bgpal;
    settings.setValue("red/window",152);
    settings.setValue("green/window",204);
    settings.setValue("blue/window",222);
    bgpal.setColor(QPalette::Background,QColor(152,204,222));
    setPalette(bgpal);
    settings.setValue("red/textview",206);
    settings.setValue("green/textview",224);
    settings.setValue("blue/textview",255);
    bgpal.setColor(QPalette::Base,QColor(206,224,255));
    express_lineEdit->setPalette(bgpal);
    result_lineEdit->setPalette(bgpal);
    memory_lineEdit->setPalette(bgpal);
    //恢复默认字体
    isChangeFont=false;
    QFont font("Arial",20);
    settings.setValue("Font",font.toString());
    express_lineEdit->setFont(font);
    result_lineEdit->setFont(font);
    memory_lineEdit->setFont(font);
    express_lineEdit->setStyleSheet("font-size : 20px");
    result_lineEdit->setStyleSheet("font-size : 20px");
    memory_lineEdit->setStyleSheet("font-size : 20px");
    //窗口不置顶
    if(topHintAction->isChecked())
    {
        topHintAction->setChecked(false);
        settings.setValue("TopHint",0);
        setWindowFlags(Qt::Widget);
        show();
    }
}
void Calculator::getHugeCalcWidget()
{
    HugeCalc *hugecalc=new HugeCalc;
    hugecalc->show();
}
void Calculator::getLinearAlgebraWidget()
{
    LinearAlgebra *linearAlgebra=new LinearAlgebra;
    linearAlgebra->show();
}
void Calculator::getnonLinearAlgebraWidget()
{
    nonLinearAlgebra *nonlinearAlgebra=new nonLinearAlgebra;
    nonlinearAlgebra->show();
}
void Calculator::help()
{
    /*
    QUrl url("C:\\Users\\Administrator\\Desktop\\gongcheng\\Readme.html");
    url.setScheme("file");
    QDesktopServices::openUrl(url);
    */
    QSettings settings;
    QPalette bgpal;
    int red,green,blue;
    red=settings.value("red/window",152).toInt();
    green=settings.value("green/window",204).toInt();
    blue=settings.value("blue/window",222).toInt();
    bgpal.setColor(QPalette::Background, QColor(red,green,blue));
    QDialog *helpDialog=new QDialog(this);
    helpDialog->setPalette(bgpal);
    helpDialog->setWindowTitle(tr("Help"));
    QPlainTextEdit *textEdit=new QPlainTextEdit;
    textEdit->setReadOnly(true);
    QFile file("readme.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    textEdit->setPlainText(in.readAll());
    file.close();
    QPalette *pal =new QPalette;
    pal->setColor(QPalette::Text,QColor(0,0,255));
    red=settings.value("red/textview",206).toInt();
    green=settings.value("green/textview",224).toInt();
    blue=settings.value("blue/textview",255).toInt();
    pal->setColor(QPalette::Base,QColor(red,green,blue));
    QFont font;
    font.setPixelSize(20);
    textEdit->setFont(font);
    textEdit->setPalette(*pal);
    QVBoxLayout *layout=new QVBoxLayout(helpDialog);
    layout->addWidget(textEdit);
    helpDialog->resize(735,400);
    helpDialog->show();
}
void Calculator::about()
{
    About *aboutDialog=new About(this);
    aboutDialog->show();
}
void Calculator::giveSuggestions()
{
    QDialog *suggestDialog=new QDialog(this);
    suggestDialog->resize(450,200);
    suggestDialog->setWindowTitle(tr("Give Some Suggestions"));
    QPlainTextEdit *suggestion=new QPlainTextEdit
                           (tr("   首先，非常感谢您使用此计算器，愿它能给您带来方便快捷的服务！\n\n"
                                "   1、如果您发现了 bug，请您及时将 bug 描述并反馈给作者（若同时附上相关截图则更好），以便及时修正。\n"
                                "   2、如您有关于\"进化算法求多项式根和快速傅里叶变换求大整数乘法\"，及有关大整数计算、矩阵中的相关算法等资料"
                                    "（或网上链接），请您与作者联系交流，以便共同进步\n"
                                "   3、如果您在使用过程中，发现有不合理之处、或有好的建议，也请您及时与作者讨论，以便逐步完善\n"
                                "   4、对于善意的批评和建议、对于有价值的反馈，作者将会特别致谢。\n"
                                "   5、邮箱地址：815111457@qq.com 或caolijie0226@163.com\n"));
    suggestion->setReadOnly(true);
    QHBoxLayout *mainlayout=new QHBoxLayout;
    mainlayout->addWidget(suggestion);
    suggestDialog->setLayout(mainlayout);
    QPalette pal;
    QSettings settings;
    int red,green,blue;
    red=settings.value("red/window",152).toInt();
    green=settings.value("green/window",204).toInt();
    blue=settings.value("blue/window",222).toInt();
    pal.setColor(QPalette::Background, QColor(red,green,blue));
    suggestDialog->setPalette(pal);
    red=settings.value("red/textview",206).toInt();
    green=settings.value("green/textview",224).toInt();
    blue=settings.value("blue/textview",255).toInt();
    pal.setColor(QPalette::Base,QColor(red,green,blue));
    pal.setColor(QPalette::Text,QColor(0,0,255));
    suggestion->setPalette(pal);
    suggestDialog->show();
}
void Calculator::ElseTools()
{
    QProcess p;
    if(Geometers_Sketchpad_Action->isChecked())
    {
        QString file("GSP5chs.exe");
        p.startDetached(file);
        Geometers_Sketchpad_Action->setChecked(false);
    }
    else if(System_Calculator_Action->isChecked())
    {
        QString file("calc.exe");
        p.startDetached(file);
        System_Calculator_Action->setChecked(false);
    }
}
