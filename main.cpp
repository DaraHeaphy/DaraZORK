 #include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "game.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    cout << "\n" << endl;

    cout << "Welcome to DARAZORK!" << endl;

    while (true) {
        cout << "Do you wish to start a new game? [y/n]" << endl;
        char start_choice;
        cin >> start_choice;
        if (start_choice == 'y') {
            Location* currentLocation = new Location();
            Game game(currentLocation);
            game.setCurrentLocationToStart();
            cout << "Current Location: " << game.getCurrentLocationDescription() << endl;
            unordered_map<string, Location> data;
            game.fillInMap(data);
            game.printAreaDescription();
            break;
        }else if(start_choice == 'n'){
            cout << "Terminating App..." << endl;
            break;
        } else {
            cout << "I do not recognise that input, please try again." << endl;
        }
    }
    return a.exec();
}


