#ifndef SCENE_H
#define SCENE_H

#include "asteroid.h"
#include "bullet.h"
#include "gameover.h"
#include "lives.h"
#include "mediumasteroid.h"
#include "ship.h"
#include "smallasteroid.h"
#include "score.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QList>
#include <QObject>
#include <string>
#include <typeinfo>

using namespace std;

/*************************************************************************************/
/******************** Scene representing the game *********************/
/*************************************************************************************/

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene();

    Asteroid* asteroid;
    Bullet* bullet;
    GameOver* gameover;
    Lives* lives;
    MediumAsteroid* mediumAsteroid;
    QList<QGraphicsItem *> objectList;
    QTimer* timer;
    Score* score; // pointer to score
    Ship* ship;
    SmallAsteroid* smallAsteroid;

    void keyPressEvent(QKeyEvent* event); // receive keyboard press events
    void keyReleaseEvent(QKeyEvent* event); // receive keyboard release events
    void spawnAsteroid(string size, int xSpawn, int ySpawn);
    void spawnBullet();
    void spawnShip();

    bool gamePaused = false;
    bool upKey = false, rightKey = false, downKey = false, leftKey = false, spaceKey = false;
    bool shipDestroyed; // keeps track of whether ship exists or not
    bool shipSwitched = false;
public slots:
    void updateScene();
    void detectCollisions();
};

#endif // SCENE_H
