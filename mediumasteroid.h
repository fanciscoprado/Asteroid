#ifndef MEDIUMASTEROID_H
#define MEDIUMASTEROID_H

#include <QGraphicsPixmapItem>
#include <QObject>

/*************************************************************************************/
/********************** Represents a medium asteroid in the game ***********************/
/*************************************************************************************/

class MediumAsteroid : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    MediumAsteroid(bool asteroidDestroyed, int collisionXPos, int collisionYPos);
    int direction;

public slots:
    void moveAsteroid();

};

#endif // MEDIUMASTEROID_H
