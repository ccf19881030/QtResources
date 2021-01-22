#ifndef MYSTATICCLASS_H
#define MYSTATICCLASS_H

#endif // MYSTATICCLASS_H

#include "myinclude.h"

class MyHelper : public QObject
{
public:
    MyHelper();~MyHelper();

    //获取当前路径
    static QString GetCurrentPath()
    {
        return QString(QCoreApplication::applicationDirPath()+"/");
    }

    //播放声音
    static void PlaySound(QString soundName)
    {
        QSound::play(soundName);
    }

    //延时处理
    static void DelayTime(int msc)
    {
        QTime t=QTime::currentTime().addMSecs(msc);
        while(QTime::currentTime()<t)
        {
            QCoreApplication::processEvents(QEventLoop::AllEvents,100);
        }
    }

    //获取当前日期时间星期
    static QString GetLongDateTime()
    {
        QDateTime time=QDateTime::currentDateTime();
        return time.toString("yyyy年MM月dd日 hh时mm分ss秒 dddd");
    }

    //获取选择文件
    static QString GetFileName(QString filter)
    {
        return QFileDialog::getOpenFileName(NULL,tr("选择文件"),QCoreApplication::applicationDirPath(),filter);
    }

    //获取选择文件集合
    static QStringList GetFileNames(QString filter)
    {
        return QFileDialog::getOpenFileNames(NULL,tr("选择文件"),QCoreApplication::applicationDirPath(),filter);
    }

    //获取选择文件夹中的文件
    static QStringList GetFolderFileNames(QStringList filter)
    {
        QStringList fileList;
        QString strFolder = QFileDialog::getExistingDirectory();
        if (!strFolder.length()==0)
        {
            QDir myFolder(strFolder);

            if (myFolder.exists())
            {
                fileList= myFolder.entryList(filter);
            }
        }
        return fileList;
    }

    //打开网址
    static void OpenUrlOrExe(QString url)
    {
        QDesktopServices::openUrl(QUrl(url));
    }

    //判断是否闰年
    static bool IsLeapYear(QString strDate)
    {
        int year=strDate.left(4).toInt();
        if(((year % 4 ==0) && (year % 100 !=0 ))|| (year % 400 ==0))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    //    //结束自己进程,需要#include "windows.h",这里注释掉，为了跨平台
    //    static void KillMe()
    //    {
    //        DWORD dwProcessID=::GetCurrentProcessId();
    //        HANDLE hProcess=::OpenProcess(PROCESS_TERMINATE,FALSE,dwProcessID);
    //        ::TerminateProcess(hProcess,0);
    //        ::CloseHandle(hProcess);
    //    }
};

class FileHelper : public QObject
{
public:
    FileHelper();~FileHelper();

    //文件是否存在
    static bool FileExists(QString strFile)
    {
        QFile tempFile(strFile);
        if (tempFile.exists())
        {
            return true;
        }
        return false;
    }

    //文件夹是否存在
    static bool FolderExists(QString strFolder)
    {
        QDir tempFolder(strFolder);
        if(tempFolder.exists())
        {
            return true;
        }
        return false;
    }

    //移除文件
    static bool RemoveFile(QString strFile)
    {
        return QFile::remove(strFile);
    }

    //重命名文件
    static bool RenameFile(QString oldName,QString newName)
    {
        return QFile::rename(oldName,newName);
    }

    //获取文件目录
    static QString GetBasePath(QString strFullPath)
    {
        QFileInfo fileInfo(strFullPath);
        return fileInfo.path();
    }

    //获取拓展名
    static QString GetExtension(QString strFile)
    {
        QFileInfo fileInfo(strFile);
        return fileInfo.suffix();
    }

    //获取文件夹名称
    static QString GetFolderName(QString strFullPath)
    {
        QString strPath(strFullPath);
        strPath.replace('\\','/');
        int pos=strPath.lastIndexOf('/');
        return strPath.mid(pos+1);
    }

