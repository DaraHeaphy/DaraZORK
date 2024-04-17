#ifndef GAME_H
#define GAME_H

#include <string>
#include <unordered_map>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QIODevice>
#include <QDebug>

using namespace std;

struct Location {
    string description_of_area;
    string description;
    string actionText;
    unordered_map<string, Location*> exits;
    unordered_map<string, bool> objects;
};

class Game {
private:
    Location* currentLocation;
    QString JsonFilePath;
    QFile File;
    QJsonDocument Document;
    unordered_map<string, Location> locations;

public:

    Game(Location* startLocation);

    void setCurrentLocationToStart();
    void moveToLocation(const string& exit);
    void interactWithObject(const string& objectId);
    void printAreaDescription();
    void fillInMap(const unordered_map<string, Location>& data);
    string getCurrentLocationDescription();
    void getCurrentLocationExits();



};

#endif // GAME_H
