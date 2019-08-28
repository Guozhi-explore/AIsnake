#include "environment.h"

#include "unit.h"

environment::environment()
{
    createBrick();
}

/* create food,to avoid the new food location is coincidly the body of snake,use a function
    to seperate food with snake,using an array of virtualSnake*/
void environment::createFood(int index,QVector<Unit> virtualSnake)
{
    int randomx,randomy;
    bool overlapflag=false;               //judge new created food's position is overlaped or not
    while(true)
    {
        overlapflag=false;
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        randomx=qrand()%BOARDWIDTH;
        randomy=qrand()%BOARDHEIGHT;
        for(int j=0;j<virtualSnake.size();++j)
        {
            if(virtualSnake[j].getUnitX()==randomx&&virtualSnake[j].getUnitY()==randomy)
            {
                overlapflag=true;
            }
        }        for(int j=0;j<QVfood.size();++j)
        {
            if(j==index)
                continue;
            if(QVfood[j].getUnitY()==randomx&&QVfood[j].getUnitY()==randomy)
                overlapflag=true;                   //avoid new created food is overlaped with other food
        }
        for(int j=0;j<QVfoodbrick.size();++j)
        {
            if(QVfoodbrick[j].getUnitX()<=randomx&&QVfoodbrick[j].getUnitX()+BRICKWIDTH>=randomx&&QVfoodbrick[j].getUnitY()<=randomy&&QVfoodbrick[j].getUnitY()+BRICKHEIGHT>=randomy)
                overlapflag=true;
        }
        for(int i=0;i<QVbrick.size();++i)
        {
            if(QVbrick[i].getUnitX()==randomx&&QVbrick[i].getUnitY()==randomy)
            {
                overlapflag=true;
            }
        }
        if(overlapflag==false)
        {
            QVfood[index].setUnitX(randomx);
            QVfood[index].setUnitY(randomy);
            return;
        }                                     //circulate till the right position is created
    }
}

/* create brick as initial terrain*/
void environment::createBrick()
{
    int random;
    createBorder();
    for(int i=1;i<BOARDWIDTH-BRICKWIDTH;++i)
    {
        for(int j=1;j<BOARDHEIGHT-BRICKHEIGHT;++j)
        {
            if(i>BOARDWIDTH/3&&2*i<BOARDWIDTH*4/3&&j>BOARDHEIGHT/3&&2*j<BOARDHEIGHT*4/3)
                continue;
            qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
            random=rand()%200;
            if(random==0)
            {
                QVfoodbrick.append(Unit(i,j,3));
                for(int k=0;k<BRICKWIDTH;++k)
                {
                    for(int t=0;t<BRICKHEIGHT;++t)
                    {
                        if(rand()%3!=0)
                         QVbrick.append(Unit(i+k,j+t,3));
                    }
                }
            }
        }
    }
}

void environment::createBorder()
{
    for(int i=0;i<=BOARDWIDTH;++i)
    {
        QVbrick.append(Unit(i,0,3));
        QVbrick.append(Unit(i,BOARDHEIGHT,3));
    }
    for(int i=0;i<=BOARDHEIGHT;++i)
    {
        QVbrick.append(Unit(0,i,3));
        QVbrick.append(Unit(BOARDWIDTH,i,3));
    }
}

/*draw brick and food*/

void environment::drawSquare(QPainter &painter, int x, int y, int shape,int squarewidth,int squareheight)
{
    static const QRgb colorTable[8] = {
        0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
        0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00
    };

    QColor color = colorTable[int(shape)];
    painter.fillRect(x + 1, y + 1, squarewidth - 2, squareheight - 2,
                     color);

    painter.setPen(color.light());
    painter.drawLine(x, y + squareheight - 1, x, y);
    painter.drawLine(x, y, x + squarewidth - 1, y);

    painter.setPen(color.dark());
    painter.drawLine(x + 1, y + squareheight - 1,
                     x + squarewidth - 1, y + squareheight - 1);
    painter.drawLine(x + squarewidth - 1, y + squareheight - 1,
                     x + squarewidth - 1, y + 1);
}