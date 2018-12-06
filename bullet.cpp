#include "bullet.h"

#include <QGraphicsScene>

// constructor
Bullet::Bullet()
{
    // display bullet
    setPixmap(QPixmap(":/Images/blue bullet.png"));
}

// move bullet
void Bullet::moveBullet()
{
    // move bullet
    double changeInY = 0, changeInX = 0;
    int direction = rotation();
    if (direction >= 0 && direction <= 90)
    {
        changeInX= 5 * (direction / 90.0);
        changeInY= -(5 - changeInX);
    }
    else if (direction > 90 && direction < 180)
    {
        changeInX= 5 * ((180 - direction) / 90.0);
        changeInY= 5 - changeInX;
    }
    else if (direction >= 180 && direction <= 270)
    {
        changeInX= -(5 * ((direction - 180) / 90.0));
        changeInY= 5 + changeInX;
    }
    else if (direction > 270 && direction < 360)
    {
        changeInX= -(5 * ((360 - direction) / 90.0));
        changeInY= -(5 + changeInX);
    }

    setPos(x() + changeInX, y() + changeInY);
}
