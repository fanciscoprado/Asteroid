#ifndef SMALLASTEROID_H
#define SMALLASTEROID_H

#include <QGraphicsPixmapItem>
#include <QObject>

/*************************************************************************************/
/********************** Represents an small asteroid in the game ***********************/
/*************************************************************************************/

class SmallAsteroid : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    SmallAsteroid(bool asteroidDestroyed, int collisionXPos, int collisionYPos);
    int direction;
public slots:
    void moveAsteroid();

};

#endif  // SMALLASTEROID_H
