#include"nonLinearAlgebra.h"
#include"Complex.h"
#include<QMessageBox>
#include<QVBoxLayout>
#include<QLineEdit>
#include<QLabel>
#include<QSettings>
#include<qmath.h>
nonLinearAlgebra::nonLinearAlgebra(QWidget *parent):QWidget(parent)
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
    plainTextEdit->setPalette(bgpal);
    move(QPoint(600,350));
    plainTextEdit->installEventFilter(this);//调用installEventFilter（）注册需要管理的对象
    plainTextEdit->setFocus();
   // plainTextEdit->setReadOnly(true);
}
void nonLinearAlgebra::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton ret;
    ret = QMessageBox::question(this, tr("Polynomial for Roots Tool"),
                  tr("Are you sure you want to close this Window?"),
                  QMessageBox::Ok| QMessageBox::Cancel,QMessageBox::Cancel);
    if (ret == QMessageBox::Ok) {
         event->accept();
    } else {
         event->ignore();
    }
}
void nonLinearAlgebra::on_num0PushButton_clicked()
{
    plainTextEdit->textCursor().insertText("0");
}
void nonLinearAlgebra::on_num1PushButton_clicked()
{
    plainTextEdit->textCursor().insertText("1");
}
void nonLinearAlgebra::on_num2PushButton_clicked()
{
    plainTextEdit->textCursor().insertText("2");
}
void nonLinearAlgebra::on_num3PushButton_clicked()
{
    plainTextEdit->textCursor().insertText("3");
}
void nonLinearAlgebra::on_num4PushButton_clicked()
{
    plainTextEdit->textCursor().insertText("4");
}
void nonLinearAlgebra::on_num5PushButton_clicked()
{
    plainTextEdit->textCursor().insertText("5");
}
void nonLinearAlgebra::on_num6PushButton_clicked()
{
    plainTextEdit->textCursor().insertText("6");
}
void nonLinearAlgebra::on_num7PushButton_clicked()
{
    plainTextEdit->textCursor().insertText("7");
}
void nonLinearAlgebra::on_num8PushButton_clicked()
{
    plainTextEdit->textCursor().insertText("8");
}
void nonLinearAlgebra::on_num9PushButton_clicked()
{
    plainTextEdit->textCursor().insertText("9");
}
void nonLinearAlgebra::on_pointPushButton_clicked()
{
    QTextCursor cursor=plainTextEdit->textCursor();
    if(cursor.atStart())
        {plainTextEdit->textCursor().insertText("0.");return;}
    QChar ch=cursor.document()->toPlainText()[cursor.position()-1];
    if(ch.isDigit())
        plainTextEdit->textCursor().insertText(".");
    else
        plainTextEdit->textCursor().insertText("0.");
}
void nonLinearAlgebra::on_iPushButton_clicked()
{
    plainTextEdit->textCursor().insertText("i");
}
void nonLinearAlgebra::on_leftbracketPushButton_clicked()
{
    plainTextEdit->textCursor().insertText("(");
}
void nonLinearAlgebra::on_rightbracketPushButton_clicked()
{
    plainTextEdit->textCursor().insertText(")");
}
void nonLinearAlgebra::on_variablePushButton_clicked()
{
    QTextCursor cursor=plainTextEdit->textCursor();
    if(cursor.atStart())
        {plainTextEdit->textCursor().insertText("x");return;}
    QString str=(cursor.document()->toPlainText()).left(cursor.position());
    int len=str.length();
    if(str[len-1].isDigit()||str[len-1]==')')
        plainTextEdit->textCursor().insertText("*x");
    else if(str[len-1]=='i')
    {
        int numbracket=0;
        for(int i=0;i<len;i++){
            if(str[i]=='(')numbracket++;
            if(str[i]==')')numbracket--;
        }
        if(numbracket<=0)
            plainTextEdit->textCursor().insertText("*x");
        else
            plainTextEdit->textCursor().insertText(")*x");
    }
    else
        plainTextEdit->textCursor().insertText("x");
}
void nonLinearAlgebra::on_addPushButton_clicked()
{
    plainTextEdit->textCursor().insertText("+");
}
void nonLinearAlgebra::on_subtractPushButton_clicked()
{
    plainTextEdit->textCursor().insertText("-");
}
void nonLinearAlgebra::on_multiplyPushButton_clicked()
{
    plainTextEdit->textCursor().insertText("*");
}
void nonLinearAlgebra::on_powerPushButton_clicked()
{
    plainTextEdit->textCursor().insertText("^");
}
void nonLinearAlgebra::on_backspacePushButton_clicked()
{
     QTextCursor cursor =plainTextEdit->textCursor();
     //判断当前是否选中了文本，如果选中了文本则取消选中的文本，再删除前一个字符
     if(cursor.hasSelection())
         cursor.clearSelection();
     //删除前一个字符
     cursor.deletePreviousChar();
     //设置当前的光标为更改后的光标
     plainTextEdit->setTextCursor(cursor);
}
void nonLinearAlgebra::on_plainTextEdit_textChanged()
{
    QString str=plainTextEdit->toPlainText();
    if(str.isEmpty())
    {
        backspacePushButton->setEnabled(false);
        clearPushButton->setEnabled(false);
        rootsPushButton->setEnabled(false);
        valuesPushButton->setEnabled(false);
        return ;
    }
    if(!str.contains('x'))
    {
        rootsPushButton->setEnabled(false);
        valuesPushButton->setEnabled(false);
        return ;
    }
    QChar charPre=str[0],charCur=str[0];
    int i;
    rootsPushButton->setEnabled(true);
    valuesPushButton->setEnabled(true);
    if(charPre=='+'||charPre=='*'||charPre=='^'||charPre=='.'||charPre==')')
    {
        rootsPushButton->setEnabled(false);
        valuesPushButton->setEnabled(false);
        return;
    }
    int numbracket=0;
    for(int i=0;i<str.length();i++){
        if(str[i]=='(')numbracket++;
        if(str[i]==')')numbracket--;
    }
    if(numbracket!=0)
    {
        rootsPushButton->setEnabled(false);
        valuesPushButton->setEnabled(false);
        return;
    }
    for(i=1;i<str.length();++i)
    {
        charCur=str[i];
        if(!charPre.isDigit())
        {
            if(charPre=='*'&&charCur=='x')
                {charPre=charCur;continue;}
            else if((charPre=='+'||charPre=='-')&&(charCur.isDigit()||charCur=='x'||charCur=='('||charCur=='i'))
                {charPre=charCur;continue;}
            else if((charPre=='.'||charPre=='^')&&charCur.isDigit())
                {charPre=charCur;continue;}
            else if(charPre=='x'&&(charCur=='^'||charCur=='+'||charCur=='-'))
                {charPre=charCur;continue;}
            else if(charPre=='('&&(charCur.isDigit()||charCur=='-'||charCur=='i'))
                {charPre=charCur;continue;}
            else if(charPre==')'&&(charCur=='*'||charCur=='x'||charCur=='+'||charCur=='-'))
                {charPre=charCur;continue;}
            else if(charPre=='i'&&(charCur==')'||charCur=='*'||charCur=='+'||charCur=='-'))
                {charPre=charCur;continue;}
            else
                {
                    rootsPushButton->setEnabled(false);
                    break;
            }
        }
        else    //charPre 为数字
        {
            if(charCur=='.')
            {
                bool work=true;
                for(int j=i-1;j>=0;j--)
                {
                    if(str[j].isDigit())continue;
                    if(str[j]=='.'||str[j]=='^')
                    {
                        valuesPushButton->setEnabled(false);
                        work=false;break;
                    }
                    else break;
                }
                if(work) charPre=charCur;
                else break;
            }
            else if(charCur=='^'||charCur=='(')
            {rootsPushButton->setEnabled(false);break;}
            else
                charPre=charCur;
        }
    }
    if(!charCur.isDigit()&&charCur!='x'&&charCur!=')'&&charCur!='i')
    {rootsPushButton->setEnabled(false);}
    if(!rootsPushButton->isEnabled())
        valuesPushButton->setEnabled(false);
    /*
    QTextCursor highlightCursor = plainTextEdit->document()->find("+");
    if (highlightCursor.isNull() == false) {
        QTextCharFormat highlightFormat;
        highlightFormat.setUnderlineColor(Qt::red);
        highlightFormat.setUnderlineStyle(QTextCharFormat::SpellCheckUnderline);
        isChange = false;
        highlightCursor.mergeCharFormat(highlightFormat);
    }*/
    return;
}

