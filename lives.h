#ifndef LIVES_H
#define LIVES_H

#include <QGraphicsTextItem>

class Lives: public QGraphicsTextItem
{
public:

    Lives(QGraphicsItem * parent =0);
    void decrease();
    int getLives();
    void increase();
private:
    int lives;
};

#endif // LIVES_H
