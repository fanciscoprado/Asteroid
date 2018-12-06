#include "mainwindow.h"
#include "scene.h"

#include <QBrush>
#include <QGraphicsView>
#include <QMenuBar>

/*************************************************************************************/
/*********************** Main application window for Asteroids ***********************/
/*************************************************************************************/

// constructor
MainWindow::MainWindow() : QMainWindow()
{
    // add drop down menu
    QMenu*  fileMenu = menuBar()->addMenu("&Menu");
    QMenu*  helpMenu = menuBar()->addMenu("&Help");

    // create menu options
    fileMenu->addAction("&New Game", this, SLOT(StartNew()));
    fileMenu->addAction("&Change Background", this, SLOT(changeBg()));
    fileMenu->addAction("&Quit", this, SLOT(close()));

    // create help menu
    helpMenu->addAction("&Up Arrow - accelerate", this, SLOT(dummy()));
    helpMenu->addAction("&Right Arrow - turn right", this, SLOT(dummy()));
    helpMenu->addAction("&Down Arrow - reverse accelerate", this, SLOT(dummy()));
    helpMenu->addAction("&Left Arrow - turn left", this, SLOT(dummy()));
    helpMenu->addAction("&S - change ship", this, SLOT(dummy()));
    helpMenu->addAction("&R - respawn, if you still have lives left", this, SLOT(dummy()));
    helpMenu->addAction("&P - pause game", this, SLOT(dummy()));

    // create a scene
    scene = new Scene();

    // add a view
    view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
    view->setFrameStyle(0);
    view->setFixedSize(800,600);
    view->show();
    setCentralWidget(view);
    scene->setSceneRect(0, 0, 800, 600);
    scene->setBackgroundBrush(QBrush(QImage(":/Images/bg5.png")));
    // set focus on scene (allows it to register keyboard input)
    view->setFocus();
}

// StartNew
void MainWindow::StartNew()
{
    // create a scene
    Scene* newScene = new Scene();

    //
    setCentralWidget(view);
    view->setScene(newScene);
    newScene->setSceneRect(0, 0, 800, 600);
    newScene->setBackgroundBrush(QBrush(QImage(":/Images/bg5.png")));
    // set focus on scene (allows it to register keyboard input)
    view->setFocus();
    // delete old scene
    delete scene;
    scene = newScene;
}

// change background
void MainWindow::changeBg()
{
    if (bgSwitched)
    {
        bgSwitched = false;
        scene->setBackgroundBrush(QBrush(QImage(":/Images/bg5.png")));
    }
    else
    {
        bgSwitched = true;
        scene->setBackgroundBrush(QBrush(QImage(":/Images/bg7.png")));
    }
}

// do nothing
void MainWindow::dummy()
{
    // Hi
}
