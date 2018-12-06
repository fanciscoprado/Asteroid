#include "lives.h"
#include <QFont>

Lives::Lives(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    // initialize the score to 0
    lives = 3;

    // draw the text
    setPlainText(QString("Lives: ") + QString::number(lives));
    setDefaultTextColor(Qt::green);
    setFont(QFont("times", 16));
    setZValue(50);
}

void Lives::decrease()
{
    lives--;
    setPlainText(QString("Lives: ") + QString::number(lives)); // updates text decreases lives
}

int Lives::getLives()
{
    return lives;
}

void Lives::increase()
{
    lives++;
}
