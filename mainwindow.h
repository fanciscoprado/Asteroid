#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class Scene;

#include <QGraphicsView>
#include <QMainWindow>


/*************************************************************************************/
/*********************** Main application window for Asteroids ***********************/
/*************************************************************************************/


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();   // constructor
    Scene* scene;
    QGraphicsView* view;
    bool bgSwitched = false;

public slots:
    void StartNew();  // start new game
    void changeBg();    // change background
    void dummy();   // dummy function, does nothing
};

#endif  // MAINWINDOW_H
