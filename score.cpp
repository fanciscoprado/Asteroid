#include "score.h"
#include <QFont>

Score::Score(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    // initialize the score to 0
    score = 0;

    // draw the text
    setPlainText(QString("Score: ") + QString::number(score));
    setDefaultTextColor(Qt::white);
    setFont(QFont("times",16));
    setZValue(50);
}

void Score::increase()
{
    score++;
    setPlainText(QString("Score: ") + QString::number(score)); //updates text increases score
}

int Score::getScore()
{
    return score;
}