    //复制文件
    static bool CopyFile(QString sourceFile, QString targetFile)
    {
        if (FileExists(targetFile))
        {
            int ret=QMessageBox::information(NULL,tr("提示"),tr("文件已经存在，是否替换？"),QMessageBox::Yes | QMessageBox::No);
            if (ret!=QMessageBox::Yes)
            {
                return false;
            }
        }
        return QFile::copy(sourceFile,targetFile);
    }

    //判断是否是文件
    static bool IsFile(QString strFile)
    {
        QFileInfo fileInfo(strFile);
        return fileInfo.isFile();
    }

    //判断是否是文件夹
    static bool IsFolder(QString strFolder)
    {
        QFileInfo fileInfo(strFolder);
        return fileInfo.isDir();
    }

    //追加文本
    static bool AppendText(QString strFile, QString strContent )
    {
        QFile inFile(strFile);
        if (!inFile.open(QIODevice::Append | QIODevice::Text))
        {
            QMessageBox::information(NULL,tr("提示"),tr("打开文件出错！"));
            return false;
        }
        QTextStream inStream(&inFile);
        inStream<<strContent;
        inFile.close();
        return true;
    }

    //创建文件夹
    static bool CreateFolder(QString strFolder)
    {
        QDir dir;
        return dir.mkdir(strFolder);
    }

    //创建文件
    static bool CreateFile(QString strFile)
    {
        QFile file(strFile);
        if (!file.open(QIODevice::WriteOnly))
        {
            return false;
        }
        file.close();
        return true;
    }

    //读取文件内容
    static QString GetFileContent(QString strFile)
    {
        QFile file(strFile);
        QString txt;
        if (!file.open(QIODevice::WriteOnly))
        {
            txt= "";
        }
        else
        {
            txt=file.readAll();
        }
        file.close();
        return txt;
    }

};


class FormHelper : public QObject
{
public:
    FormHelper();~FormHelper();

    static void FormQQ(QWidget *frm,int frmHeight)
    {
        if (frm->windowState()!=Qt::WindowMinimized)
        {
            int DeskX=QCursor::pos().x();
            int DeskY=QCursor::pos().y();

            int FrmLeft=frm->geometry().left();
            int FrmRight=frm->geometry().right();
            int FrmTop=frm->geometry().top();
            int FrmBottom=frm->geometry().bottom();

            int FrmWidth=frm->geometry().width();
            int FrmHeight=frm->geometry().height();

            QDesktopWidget desktop;
            int DeskWidth=desktop.availableGeometry().width();
            //int DeskHeight=desktop.availableGeometry().height();

            if (DeskX>FrmLeft-1 && DeskX<FrmRight && DeskY>FrmTop-1 && DeskY<FrmBottom)
            {
                if (FrmTop<=0 && FrmLeft>5 && FrmLeft<DeskWidth-FrmWidth)
                {
                    frm->rect().setTop(0);
                }
                else if (FrmLeft<=0)
                {
                    frm->rect().setLeft(0);
                }
                else if (FrmLeft+FrmWidth>DeskWidth)
                {
                    frm->rect().setLeft(DeskWidth-FrmWidth);
                }
                else
                {
                    if (frmHeight>0)
                    {
                        frm->rect().setHeight(frmHeight);
                        frmHeight=0;
                    }
                }
            }
            else
            {
                if (frmHeight<1)
                {
                    frmHeight=FrmHeight;
                }

                if (FrmTop<=4 && FrmLeft>5 && FrmLeft<DeskWidth-FrmWidth)
                {
                    frm->rect().setTop(3-FrmHeight);

                    if (FrmLeft<=4)
                    {
                        frm->rect().setLeft(-5);
                    }
                    else if (FrmLeft+FrmWidth>=DeskWidth-4)
                    {
                        frm->rect().setLeft(DeskWidth-FrmWidth+5);
                    }
                }
                else if (FrmLeft<=4)
                {
                    frm->rect().setLeft(3-FrmWidth);
                }
                else if (FrmLeft+FrmWidth>=DeskWidth-4)
                {
                    frm->rect().setLeft(DeskWidth-3);
                }
            }
        }
    }


