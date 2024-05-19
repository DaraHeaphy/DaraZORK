 #ifndef GAME_H
#define GAME_H

#include <string>
#include <unordered_map>
#include <QString>
#include <QFile>
#include <QObject>
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
    string location_image;
    string actionText;
    unordered_map<string, Exit> exits;
    unordered_map<string, bool> objects;
};

class Game  : public QObject
{
    Q_OBJECT

public:
    explicit Game();

    unordered_map<string, Location>& getLocations();

    void setCurrentLocationToStart();
    void moveToLocation(const string& direction);
    void interactWithObject(const string& objectId);
    void printAreaDescription();
    void fillInMap(const unordered_map<string, Location>& locationsObj);
    void getCurrentLocationExits();

signals:
    void transmit_to_gui(QString output);
    void areaDescriptionChanged(const QString& description);
    void locationChanged(const QString& locationID);
    void locationImageChanged(const QString& imageUrl);
    void invalidDirection(const QString& actionText);

private slots:
    void receive_from_gui(bool value);

private:
    Location* currentLocation;
    QString JsonFilePath;
    QFile File;
    QJsonDocument Document;
    unordered_map<string, Location> locations;
    bool state;
};

extern Game game;

#endif // GAME_H
