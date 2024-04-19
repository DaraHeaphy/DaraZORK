#include "gamemanager.h"
#include "game.h"
#include <iostream>

using namespace std;

GameManager::GameManager() {}

bool GameManager::setUpNewGame() {
    cout << "Do you wish to start a new game? [y/n]" << endl;
    char start_choice;
    cin >> start_choice;
    if (start_choice == 'y') {
        Game game;
        game.printAreaDescription();
        return true;
    }else if(start_choice == 'n'){
        cout << "Terminating App..." << endl;
        return false;
    } else {
        cout << "I do not recognise that input, please try again." << endl;
        return false;
    }
}

void GameManager::performAction(string command) { //make go north/south/east/west functions
    cout << "Command Received: " << command << endl;
}


void GameManager::askForNextAction() {
    string actionChoice;
    cin >> actionChoice;
    performAction(actionChoice); //*create isValidActionChoice function performAction function*
}