    //窗体居中显示
    static void FormInCenter(QWidget *frm)
    {
        QDesktopWidget desktop;
        int screenX=desktop.availableGeometry().width();
        int screenY=desktop.availableGeometry().height();
        int wndX=frm->width();
        int wndY=frm->height();
        QPoint movePoint(screenX/2-wndX/2,screenY/2-wndY/2);
        frm->move(movePoint);
    }

    //窗体没有最大化按钮
    static void FormNoMaxButton(QWidget *frm)
    {
        frm->setWindowFlags(Qt::WindowMinimizeButtonHint);
    }

    //窗体没有最大化和最小化按钮
    static void FormOnlyCloseButton(QWidget *frm)
    {
        frm->setWindowFlags(Qt::WindowMinMaxButtonsHint);
        frm->setWindowFlags(Qt::WindowCloseButtonHint);
    }

    //设置窗体透明度
    static void FormOpacity(QWidget *frm,double value)
    {
        frm->setWindowOpacity(value);
    }

    //窗体不能改变大小
    static void FormNotResize(QWidget *frm)
    {
        frm->setFixedSize(frm->width(),frm->height());
    }

    //窗体前端显示
    static void FormOnTop(QWidget *frm)
    {
        frm->setWindowFlags(Qt::WindowStaysOnTopHint);
    }

    //窗体后端显示
    static void FormOnBottom(QWidget *frm)
    {
        frm->setWindowFlags(Qt::WindowStaysOnBottomHint);
    }

    //获取桌面大小
    static QSize GetDesktopSize()
    {
        QDesktopWidget desktop;
        return QSize(desktop.availableGeometry().width(),desktop.availableGeometry().height());
    }

    //设置编码为GB2312
    static void SetGB2312Code()
    {
       // QTextCodec *codec=QTextCodec::codecForName("GB2312");
        //QTextCodec::setCodecForLocale(codec);
        //QTextCodec::setCodecForCStrings(codec);
       // QTextCodec::setCodecForTr(codec);
    }

    //设置编码为UTF8
    static void SetUTF8Code()
    {
       // QTextCodec *codec=QTextCodec::codecForName("UTF8");
       // QTextCodec::setCodecForLocale(codec);
      //  QTextCodec::setCodecForCStrings(codec);
       // QTextCodec::setCodecForTr(codec);
    }

    //设置全局为plastique样式
    static void SetPlastiqueStyle()
    {
        QApplication::setStyle(QStyleFactory::create("Plastique"));
        QApplication::setPalette(QApplication::style()->standardPalette());//替换应用程序的颜色组合
    }

    static void SetPlastiqueStyle(QWidget *frm)
    {
        frm->setStyle(QStyleFactory::create("Plastique"));
    }

    static void SetMyStyle(QWidget *frm)
    {
        QString myStyle1="QPushButton {";
        myStyle1.append("border: 2px solid #8f8f91; ");
        myStyle1.append("border-radius: 6px;");
        myStyle1.append("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #f6f7fa, stop: 1 #dadbde); ");
        myStyle1.append("min-width: 80px;}");
        myStyle1.append("QPushButton:pressed {");
        myStyle1.append("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #dadbde, stop: 1 #f6f7fa); }");
        myStyle1.append("QPushButton:default  {");
        myStyle1.append("border-color: navy; /* 使得按钮显示变得更加突出 */}");

        QString myStyle2="QSlider::groove:horizontal {";
        myStyle2.append("border: 1px solid #999999;");
        myStyle2.append("height: 8px;");
        myStyle2.append("background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);");
        myStyle2.append("margin: 2px 0;}");
        myStyle2.append("QSlider::handle:horizontal {");
        myStyle2.append("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f);");
        myStyle2.append("border: 1px solid #5c5c5c;");
        myStyle2.append("width: 18px; margin: -2px 0;");
        myStyle2.append("border-radius: 3px;}");

        QString myStyle3="QGroupBox {";
        myStyle3.append("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,  stop: 0 #E0E0E0, stop: 1 #FFFFFF);");
        myStyle3.append("border: 2px solid gray;");
        myStyle3.append("border-radius: 5px;");
        myStyle3.append("margin-top: 1ex;}");
        myStyle3.append("QGroupBox::title {");
        myStyle3.append("subcontrol-origin: margin; ");
        myStyle3.append("subcontrol-position: top center;");
        myStyle3.append("padding: 0 3px;}");

        frm->setStyleSheet(myStyle1+myStyle2+myStyle3);
    }

