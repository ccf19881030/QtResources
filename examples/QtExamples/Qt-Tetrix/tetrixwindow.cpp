#include "tetrixwindow.h"
#include "tetrixboard.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDebug>

TetrixWindow::TetrixWindow()
{
    board = new TetrixBoard();
    nextPieceLabel = new QLabel();
    nextPieceLabel->setFrameStyle(QFrame::NoFrame);
    nextPieceLabel->setAlignment(Qt::AlignCenter);
    nextPieceLabel->setFixedWidth(80);
    nextPieceLabel->setFixedHeight(80);
    board->setNextPieceLabel(nextPieceLabel);

    levelLCD = new QLCDNumber(5);
    levelLCD->setFixedWidth(80);
    levelLCD->setFrameStyle(QLCDNumber::NoFrame);
    levelLCD->setSegmentStyle(QLCDNumber::Flat);

    scoreLCD = new QLCDNumber(5);
    scoreLCD->setFixedWidth(80);
    scoreLCD->setFrameStyle(QLCDNumber::NoFrame);
    scoreLCD->setSegmentStyle(QLCDNumber::Flat);

    startButton = new QPushButton(tr("Start"));
    startButton->setFixedWidth(80);
    startButton->setFocusPolicy(Qt::NoFocus);
    pauseButton = new QPushButton(tr("Pause"));
    pauseButton->setFixedWidth(80);
    pauseButton->setFocusPolicy(Qt::NoFocus);

    QVBoxLayout *rightBox = new QVBoxLayout;
    rightBox->addWidget(createLabel(tr("Next")));
    rightBox->addWidget(nextPieceLabel);
    rightBox->addWidget(createLabel(tr("Level")));
    rightBox->addWidget(levelLCD);
    rightBox->addWidget(createLabel(tr("Score")));
    rightBox->addWidget(scoreLCD);
    rightBox->addWidget(startButton);
    rightBox->addWidget(pauseButton);
    rightBox->addStretch(1);

    connect(startButton,SIGNAL(clicked()),board,SLOT(start()));
    connect(pauseButton,SIGNAL(clicked()),board,SLOT(pause()));
    connect(board,SIGNAL(levelChanged(int)),levelLCD,SLOT(display(int)));
    connect(board,SIGNAL(scoreChanged(int)),scoreLCD,SLOT(display(int)));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(board);
    layout->addLayout(rightBox);

    setLayout(layout);
    setWindowTitle(tr("Tetrix"));
    setFixedSize(470, 624);
}


QLabel *TetrixWindow::createLabel(const QString &text){
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignCenter);
    return label;
}