void nonLinearAlgebra::on_plainTextEdit_cursorPositionChanged()
{
    QTextCursor cursor=plainTextEdit->textCursor();
    numGroupBox->setEnabled(true);
    if(cursor.atStart())
    {
        addPushButton->setEnabled(false);
        subtractPushButton->setEnabled(true);
        multiplyPushButton->setEnabled(false);
        powerPushButton->setEnabled(false);
        leftbracketPushButton->setEnabled(true);
        iPushButton->setEnabled(true);
        variablePushButton->setEnabled(true);
        pointPushButton->setEnabled(false);
        return ;
    }
    backspacePushButton->setEnabled(true);
    clearPushButton->setEnabled(true);
    //获取光标左边的字符串
    int pos=cursor.position();
    QString str=(cursor.document()->toPlainText()).left(pos);
    QChar ch=str[pos-1];
    int numbracket=0;
    for(int i=0;i<str.length();i++){
        if(str[i]=='(')numbracket++;
        if(str[i]==')')numbracket--;
    }
    if(numbracket>0){
        leftbracketPushButton->setEnabled(false);
        rightbracketPushButton->setEnabled(true);
    }
    else{
        rightbracketPushButton->setEnabled(false);
    }
    if(ch.isDigit())
    {
        addPushButton->setEnabled(true);
        subtractPushButton->setEnabled(true);
        if(numbracket<=0)
            multiplyPushButton->setEnabled(true);
        powerPushButton->setEnabled(false);
        if(numbracket>0)
            iPushButton->setEnabled(true);
        leftbracketPushButton->setEnabled(false);
        variablePushButton->setEnabled(true);
        pointPushButton->setEnabled(true);
        for(int i=pos-2;i>=0;i--)
        {
            if(str[i].isDigit())
                continue;
            else if(str[i]=='.'||str[i]=='^')
                {
                 pointPushButton->setEnabled(false);
                 if(str[i]=='^')
                 {  variablePushButton->setEnabled(false);
                    multiplyPushButton->setEnabled(false);
                 }
                 break;
                }
            else
                break;
        }
    }
    else if(ch=='+'||ch=='-')
    {
        addPushButton->setEnabled(false);
        subtractPushButton->setEnabled(false);
        multiplyPushButton->setEnabled(false);
        powerPushButton->setEnabled(false);
        iPushButton->setEnabled(true);
        if(numbracket==0)
            leftbracketPushButton->setEnabled(true);
        rightbracketPushButton->setEnabled(false);
        variablePushButton->setEnabled(true);
    }
    else if(ch=='*')
    {
        addPushButton->setEnabled(false);
        subtractPushButton->setEnabled(false);
        multiplyPushButton->setEnabled(false);
        powerPushButton->setEnabled(false);
        numGroupBox->setEnabled(false);
        leftbracketPushButton->setEnabled(false);
        variablePushButton->setEnabled(true);
    }
    else if(ch=='^'||ch=='.')
    {
        addPushButton->setEnabled(false);
        subtractPushButton->setEnabled(false);
        multiplyPushButton->setEnabled(false);
        powerPushButton->setEnabled(false);
        pointPushButton->setEnabled(false);
        iPushButton->setEnabled(false);
        leftbracketPushButton->setEnabled(false);
        variablePushButton->setEnabled(false);
    }
    else if(ch=='x')
    {
        addPushButton->setEnabled(true);
        subtractPushButton->setEnabled(true);
        multiplyPushButton->setEnabled(false);
        powerPushButton->setEnabled(true);
        numGroupBox->setEnabled(false);
        leftbracketPushButton->setEnabled(false);
        rightbracketPushButton->setEnabled(false);
        variablePushButton->setEnabled(false);
    }
    else if(ch=='(')
    {
        addPushButton->setEnabled(false);
        subtractPushButton->setEnabled(true);
        multiplyPushButton->setEnabled(false);
        powerPushButton->setEnabled(false);
        iPushButton->setEnabled(true);
        rightbracketPushButton->setEnabled(false);
        variablePushButton->setEnabled(false);
    }
    else if(ch==')')
    {
        addPushButton->setEnabled(true);
        subtractPushButton->setEnabled(true);
        multiplyPushButton->setEnabled(true);
        powerPushButton->setEnabled(false);
        numGroupBox->setEnabled(false);
        variablePushButton->setEnabled(true);
    }
    else if(ch=='i')
    {
        addPushButton->setEnabled(true);
        subtractPushButton->setEnabled(true);
        multiplyPushButton->setEnabled(false);
        powerPushButton->setEnabled(false);
        numGroupBox->setEnabled(false);
        leftbracketPushButton->setEnabled(false);
        variablePushButton->setEnabled(true);
    }
    else
    {
        cursor.deletePreviousChar();
    }
    plainTextEdit->setFocus();
}

