#define QT_NO_OPENGL
#ifndef SINGLESNAKEBOARD_H
#define SINGLESNAKEBOARD_H

#include"snakeboard.h"
#include <QBasicTimer>
#include <QFrame>
#include <QPointer>
#include "snake.h"
#include"environment.h"
#include"shareinfo.h"

class singlesnakeboard:public snakeboard
{
    Q_OBJECT

public:
    singlesnakeboard(QWidget *parent=0);

public slots:
    void start();

signals:
    void score1Changed(int score);
    void level1Changed(int level);
    void hidetimesChanged(int hidetimes);

private:

    int level1;
    int score1;
    int remainhidetimes=0;   //可以隐身的次数
    int hideleft=0;         //这次隐身剩下的时间

    environment environ;
    Snake *snake;

    QBasicTimer timer;

    int timeoutTime()
    {
        return 400/(1+level1);
    }

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void paintEvent(QPaintEvent *) override;

};

#endif // SINGLESNAKEBOARD_H
