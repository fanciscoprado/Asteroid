#ifndef SHIP_H
#define SHIP_H

#include <QGraphicsPixmapItem>
#include <QObject>

/*************************************************************************************/
/******************* Represents a ship in the game ********************/
/*************************************************************************************/

class Ship : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Ship();   // constructor

    int getCurrentAngle();
    int getXPos();
    int getYPos();

    void accelerate();
    void turnRight();
    void reverse();
    void turnLeft();

    double xVel = 0, yVel = 0;  // holds ship's current velocity on x and y axis
    int xPos, yPos;
    int currentAngle = 0;   // holds ship's current angle (it's 0 degrees when facing straight up)
    bool upPressed = false, downPressed = false; // keeps track of whether up or down keys have been pressed (whether ship is moving)
public slots:
    void moveShip(bool up, bool right, bool down, bool left);
};

#endif  // SHIP_H
