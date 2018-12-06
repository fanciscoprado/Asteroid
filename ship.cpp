#include "ship.h"

#include <QGraphicsScene>

/*************************************************************************************/
/******************* Represents a ship in the game ********************/
/*************************************************************************************/

// constructor
Ship::Ship()
{
    // display ship
    setPixmap(QPixmap(":/Images/spaceship1.png"));
    setTransformOriginPoint(25, 25);
    setPos(400, 300);
}

// determine ship's current angle
int Ship::getCurrentAngle()
{
    return currentAngle;
}

// determine ship's position on x-axis
int Ship::getXPos()
{
    return x();
}

// determine ship's position on y-axis
int Ship::getYPos()
{
    return y();
}

// moves ship (used by timer)
void Ship::moveShip(bool up, bool right, bool down, bool left)
{
    // detect if ship has accelerated
    if (upPressed || downPressed)
    {
        setPos(x() + xVel, y() + yVel);
    }

    // determines what to do based on keys pressed
    if (up || (up && right) || (up && left))
        accelerate();

    else if (down || (down && right) || (down && left))
        reverse();

    else if (right)
        turnRight();

    else if (left)
        turnLeft();

    int xPos = x();
    int yPos = y();
    // wraps ship around x-axis
    if (xPos + 1 > 800)
        setPos(0, yPos);
    if (xPos - 1 < 0)
        setPos(800, yPos);
    // wraps ships around y-axis
    if (yPos + 1 > 600)
        setPos(xPos, 0);
    if (yPos - 1 < 0)
        setPos(xPos, 600);
}

// accelerate ship
void Ship::accelerate()
{
    // accelerate ship
    double changeInY = 0, changeInX = 0;
    upPressed = true;
    if (currentAngle >= 0 && currentAngle <= 90)
    {
        changeInX = 1 * (currentAngle / 90.0);
        changeInY = -(1 - changeInX);
    }
    else if (currentAngle > 90 && currentAngle < 180)
    {
        changeInX = 1 * ((180 - currentAngle) / 90.0);
        changeInY = 1 - changeInX;
    }
    else if (currentAngle >= 180 && currentAngle <= 270)
    {
        changeInX = -(1 * ((currentAngle - 180) / 90.0));
        changeInY = 1 + changeInX;
    }
    else if (currentAngle > 270 && currentAngle < 360)
    {
        changeInX = -(1 * ((360 - currentAngle) / 90.0));
        changeInY = -(1 + changeInX);
    }
    xVel += changeInX;
    yVel += changeInY;
}

// turn ship right
void Ship::turnRight()
{
    // turn ship right
    currentAngle = (currentAngle + 10);
    setRotation(currentAngle);
    if (currentAngle >= 360)
        currentAngle -= 360;
}

// reverse
void Ship::reverse()
{
    // move ship in direction opposite that of which it is facing
    downPressed = true;
    double changeInY = 0, changeInX = 0;
    if (currentAngle >= 0 && currentAngle <= 90)
    {
        changeInX= -(1 * (currentAngle / 90.0));
        changeInY= 1 + changeInX;
    }
    else if (currentAngle > 90 && currentAngle < 180)
    {
        changeInX= -(1 * ((180 - currentAngle) / 90.0));
        changeInY= -(1 + changeInX);
    }
    else if (currentAngle >= 180 && currentAngle <= 270)
    {
        changeInX= 1 * ((currentAngle - 180) / 90.0);
        changeInY= -(1 - changeInX);
    }
    else if (currentAngle > 270 && currentAngle < 360)
    {
        changeInX= 1 * ((360 - currentAngle) / 90.0);
        changeInY= 1 - changeInX;
    }
    xVel += changeInX;
    yVel += changeInY;
}

// turn ship left
void Ship::turnLeft()
{
    // turn ship left
    currentAngle = (currentAngle - 10);
    setRotation(currentAngle);
    if (currentAngle < 0)
        currentAngle += 360;
}
