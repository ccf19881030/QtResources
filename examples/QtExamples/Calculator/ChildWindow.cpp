 #include"ChildWindow.h"
#include<QMessageBox>
#include<QSettings>
#include<QTextBlock>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QBitmap>
#include<cmath>
#include<QTimer>
History::History( QWidget * parent):QDialog(parent)
{
    setupUi(this);
    QPalette bgpal;
    QSettings settings;
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

    plainTextEdit->installEventFilter(this);
}
bool History::eventFilter(QObject *target, QEvent *event)
{
   if(target ==plainTextEdit)//此判断可以省略,此程序中必进入此判断，但是有此句判断让程序更加规范
   {
         if (event->type() == QEvent::KeyPress)
         {
             QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
             int code=keyEvent->key();
             if(code==Qt::Key_Up)
             {
                 plainTextEdit->moveCursor(QTextCursor::Up);
                 return false;
             }
             if(code==Qt::Key_Down)
             {
                 plainTextEdit->moveCursor(QTextCursor::Down);
                 return false;
             }
         }
         else
             return false;
   }
   return QObject::eventFilter(target, event);
}
void History::on_clearPushButton_clicked()
{
   QMessageBox::StandardButton ret;
   if(!plainTextEdit->toPlainText().isEmpty())
   {
        ret = QMessageBox::warning(this, tr("History Record"),
                              tr("Are you sure you want to clear all the Records?"),
                              QMessageBox::Ok| QMessageBox::Cancel);
        if (ret == QMessageBox::Ok)
        {
            QSettings settings;
            settings.setValue("historyRecord",QStringList());
            plainTextEdit->clear();
            lineEdit->clear();
            usePushButton->setEnabled(false);
            copyPushButton->setEnabled(false);
            deletePushButton->setEnabled(false);
            clearPushButton->setEnabled(false);
        }
    }
}
void History::on_usePushButton_clicked()
{close();}
void History::on_deletePushButton_clicked()
{
    QSettings settings;
    QStringList historyRecord = settings.value("historyRecord").toStringList();
    historyRecord.removeAll(lineEdit->text());
    settings.setValue("historyRecord",historyRecord);
/*
    QTextCursor tc = plainTextEdit->textCursor();
    QTextLayout* lo = tc.block().layout();
    int pos = tc.positionInBlock();
    int rowIndex = lo->lineForTextPosition(pos).lineNumber() + tc.block().firstLineNumber();
*/
    int numRecords=historyRecord.size();
    plainTextEdit->clear();
    for(int i=0;i<numRecords;++i)
    {
        QString record=historyRecord[i];
        plainTextEdit->appendPlainText(record);
    }

    if(numRecords==0)
    {
        usePushButton->setEnabled(false);
        copyPushButton->setEnabled(false);
        deletePushButton->setEnabled(false);
        clearPushButton->setEnabled(false);
    }
}
void History::on_copyPushButton_clicked()
{
    lineEdit->selectAll();
    lineEdit->copy();
}
void History::on_plainTextEdit_cursorPositionChanged()
{
    if(!plainTextEdit->toPlainText().isEmpty())
    {
        QList<QTextEdit::ExtraSelection> extraSelections;
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(0,0,170).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor =plainTextEdit->textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);

        //暂时标记指定的文档中的一部分，用指定的颜色
        plainTextEdit->setExtraSelections(extraSelections);

        usePushButton->setEnabled(true);
        deletePushButton->setEnabled(true);
        copyPushButton->setEnabled(true);
        clearPushButton->setEnabled(true);

        //获取光标所在行数
        QTextCursor tc = plainTextEdit->textCursor();
        QTextLayout* lo = tc.block().layout();
        int pos = tc.positionInBlock();
        int rowIndex = lo->lineForTextPosition(pos).lineNumber() + tc.block().firstLineNumber();

        lineEdit->setText(plainTextEdit->document()->findBlockByLineNumber(rowIndex).text());
        //plainTextEdit->document()->findBlockByLineNumber(rowIndex).text() 获取指定行的内容
    }
    else
    {
        usePushButton->setEnabled(false);
        deletePushButton->setEnabled(false);
        copyPushButton->setEnabled(false);
        clearPushButton->setEnabled(false);
        lineEdit->clear();
    }
}

