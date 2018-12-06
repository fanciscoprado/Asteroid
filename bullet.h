#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>

/*************************************************************************************/
/******************* Represents a bullet in the game ********************/
/*************************************************************************************/

class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet();
public slots:
    void moveBullet();
};

#endif  // BULLET_H
