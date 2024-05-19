#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <QObject>

using namespace std;

class GameManager : public QObject
{
    Q_OBJECT

public:
     GameManager();
    bool setUpNewGame();

private:
    string output;
};

#endif // GAMEMANAGER_H
