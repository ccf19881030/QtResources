#include "frmmain.h"
#include <QApplication>
#include "api/appinit.h"
#include "api/applog.h"
#include "api/myhelper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName(App::AppName);
    a.setApplicationVersion("1.0");
    a.setWindowIcon(QIcon(":/main.ico"));

    AppInit *init = new AppInit;
    init->Load();

    if (App::SaveLog) {
        AppLog *log = new AppLog;
        log->Load();
    }

    frmMain w;
    w.show();

    return a.exec();
}
