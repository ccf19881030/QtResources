#include "createshortcut.h"

createShortcut::createShortcut(QWidget *parent)
    : QDialog(parent)
{
    shortcutLabel=new QLabel;
    shortcutLabel->setText(tr("指定快捷方式名"));
    shortcutEdit=new QLineEdit;
    shortcutEdit->setText(tr(""));
    destDirLabel=new QLabel;
    destDirLabel->setText(tr("指定目录"));
    destDirEdit=new QLineEdit;
    destDirEdit->setText(tr("D:\\Win+R"));
    showTypeLabel=new QLabel;
    showTypeLabel->setText(tr("显示方式"));
    showTypeCombo=new QComboBox;
    showTypeCombo->addItem(tr("SW_SHOWNORMAL"));
    showTypeCombo->addItem(tr("SW_SHOWMINNOACTIVE"));
    showTypeCombo->addItem(tr("SW_SHOWMAXIMIZED"));
    descLabel=new QLabel;
    descLabel->setText(tr("描述"));
    descEdit=new QLineEdit;
    descEdit->setText(tr(""));
    okBtn=new QPushButton;
    okBtn->setText(tr("确定"));
    connect(okBtn,SIGNAL(clicked()), this, SLOT(onOkBtn()));
    quitBtn=new QPushButton;
    quitBtn->setText(tr("取消"));
    connect(quitBtn,SIGNAL(clicked()), this, SLOT(onQuitBtn()));
    layout=new QGridLayout;
    layout->addWidget(shortcutLabel,0,0);
    layout->addWidget(shortcutEdit,0,1);
    layout->addWidget(destDirLabel,1,0);
    layout->addWidget(destDirEdit,1,1);
    layout->addWidget(showTypeLabel,2,0);
    layout->addWidget(showTypeCombo,2,1);
    layout->addWidget(descLabel,3,0);
    layout->addWidget(descEdit,3,1);
    layout->addWidget(okBtn,4,0);
    layout->addWidget(quitBtn,4,1);

    this->setLayout(layout);

}

createShortcut::~createShortcut(){
}

void createShortcut::onQuitBtn(){
    this->close();
}

void createShortcut::onOkBtn(){
    //获得命令行参数
    int argc=0;
    LPWSTR *argv=::CommandLineToArgvW(::GetCommandLineW(),&argc);

    char *destDirCH;
    QByteArray destDirArray = destDirEdit->text().toLatin1();
    destDirCH=destDirArray.data();
    char *shortcutCH;
    QByteArray shortcutArray = shortcutEdit->text().toLatin1();
    shortcutCH=shortcutArray.data();
    char *descCH;
    QByteArray descArray=descEdit->text().toLatin1();
    descCH=descArray.data();

    HRESULT hr = CoInitialize(NULL); //初始化COM
    if(FAILED(hr)){
        QMessageBox msg1;
        msg1.setText("初始化COM失败！");
        msg1.exec();
    }
    if(onCreateShortcut(QString::fromWCharArray(argv[1]).toStdString().c_str(), "D:\\Win+R", NULL, NULL, 0,NULL, SW_SHOWNORMAL)) {
        this->close();
    } else {
        QMessageBox msg2;
        msg2.setText("创建快捷方式失败！");
        msg2.exec();
    }
}

BOOL createShortcut::onCreateShortcut(LPCSTR lpszFileName, LPCSTR lpszLnkFileDir, LPCSTR lpszLnkFileName, LPCSTR lpszWorkDir, WORD wHotkey, LPCWSTR lpszDescription, int iShowCmd){
    /*
        函数功能：对指定文件在指定的目录下创建其快捷方式
        函数参数：
        lpszFileName    指定文件，为NULL表示当前进程的EXE文件。
        lpszLnkFileDir  指定目录，不能为NULL。
        lpszLnkFileName 快捷方式名称，为NULL表示EXE文件名
        lpszWorkDir     工作目录，一般设置为NULL
        wHotkey         为0表示不设置快捷键
        pszDescription  备注
        iShowCmd        运行方式，默认为常规窗口
        */
        IShellLink *pLink=NULL;  //指向接口实例的指针
        IPersistFile *ppf=NULL;
        char szBuffer[MAX_PATH];
        WCHAR wsz[MAX_PATH];

        if(lpszLnkFileDir == NULL) {
            cout << "指定快捷方式生成的目录为空！";
            return FALSE;
        }

        //通过调用实例的QueryInterface()方法我们又创建了一个COM接口的实例
        //不过这个实例隶属于原来的pLink实例
        HRESULT hRet = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&pLink);

        if(FAILED(hRet)) {
            cout << "创建IShellLink实例失败";
            return FALSE;
        }

        hRet = pLink->QueryInterface(IID_IPersistFile, (void**)&ppf);   //从IShellLink对象中获取IPersistFile接口

        if(FAILED(hRet)) {
            pLink->Release();
            cout << "获取IPersistFile接口失败";
            return FALSE;
        }

        //创建之后就可以对pLink设置目标，快捷键，备注等
        //设置完后再用ppf创建快捷方式文件就可以了
        //最后要记得释放资源

        //_pgmptr表示当前可执行程序的全路径
        if(lpszFileName == NULL) {
            MultiByteToWideChar(CP_ACP, 0, _pgmptr, -1, wsz, MAX_PATH); //使用MultiByteToWideChar()函数转换为Unicode
            pLink->SetPath(wsz);
        } else {
            MultiByteToWideChar(CP_ACP, 0, lpszFileName, -1, wsz, MAX_PATH);
            pLink->SetPath(wsz);
        }

        if(lpszWorkDir != NULL) {
            MultiByteToWideChar(CP_ACP, 0, lpszWorkDir, -1, wsz, MAX_PATH);
            pLink->SetPath(wsz);
        }

        if(wHotkey != 0) {
            pLink->SetHotkey(wHotkey);
        }

        pLink->SetShowCmd(iShowCmd);    //Sets the show command for a Shell link object. The show command sets the initial show state of the window.
        pLink->SetDescription(lpszDescription);
        pLink->SetIconLocation(TEXT("c:\\windows\\explorer.exe"), 20);

        //获取可执行程序路径及盘符、目录、文件名、扩展名
        char   path_buffer[_MAX_PATH];
        char   drive[_MAX_DRIVE];
        char   dir[_MAX_DIR];
        char   fname[_MAX_FNAME];
        char   ext[_MAX_EXT];
        _splitpath(_pgmptr, drive, dir, fname, ext);

        if(lpszLnkFileName != NULL) {
            sprintf(szBuffer, "%s\\%s", lpszLnkFileDir, lpszLnkFileName);
        } else {
            sprintf(szBuffer, "%s\\%s%s", lpszLnkFileDir, fname, ".lnk");
        }

        MultiByteToWideChar(CP_ACP, 0, szBuffer, -1, wsz, MAX_PATH);
        hRet = ppf->Save(wsz, TRUE);    //实际保存到wsz指定的位置
        ppf->Release();                 //释放IShellLink对象
        pLink->Release();               //释放IShellLink对象
        return SUCCEEDED(hRet);
}
