#ifndef ASTEROID_H
#define ASTEROID_H

#include <QGraphicsPixmapItem>
#include <QObject>

/*************************************************************************************/
/********************** Represents an asteroid in the game ***********************/
/*************************************************************************************/

class Asteroid : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Asteroid();
    int direction;
    /*double changeInY = 0, changeInX = 0;
    int lastWrapAround;*/
public slots:
    void moveAsteroid();

};

#endif  // ASTEROID_H
