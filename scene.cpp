#include "asteroid.h"
#include "bullet.h"
#include "mediumasteroid.h"
#include "scene.h"
#include "score.h"
#include "ship.h"
#include "smallasteroid.h"

#include <ctime>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QList>
#include <QTimer>
#include <string>
#include <typeinfo>

#include <QDebug>

// constructor
Scene::Scene()
{
    // create ship
    shipDestroyed = false;
    spawnShip();

    // create score
    score = new Score();

    // create lives counter
    lives = new Lives();

    // add score to scene
    addItem(score);

    // add lives to scene
    addItem(lives);
    lives->setPos(lives->x(), lives->y() + 25);

    // universal timer (spawns and moves asteroids, spawns and moves bullets, moves ship, detects collisions)
    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(updateScene()));
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(detectCollisions()));
    timer->start(30);
}

//
void Scene::detectCollisions()
{
    // detect collison between any object
    for (int i = 0; i < objectList.size(); ++i)
    {
        QList<QGraphicsItem*> collisionList = objectList[i]->collidingItems();
        if (collisionList.size() > 0)
        {
            for (int j = 0; j < collisionList.size(); ++j)
            {
                // if object 'j' is an asteroid, destroy object 'i' and object 'j', and spawn two medium asteroids
                if (typeid(*(collisionList[j])) == typeid(Asteroid))
                {
                    // if object 'i' is the ship, set flag and decrease lives
                    if (typeid(*(objectList[i])) == typeid(Ship))
                    {
                        shipDestroyed = true;
                        lives->decrease();
                    }

                    if(!(typeid(*(objectList[i])) == typeid(Asteroid)) && !(typeid(*(objectList[i])) == typeid(MediumAsteroid)) && !(typeid(*(objectList[i])) == typeid(SmallAsteroid)))
                    {
                        removeItem(objectList[i]);  // remove object 'i' from scene
                        delete objectList[i];   // delete object 'i' from memory
                        objectList.removeAt(i); // remove object 'i' from objectList

                        // spawn two medium asteroids
                        spawnAsteroid("medium", collisionList[j]->x(), collisionList[j]->y());
                        spawnAsteroid("medium", collisionList[j]->x(), collisionList[j]->y());

                        removeItem(collisionList[j]);  // remove object 'j' from scene
                        objectList.removeAt(objectList.indexOf(collisionList[j]));    // remove object 'j' from objectList
                        delete collisionList[j];  // delete object 'j' from memory

                        // increase score
                        score->increase();
                    }
                }

                // if object 'j' is a medium asteroid, destroy object 'i' and object 'j', and spawn two small asteroids
                else if (typeid(*(collisionList[j])) == typeid(MediumAsteroid))
                {
                    // if object 'i' is the ship, set flag and decrease lives
                    if (typeid(*(objectList[i])) == typeid(Ship))
                    {
                        shipDestroyed = true;
                        lives->decrease();
                    }

                    if(!(typeid(*(objectList[i])) == typeid(Asteroid)) && !(typeid(*(objectList[i])) == typeid(MediumAsteroid)) && !(typeid(*(objectList[i])) == typeid(SmallAsteroid)))
                    {
                        removeItem(objectList[i]);  // remove object 'i' from scene
                        delete objectList[i];   // delete object 'i' from memory
                        objectList.removeAt(i); // remove object 'i' from objectList

                        // spawn two small asteroids
                        spawnAsteroid("small", collisionList[j]->x(), collisionList[j]->y());
                        spawnAsteroid("small", collisionList[j]->x(), collisionList[j]->y());

                        removeItem(collisionList[j]);  // remove object 'j' from scene
                        objectList.removeAt(objectList.indexOf(collisionList[j]));    // remove object 'j' from objectList
                        delete collisionList[j];  // delete object 'j' from memory

                        // increase score
                        score->increase();
                    }
                }

                // if object 'j' is a small asteroid, destroy object 'i' and object 'j'
                else if (typeid(*(collisionList[j])) == typeid(SmallAsteroid))
                {
                    // if object 'i' is the ship, set flag and decrease lives
                    if (typeid(*(objectList[i])) == typeid(Ship))
                    {
                        shipDestroyed = true;
                        lives->decrease();
                    }

                    if(!(typeid(*(objectList[i])) == typeid(Asteroid)) && !(typeid(*(objectList[i])) == typeid(MediumAsteroid)) && !(typeid(*(objectList[i])) == typeid(SmallAsteroid)))
                    {
                        removeItem(objectList[i]);  // remove object 'i' from scene
                        delete objectList[i];   // delete object 'i' from memory
                        objectList.removeAt(i); // remove object 'i' from objectList

                        removeItem(collisionList[j]);  // remove object 'j' from scene
                        objectList.removeAt(objectList.indexOf(collisionList[j]));    // remove object 'j' from objectList
                        delete collisionList[j];  // delete object 'j' from memory

                        // increase score
                        score->increase();
                    }
                }

                // if object 'i' is a bullet that has gone offscreen, destroy it
                else if (typeid(*(objectList[i])) == typeid(Bullet))
                {
                    // deletes bullet once it goes offscreen
                    if (objectList[i]->pos().y() + 16 < 0 || objectList[i]->pos().y() + 16 > 600 || objectList[i]->pos().x() + 16 < 0 || objectList[i]->pos().x() + 16 > 800)
                    {
                        removeItem(objectList[i]);  // remove object 'i' from scene
                        delete objectList[i];   // delete object 'i' from memory
                        objectList.removeAt(i); // remove object 'i' from objectList
                    }
                }
            }
            collisionList.clear();
        }
    }
}

