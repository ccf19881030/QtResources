#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->regexEdit->setText("^\\s*(.*[/\\\\])?(.+\\.(mp3|wmv))\\s*$");
    ui->textEdit->setText("     c:\\music/jay\\0108.indianOldBird.mp3       ");
    ui->replaceEdit->setText("Unfinished");
    ui->resultEdit->setText("Unfinished");
    dealChanged();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_regexEdit_textEdited(const QString &)
{ dealChanged(); }

void MainWindow::on_textEdit_textChanged()
{ dealChanged(); }

#include <QRegularExpression>
#include <QRegularExpressionMatch>
void MainWindow::dealChanged()
{
    const QRegularExpression regex(ui->regexEdit->text());
    const QRegularExpressionMatch match = regex.match(ui->textEdit->toPlainText());

    QString list;
    for(int i = 0; i <= match.lastCapturedIndex(); i++) {
        list += QString("[%1]%2\n").arg(i).arg(match.captured(i));
    }

    ui->matchEdit->setText(list);
}