About::About( QWidget * parent):QDialog(parent)
{
    setupUi(this);
    QPalette bgpal;
    QSettings settings;
    int red,green,blue;
    red=settings.value("red/window",152).toInt();
    green=settings.value("green/window",204).toInt();
    blue=settings.value("blue/window",222).toInt();
    bgpal.setColor(QPalette::Background, QColor(red,green,blue));
    setPalette(bgpal);
    QPixmap pixmap(":/images/banben.png");
    QPalette   palette;
    palette.setBrush(frame->backgroundRole(),QBrush(pixmap));
    frame->setPalette(palette);
    frame->setMask(pixmap.mask());  //可以将图片中透明部分显示为透明的
    frame->setAutoFillBackground(true);
}
Constant::Constant( QWidget * parent):QDialog(parent)
{
    setupUi(this);
    QPalette bgpal;
    QSettings settings;
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
    tableWidget->setPalette(bgpal);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //设置选择行为，以行为单位
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection); //设置选择模式，选择单行
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //设置禁止编辑模式
    tableWidget->selectRow(0);     //选中第一行
    tableWidget->setColumnWidth(2,160);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addStretch();
    hlayout->addWidget(usePushButton);
    hlayout->addWidget(closePushButton);
    mainLayout->addWidget(tableWidget);
    mainLayout->addLayout(hlayout);

    setMinimumSize(400,300);
    setMaximumSize(500,450);
}
Variable *Variable::m_instance = 0;
Variable::Variable( QWidget * parent):QDialog(parent)
{
    setupUi(this);
    QPalette bgpal;
    QSettings settings;
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
    tableWidget->setPalette(bgpal);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *hlayout = new QHBoxLayout();
    hlayout->addStretch();
    hlayout->addWidget(clearButton);
    hlayout->addWidget(calcButton);
    mainLayout->addWidget(tableWidget);
    mainLayout->addLayout(hlayout);

    setMinimumSize(255,200);
    setMaximumSize(255,200);
    tableWidget->setColumnWidth(1,140);
    tableWidget->setCurrentCell(0,1);
    tableWidget->verticalHeader()->setVisible(false);
    if(settings.value("Variable_X_Bool",0).toBool())
    {
        tableWidget->setItem(0,1,new QTableWidgetItem(settings.value("Variable_X_Value").toString()));
        tableWidget->item(0,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }
    if(settings.value("Variable_Y_Bool",0).toBool())
    {
        tableWidget->setItem(1,1,new QTableWidgetItem(settings.value("Variable_Y_Value").toString()));
        tableWidget->item(1,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }
    if(settings.value("Variable_Z_Bool",0).toBool())
    {
        tableWidget->setItem(2,1,new QTableWidgetItem(settings.value("Variable_Z_Value").toString()));
        tableWidget->item(2,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }
}
void Variable::clearVariables()
{
    QSettings settings;
    tableWidget->item(0,1)->setText("");
    tableWidget->item(1,1)->setText("");
    tableWidget->item(2,1)->setText("");
    settings.setValue("Variable_X_Bool",false);
    settings.setValue("Variable_Y_Bool",false);
    settings.setValue("Variable_Z_Bool",false);
}
void Variable::updateVariables(QTableWidgetItem *item)
{
    QString str;
    QSettings settings;
    str=item->text();
    int row=item->row();
    if(!str.isEmpty())
    {
        if(row==0)
        {
            settings.setValue("Variable_X_Bool",true);
            settings.setValue("Variable_X_Value",str);
        }
        else if(row==1)
        {
            settings.setValue("Variable_Y_Bool",true);
            settings.setValue("Variable_Y_Value",str);
        }
        else
        {
            settings.setValue("Variable_Z_Bool",true);
            settings.setValue("Variable_Z_Value",str);
        }
    }
}
