 #include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "gamemanager.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;
    // w.show();

    cout << "\n" << endl;
    cout << "Welcome to DARAZORK!" << endl;

    GameManager gameManager;

    string gameState = "start";

    while (true) {
        if(gameState == "start") {
            bool setUpStatus = gameManager.setUpNewGame();
            if(setUpStatus == true) {
                gameState == "In Progress";
            }
            break;
        }
    }

    return a.exec();
}