// detect key presses
void Scene::keyPressEvent(QKeyEvent *event)
{
    // detects "up" key press
    if (event->key() == Qt::Key_Up)
        upKey = true;

    // detects "right" key press
    if (event->key() == Qt::Key_Right)
        rightKey = true;

    // detects "down" key press
    if (event->key() == Qt::Key_Down)
        downKey = true;

    // detects "left" key press
    if (event->key() == Qt::Key_Left)
        leftKey = true;

    // detects "space" key press
    if (event->key() == Qt::Key_Space)
        spaceKey = true;

    // detects "r" key press
    if ((event->key() == Qt::Key_R) && shipDestroyed)
    {
        shipDestroyed = false;
        spawnShip();
    }

    //detects "p" key press
    if (event->key() == Qt::Key_P)
    {
        // if game is paused, unpause it, otherwise pause it
        if (gamePaused)
        {
            gamePaused = false;
            timer->start(30);
        }
        else
        {
            gamePaused = true;
            timer->stop();
        }
    }

    //detects "s" key press
    if (event->key() == Qt::Key_S)
    {
        if (!shipDestroyed)
        {
            // if ship is switched, unswitch it, otherwise switch it
            if (shipSwitched)
            {
                shipSwitched = false;
                ship->setPixmap(QPixmap(":/Images/spaceship1.png"));
            }
            else
            {
                shipSwitched = true;
                ship->setPixmap(QPixmap(":/Images/spaceship2.png"));
            }
        }
    }
}

// detect key releases
void Scene::keyReleaseEvent(QKeyEvent *event)
{
    // detects "up" key release
    if (event->key() == Qt::Key_Up)
        upKey = false;

    // detects "right" key release
    if (event->key() == Qt::Key_Right)
        rightKey = false;

    // detects "down" key release
    if (event->key() == Qt::Key_Down)
        downKey = false;

    // detects "left" key release
    if (event->key() == Qt::Key_Left)
        leftKey = false;

    // detects "space" key release
    if (event->key() == Qt::Key_Space)
    {
        spaceKey = false;
    }
}

// spawn asteroid
void Scene::spawnAsteroid(string size, int xSpawn, int ySpawn)
{
    if (size == "medium")
    {
        mediumAsteroid = new MediumAsteroid(true, xSpawn, ySpawn);
        objectList.append(mediumAsteroid);    // add mediumAsteroid to objectList
        addItem(mediumAsteroid); // add medium asteroid to scene
        // move asteroid
        connect(timer, SIGNAL(timeout()), mediumAsteroid, SLOT(moveAsteroid()));
    }
    else if (size == "small")
    {
        smallAsteroid = new SmallAsteroid(true, xSpawn, ySpawn);
        objectList.append(smallAsteroid);    // add smallAsteroid to objectList
        addItem(smallAsteroid); // add small asteroid to scene
        // move asteroid
        connect(timer, SIGNAL(timeout()), smallAsteroid, SLOT(moveAsteroid()));
    }
    else if (size == "random")
    {
        // create an asteroid randomly
        if (rand() % 100 <= 2) // only create an asteroid 2% of the time
        {
            int randomSize = rand() % 3 + 1;
            if (randomSize == 1)
            {
                asteroid = new Asteroid();
                objectList.append(asteroid);  // add asteroid to objectList
                addItem(asteroid);  // add asteroid to scene
                // move asteroid
                connect(timer, SIGNAL(timeout()), asteroid, SLOT(moveAsteroid()));
            }
            else if (randomSize == 2)
            {
                mediumAsteroid = new MediumAsteroid(true, xSpawn, ySpawn);
                objectList.append(mediumAsteroid);    // add mediumAsteroid to objectList
                addItem(mediumAsteroid); // add medium asteroid to scene
                // move asteroid
                connect(timer, SIGNAL(timeout()), mediumAsteroid, SLOT(moveAsteroid()));
            }
            else
            {
                smallAsteroid = new SmallAsteroid(false, 0, 0);
                objectList.append(smallAsteroid);    // add smallAsteroid to smallAsteroidList
                addItem(smallAsteroid); // add small asteroid to scene
                // move asteroid
                connect(timer, SIGNAL(timeout()), smallAsteroid, SLOT(moveAsteroid()));
            }
        }
    }
}

// spawn bullet
void Scene::spawnBullet()
{
    // create a bullet
    Bullet* bullet = new Bullet();  // creates bullet
    bullet->setRotation(ship->getCurrentAngle());
    bullet->setPos(ship->getXPos() + 25, ship->getYPos() + 25);
    objectList.append(bullet);  // add bullet to list
    addItem(bullet);    // adds bullet to scene
    // move bullet
    connect(timer, SIGNAL(timeout()), bullet, SLOT(moveBullet()));
}

// move ship
void Scene::updateScene()
{
    if (lives->getLives() == 0)
    {
        timer->stop();  // pause game
        gameover = new GameOver();
        addItem(gameover);  // add gameover to scene
    }

    // spawn asteroid
    spawnAsteroid("random", 0, 0);

    // move ship if it exists
    if (!shipDestroyed)
    {
        if (spaceKey)
        {
            ship->moveShip(upKey, rightKey, downKey, leftKey);
            spawnBullet();
            spaceKey = false;
        }
        else
            ship->moveShip(upKey, rightKey, downKey, leftKey);
    }
}

// spawn ship
void Scene::spawnShip()
{
    ship = new Ship();
    objectList.append(ship);    // add ship to list
    addItem(ship);  // add ship to scene
}
