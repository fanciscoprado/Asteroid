#include "asteroid.h"

#include <QGraphicsScene>

// constructor
Asteroid::Asteroid()
{
    // display asteroid
    setPixmap(QPixmap(":/Images/Asteroids_BigRock.png"));

    // determine spawn position using RNG
    int windowSide = rand() % 2 + 1;    // determine from which side asteroid will spawn from
    int xPos, yPos;	// holds random numbers generated
    if (windowSide == 1)
    {
        xPos = rand() % 801; // determines x-axis spawn point (range of 0-800)
        yPos = -60;
    }
    else if (windowSide == 2)
    {
        xPos = -60;
        yPos = rand() % 601; // determines y-axis spawn point (range of 0-600)
    }
    setPos(xPos, yPos);
    setRotation(rand() % 360);  // set random rotation
    direction = rand() % 360;   // determines what direction the asteroid is headed
}

// move asteroid
void Asteroid::moveAsteroid()
{
    // move asteroid
    int xPos = x(), yPos = y();
    if (direction >= 0 && direction <= 90)
    {
        if (xPos + 1 > 800)
            setPos(-60, yPos);
        else if (yPos + 60 < 0)
            setPos(xPos, 600);
        else
            setPos(xPos + 1, yPos - 1);
    }
    else if (direction > 90 && direction < 180)
    {
        if (xPos + 1 > 800)
            setPos(-60, yPos);
        else if (yPos + 1 > 600)
            setPos(xPos, -60);
        else
            setPos(xPos + 1, yPos + 1);
    }
    else if (direction >= 180 && direction <= 270)
    {
        if (xPos + 60 < 0)
            setPos(800, yPos);
        else if (yPos + 1 > 600)
            setPos(xPos, -60);
        else
            setPos(xPos - 1, yPos + 1);
    }
    else if (direction > 270 && direction < 360)
    {
        if (xPos + 60 < 0)
            setPos(800, yPos);
        if (yPos + 60 < 0)
            setPos(xPos, 600);
        else
            setPos(xPos - 1, yPos - 1);
    }
}
