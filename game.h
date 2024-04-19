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

struct Exit {
    string description;
    string actionText;
    string id;
    bool accessible;
};

struct Location {
    string description_of_area;
    string actionText;
    unordered_map<string, Exit> exits;
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
    Game();

    unordered_map<string, Location>& getLocations();

    void setCurrentLocationToStart();
    void moveToLocation(const string& direction);
    void interactWithObject(const string& objectId);
    void printAreaDescription();
    void fillInMap(const unordered_map<string, Location>& locationsObj);
    string getCurrentLocationDescription();
    void getCurrentLocationExits();



};

#endif // GAME_H
