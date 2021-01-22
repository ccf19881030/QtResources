#include "projectlistwidget.h"

ProjectListWidget::ProjectListWidget(QWidget *parent)
    : QListWidget(parent)
{
    //允许拖放
        setAcceptDrops(true);
}

void ProjectListWidget::mousePressEvent(QMouseEvent *event)
{
    //获取鼠标按下时候的坐标
    if (event->button() == Qt::LeftButton)
        startPos = event->pos();
    QListWidget::mousePressEvent(event);
}

void ProjectListWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        int distance = (event->pos() - startPos).manhattanLength();
        //如果长度大于推荐的拖动起始距离，则认为是拖动(存在用户手抖的情况)
        if (distance >= QApplication::startDragDistance())
            performDrag();
    }
    QListWidget::mouseMoveEvent(event);
}

//有文件拖动到窗口上时，触发此dragEnterEvent事件
void ProjectListWidget::dragEnterEvent(QDragEnterEvent *event)
{
    //当为同一个应用程序的一部分时，event->source()返回启动这个拖动窗口部件的指针
    ProjectListWidget *source =
            qobject_cast<ProjectListWidget *>(event->source());
    if (source && source != this) {
        //确认是一个移动的操作
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

void ProjectListWidget::dragMoveEvent(QDragMoveEvent *event)
{
    ProjectListWidget *source =
            qobject_cast<ProjectListWidget *>(event->source());
    if (source && source != this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

void ProjectListWidget::dropEvent(QDropEvent *event)
{
    ProjectListWidget *source =
            qobject_cast<ProjectListWidget *>(event->source());
    if (source && source != this) {
        //得到数据并增加到列表中
        addItem(event->mimeData()->text());
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

void ProjectListWidget::performDrag()
{
    //当前被拖动的选项
    QListWidgetItem *item = currentItem();
    if (item) {
        QMimeData *mimeData = new QMimeData;
        mimeData->setText(item->text());

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        drag->setPixmap(QPixmap(":/images/person.png"));
        //进行拖动操作
        if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
            delete item;
    }
}
