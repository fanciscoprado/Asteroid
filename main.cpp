// Group 1 - Francisco, Jovani, Nathan, Zack
// player is given three lives, and can manually respawn
// scoring is implemented, backgrounds can be switched
// player ships can be switched, and a pause function is implemented
// controls can be found under help

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // create main event loop handler and parse command line arguments
    QApplication app(argc, argv);

    // create application main window & enter main event loop
    MainWindow window;
    window.setFixedSize(800,600);
    window.show();

    return app.exec();
}