    //改变样式
    static bool InstallStyle(QWidget* window,QString styleFile)
    {
        QFile file(styleFile);
        QString strStyleSheet;
        if (!file.open(QIODevice::WriteOnly))
        {
            strStyleSheet= "";
        }
        else
        {
            strStyleSheet=file.readAll();
        }
        file.close();

        if(strStyleSheet.isEmpty())
        {
            return false;
        }
        window->setStyleSheet(strStyleSheet);
        return true;
    }

    //获取ICO图标
    static QIcon GetLocalFileIcon(QString strFile)
    {
        QFileIconProvider fIconProvider;
        return fIconProvider.icon(QFileInfo(strFile));
    }
};


class ListWidget : public QObject
{
public :
        ListWidget();~ListWidget();

static bool HasTheData(QListWidget* root,int role,const QString& strData)
{
    bool has=false;
    for(int i=0;i<root->count();i++)
    {
        QListWidgetItem* theItem=root->item(i);
        QString tmpData=theItem->data(role).toString();
        if(tmpData==strData)
        {
            has=true;
            break;
        }
    }
    return has;
}

static bool HasTheText(QListWidget* root,const QString& strText)
{
    bool has=false;
    for(int i=0;i<root->count();i++)
    {
        QListWidgetItem* theItem=root->item(i);
        QString tmpData=theItem->text();
        if(tmpData==strText)
        {
            has=true;
            break;
        }
    }
    return has;
}

static int CheckedItemCount(QListWidget* root)
{
    int count=0;
    for(int i=0;i<root->count();i++)
    {
        QListWidgetItem* item=root->item(i);
        if(item->checkState()==Qt::Checked)
        {
            count++;
        }
    }
    return count;
}

static int UncheckedItemCount(QListWidget* root)
{
    int checkedCount=CheckedItemCount(root);
    int totalCount=root->count();
    return totalCount-checkedCount;
}

};


class SettingMgr : public QObject
{
public:
    SettingMgr();~SettingMgr();

    static QString ReadSetting(QString strFile,QString bootName,QString key)
    {
        QSettings settings(strFile,bootName);
        return settings.value(key).toString();
    }

    static void WriteSetting(QString strFile,QString bootName,QString key, QString value)
    {
        QSettings settings(strFile,bootName);
        settings.setValue(key,value);
    }

};


class MyMessageBox : public QObject
{
public:
    MyMessageBox();~MyMessageBox();

    static void ChMessageOnlyOk(QString info)
    {
        QMessageBox msg;
        msg.setWindowTitle(tr("提示"));
        msg.setText(info);
        msg.setIcon(QMessageBox::Information);
        msg.addButton(tr("确定"),QMessageBox::ActionRole);
        msg.exec();
    }

    static void ChMessageOkCancel(QString info)
    {
        QMessageBox msg;
        msg.setWindowTitle(tr("提示"));
        msg.setText(info);
        msg.setIcon(QMessageBox::Information);
        msg.addButton(tr("确定"),QMessageBox::ActionRole);
        msg.addButton(tr("取消"),QMessageBox::ActionRole);
        msg.exec();
    }
};