void nonLinearAlgebra::on_clearPushButton_clicked()
{
    plainTextEdit->clear();
    plainTextEdit->setFocus();
}

bool nonLinearAlgebra::eventFilter(QObject *target, QEvent *event)
{
   if(target ==plainTextEdit)//此判断可以省略,此程序中必进入此判断，但是有此句判断让程序更加规范
   {
         if (event->type() == QEvent::KeyPress)
         {
             QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
             int code=keyEvent->key();
             if(code==Qt::Key_Backspace||code==Qt::Key_Left||code==Qt::Key_Right)
                 return false;
             else
             {
                 QApplication::beep();return true;
             }
         }
         else
             return false;
   }
   return QObject::eventFilter(target, event);
}
void nonLinearAlgebra::on_valuesPushButton_clicked()
{
    QDialog *dialog=new QDialog(this);
    dialog->setWindowTitle(tr("Polynomial for Roots Tool"));
    QVBoxLayout *vlayout=new QVBoxLayout(dialog);
    QHBoxLayout *hlayout = new QHBoxLayout();
    QPushButton *CalcButton = new QPushButton;
    CalcButton->setText(tr("Calc"));
    QLabel *variableLabel,*resultLabel;
    variableEdit = new  QLineEdit;
    resultEdit  = new QLineEdit;
    resultEdit->setReadOnly(true);
    variableLabel = new QLabel(tr("x's value: "));
    resultLabel = new QLabel(tr("poly's value: "));
    vlayout->addWidget(variableLabel);
    vlayout->addWidget(variableEdit);
    vlayout->addWidget(resultLabel);
    vlayout->addWidget(resultEdit);
    hlayout->addStretch();
    hlayout->addWidget(CalcButton);
    vlayout->addLayout(hlayout);
    connect(CalcButton,SIGNAL(clicked()),this,SLOT(getValue()));

    QSettings settings;
    QPalette bgpal;
    int red,green,blue;
    red=settings.value("red/window",152).toInt();
    green=settings.value("green/window",204).toInt();
    blue=settings.value("blue/window",222).toInt();
    bgpal.setColor(QPalette::Background, QColor(red,green,blue));
    dialog->setPalette(bgpal);
    red=settings.value("red/textview",206).toInt();
    green=settings.value("green/textview",224).toInt();
    blue=settings.value("blue/textview",255).toInt();
    bgpal.setColor(QPalette::Base,QColor(red,green,blue));
    variableEdit->setPalette(bgpal);
    resultEdit->setPalette(bgpal);
    dialog->show();
}
void nonLinearAlgebra::on_rootsPushButton_clicked()
{
    Complex *roots,*values;
    Polynomial poly;
    if(getPoly(poly,true)==false) //获取多项式失败
       return ;
    int i,n = poly.getOrder();
    int count=0;
    while(count++<5)
    {
        roots = new Complex[n];
        GeneticAlgorithm ga(poly);
        if(ga.searchRoot(roots)==true)
            break;
    }
    values = new Complex[n];
    for(i=0;i<n;i++)
        values[i] = poly.poly_value(roots[i]);//求对应的函数值
    if(count==6)
    {
        QMessageBox::information(this,tr("Polynomial for Roots Tool"),
                tr("sorry,the program can't search the all roots"));
    }
    QPlainTextEdit *result=new QPlainTextEdit;
    QString str;
    result->setReadOnly(true);
    QDialog *dialog=new QDialog(this);
    dialog->setWindowTitle(tr("Polynomial for Roots Tool"));
    result->setPlainText(tr("The polynomial has %1 root(s):").arg(n));
    str.clear();
    for(i=0;i<n;i++)
    {
        str+=roots[i].toString(6);//保留有效数字6位
        str+='\n';
    }
    str+='\n';
    str+=tr("The values of polynomial are:");
    str+='\n';
    for(i=0;i<n;i++)
    {
        str += values[i].toString(6);
        str += '\n';
    }
    result->appendPlainText(str);
    QVBoxLayout *vlayout=new QVBoxLayout(dialog);
    vlayout->addWidget(result);
    QSettings settings;
    QPalette bgpal;
    int red,green,blue;
    red=settings.value("red/window",152).toInt();
    green=settings.value("green/window",204).toInt();
    blue=settings.value("blue/window",222).toInt();
    bgpal.setColor(QPalette::Background, QColor(red,green,blue));
    dialog->setPalette(bgpal);
    red=settings.value("red/textview",206).toInt();
    green=settings.value("green/textview",224).toInt();
    blue=settings.value("blue/textview",255).toInt();
    bgpal.setColor(QPalette::Base,QColor(red,green,blue));
    result->setPalette(bgpal);
    dialog->show();
}
void nonLinearAlgebra::getValue()
{
    Polynomial p;
    if(getPoly(p,false)==false)
    {return ;}
    QString str = variableEdit->text();
    if(str.contains('i')){
        int index01 = str.lastIndexOf('+');
        int index02 = str.lastIndexOf('-');
        if(index01>0){
            str.insert(index01,' ');
            str.insert(index01+2,' ');
        }
        if(index01<=0&&index02>0)
        {
            str.insert(index02,' ');
            str.insert(index02+2,' ');
        }
    }
    Complex x;
    x.setComplex(str);
    Complex value = p.poly_value(x);
    resultEdit->setText(value.toString(6));
}
bool nonLinearAlgebra::getPoly(Polynomial &poly,bool ok)
{
    QString express=plainTextEdit->toPlainText(),str;
    int len=express.length(),i,n=0;
    Complex dl(0);
    Complex a[21];
    QChar ch;
    for(i=0;i<21;i++)
        a[i]=Complex(0);
    if(express[0]=='x')
        dl=Complex(1);
    for(i=0;i<len;)
    {
       str.clear();
       ch=express[i];
       if(ch=='(')
       {
           bool isNegative=false;
           if(i>0&&express[i-1]=='-')
               isNegative=true;
           i++;ch=express[i];dl=0;
           while(ch!=')'){
               str="";
               if(ch!='i'){
                   do{
                      str+=ch;
                      ch=express[++i];
                   }while(ch.isDigit()||ch=='.');
               }
               if(str=="+"||str=="-"||str=="")
               {
                   str+='1';
               }
               if(ch=='i'){
                    ch=express[++i];
                    dl+=Complex(0,str.toDouble());
               }
               else
                    dl+=Complex(str.toDouble());
           }
           if(isNegative)
               dl=0-dl;
           if(i==len-1||(express[i+1]!='x'&&express[i+1]!='*'))
               a[0]+=dl;
           i++;
           continue;
       }
       if(ch.isDigit()||ch=='+'||ch=='-')
       {
           do{
              str+=ch;
              if(i<len-1)
                 ch=express[++i];
              else {i++;break;}
           }while(ch.isDigit()||ch=='.');
           if((str=="+"||str=="-")&&ch!='(')str+='1';
           if(ch=='i'){
                if(i<len-1)
                    ch=express[++i];
                dl=Complex(0,str.toDouble());
           }
           else
                dl=Complex(str.toDouble());
           if(ch!='*'&&ch!='x'&&ch!='(')
               a[0]+=dl;
           continue;
       }
       if(ch=='^')
       {
           ch=express[++i];
           do{
               str+=ch;
               if(i<len-1)
                  ch=express[++i];
               else
                  {i++; break;}
            }while(ch.isDigit());
           if(str.toInt()>20){
               QMessageBox::warning(this, tr("Polynomial for Roots Tool"),
                                 tr("The maxinum order of the polynomial is 20!"),
                                 QMessageBox::Ok);
               return false;
               }
           a[str.toInt()]=dl;
           continue;
       }
       else if(ch=='x')
       {
           if(i==len-1||express[i+1]!='^')
              {a[1]+=dl;}
           i++;
           continue;
       }
       else
           i++;
    }
    for(i=20;i>0;i--)
    {
        if(!a[i].isZero())
            {n=i;break;}
    }
    if(n==0)
    {
        QMessageBox::warning(this, tr("Polynomial for Roots Tool"),
                          tr("The order of the polynomial must be bigger than 0!"),
                          QMessageBox::Ok);
        return false;
    }
    if(ok==true){
        for(i=0;i<=n;++i)
            a[i]=a[i]/a[n];
    }
    for(i=0;i<=n/2;i++)
    {
        Complex temp=a[i];
        a[i]=a[n-i];
        a[n-i]=temp;
    }
    poly = Polynomial(n,a);
    return true;
}
