
#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "gamemanager.h"
#include <QFileInfo>

using namespace std;

bool fileExists(QString path) {
    QFileInfo check_file(path);
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setFixedSize(910, 520);
    w.show();

    GameManager gameManager;
    gameManager.setUpNewGame();

    return a.exec();
}




