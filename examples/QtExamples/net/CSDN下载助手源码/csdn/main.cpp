#include "cmainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include "clogindialog.h"
#include "cgetintegral.h"
#include "chelp.h"
#include "log_sys/log_sys.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 注册自定义消息回调函数   如果需要弄文件日志系统  就调用它

  //  qInstallMsgHandler(myMsgHandler);

    #if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    #endif

    CLoginDialog loginDialog;
    CMainWindow w;
    if (1 ==loginDialog.exec()) {

        w.init(); // 这样做，是为了更好的获取用户名和cookie
        w.show();  
    } else {

        exit(0);
    }

    return a.exec();
}
