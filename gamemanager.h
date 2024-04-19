#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <string>

using namespace std;

class GameManager
{
private:
    void performAction(string command);


public:
    GameManager();
    string actionChoice;
    bool setUpNewGame();
    void askForNextAction();
};

#endif // GAMEMANAGER_H
