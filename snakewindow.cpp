#define QT_NO_OPENGL
#include <QtWidgets>
#include "snakewindow.h"
#include "snakeborder.h"

SnakeWindow::SnakeWindow()
{
    board=new SnakeBorder;
    scoreLcd=new QLCDNumber(5);   //specify the max length of the number
    scoreLcd->setSegmentStyle(QLCDNumber::Filled);
    levelLcd=new QLCDNumber(5);
    levelLcd->setSegmentStyle(QLCDNumber::Filled);

    startButton = new QPushButton(tr("&Start"));
    startButton->setFocusPolicy(Qt::NoFocus);
    quitButton = new QPushButton(tr("&Quit"));
    quitButton->setFocusPolicy(Qt::NoFocus);
    pauseButton = new QPushButton(tr("&Pause"));
    pauseButton->setFocusPolicy(Qt::NoFocus);

    connect(startButton, &QPushButton::clicked, board, &SnakeBorder::start);
    connect(quitButton , &QPushButton::clicked, qApp, &QApplication::quit);
    connect(pauseButton, &QPushButton::clicked, board, &SnakeBorder::pause);

#if __cplusplus >= 201402L
    connect(board, &SnakeBoard::scoreChanged,
            scoreLcd, qOverload<int>(&QLCDNumber::display));
    connect(board, &SnakeBoard::levelChanged,
            levelLcd, qOverload<int>(&QLCDNumber::display));
#else
    connect(board, &SnakeBorder::scoreChanged,
            scoreLcd, QOverload<int>::of(&QLCDNumber::display));
    connect(board, &SnakeBorder::levelChanged,
            levelLcd, QOverload<int>::of(&QLCDNumber::display));

#endif

    QGridLayout *layout=new QGridLayout;
    //layout->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    layout->addWidget(board, 0, 0,9,10);

    layout->addWidget(createLabel(tr("LEVEL")), 0, 10,1,1);
    layout->addWidget(levelLcd, 1, 10,1,1);
    layout->addWidget(createLabel(tr("SCORE")), 2, 10,1,1);
    layout->addWidget(scoreLcd, 3, 10,1,1);

    layout->addWidget(startButton, 5, 10,1,1);
    layout->addWidget(quitButton, 6, 10,1,1);
    layout->addWidget(pauseButton, 7, 10,1,1);
    layout->setMargin(0);

    setLayout(layout);
    setWindowTitle(tr("QSnake"));
    resize(550,370);
}

QLabel *SnakeWindow::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return label;
}
