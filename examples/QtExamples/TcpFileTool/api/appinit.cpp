#include "appinit.h"
#include "myhelper.h"

AppInit::AppInit(QObject *parent) : QObject(parent)
{
    mousePressed = false;
    if (App::UseStyle) {
        qApp->installEventFilter(this);
    }
}

bool AppInit::eventFilter(QObject *obj, QEvent *evt)
{
    QWidget *w = (QWidget *)obj;
    if (!w->property("CanMove").toBool()) {
        return QObject::eventFilter(obj, evt);
    }

    QMouseEvent *event = static_cast<QMouseEvent *>(evt);
    if (event->type() == QEvent::MouseButtonPress) {
        if (event->button() == Qt::LeftButton) {
            mousePressed = true;
            mousePoint = event->globalPos() - w->pos();
            return true;
        }
    } else if (event->type() == QEvent::MouseButtonRelease) {
        mousePressed = false;
        return true;
    } else if (event->type() == QEvent::MouseMove) {
        if (mousePressed && (event->buttons() && Qt::LeftButton)) {
            w->move(event->globalPos() - mousePoint);
            return true;
        }
    }

    return QObject::eventFilter(obj, evt);
}

void AppInit::Load()
{
    myHelper::SetUTF8Code();
    myHelper::SetChinese();

    App::AppPath = QApplication::applicationDirPath();
    App::DeskWidth = qApp->desktop()->availableGeometry().width();
    App::DeskHeight = qApp->desktop()->availableGeometry().height();
    App::ReadConfig();

    myHelper::SetFont();

    if (App::UseStyle) {
        myHelper::SetStyle(App::StyleName);
    }
}
