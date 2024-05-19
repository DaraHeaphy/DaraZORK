#include <iostream>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QIODevice>
#include <QDebug>
#include <QObject>
#include <unordered_map>
#include "game.h"

using namespace std;

Game::Game() : currentLocation(nullptr), JsonFilePath(":/Locations.json"), File(JsonFilePath) {

    if (!File.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open file:" << JsonFilePath;
        return;
    }

    QByteArray Bytes = File.readAll();
    File.close();

    QJsonParseError JsonError;
    Document = QJsonDocument::fromJson(Bytes, &JsonError);
    if (JsonError.error != QJsonParseError::NoError) {
        qDebug() << "Error In Json Data :" << JsonError.errorString();
        return;
    }

    if (!Document.isObject()) {
        qDebug() << "Invalid JSON format";
        return;
    }

    QJsonObject locationsObj = Document.object()["locations"].toObject();

    for(const QString& locationKey : locationsObj.keys()) {
        QJsonObject locationObj = locationsObj.find(locationKey).value().toObject();

        Location location;
        location.description_of_area = locationObj.value("description-of-area").toString().toStdString();
        location.location_image = locationObj.value("location-image").toString().toStdString();

        QJsonObject exitsObj = locationObj["exits"].toObject();
        if(!exitsObj.isEmpty()) {
            for (const QString& exitKey : exitsObj.keys()) {
                QJsonObject exitDetailsObj = exitsObj[exitKey].toObject();
                if(exitDetailsObj.isEmpty()) {
                    continue;
                }
                Exit exit;
                if(exitDetailsObj.contains("id") && exitDetailsObj.find("id").value() != NULL){
                    exit.id = exitDetailsObj.find("id").value().toString().toStdString();
                }
                if(exitDetailsObj.contains("description") && exitDetailsObj.find("description").value() != NULL){
                    exit.description = exitDetailsObj.find("description").value().toString().toStdString();
                }
                if(exitDetailsObj.contains("accessible") && exitDetailsObj.find("accessible").value() != NULL){
                    exit.accessible = exitDetailsObj.find("accessible").value().toBool();
                }
                if(exitDetailsObj.contains("actionText") && exitDetailsObj.find("actionText").value() != NULL){
                    exit.actionText = exitDetailsObj.find("actionText").value().toString().toStdString();
                }
                location.exits[exitKey.toStdString()] = exit;
            }
        }
        locations[locationKey.toStdString()] = location;
    }

    if(locations.find("start") != locations.end()) {
        currentLocation = &locations.find("start")->second;
    } else {
        throw runtime_error("No location with key 'start' found");
    }
}

unordered_map<string, Location>& Game::getLocations(){
    return this->locations;
}

void Game::fillInMap(const unordered_map<string, Location>& locationsObj) {
    locations = locationsObj;
}

void Game::setCurrentLocationToStart() {
    if (locations.find("start") != locations.end()) {
        currentLocation = &locations["start"];
        printAreaDescription();
        emit locationImageChanged(QString::fromStdString(currentLocation->location_image));
    } else {
        cout << "Start location not found." << endl;
    }
}

void Game::moveToLocation(const string& direction) {
    QString actionText;
    if (currentLocation->exits.find(direction) != currentLocation->exits.end()) {
        Exit exit = currentLocation->exits.find(direction)->second;
        if (!exit.accessible) {
            actionText += exit.actionText;
            emit invalidDirection(actionText);
            return;
        }
        if (locations.find(exit.id) != locations.end()) {
            currentLocation = &locations.at(exit.id);
            printAreaDescription();
            emit locationChanged(QString::fromStdString(exit.id));
            emit locationImageChanged(QString::fromStdString(currentLocation->location_image));
        }
    } else {
        emit invalidDirection(actionText);
    }
}

void Game::interactWithObject(const string& objectId) {
    if (currentLocation->objects.find(objectId) != currentLocation->objects.end()) {
        if (currentLocation->objects[objectId]) {
            cout << "Interacted with object: " << objectId << endl;
        } else {
            cout << "Object not accessible at this location!" << endl;
        }
    } else {
        cout << "Object not found!" << endl;
    }
};

void Game::getCurrentLocationExits() {
    cout << "Exits: ";
    for (const auto& exit : currentLocation->exits) {
        cout << exit.first << ", ";
    }
    cout << endl;
}

void Game::printAreaDescription() {
    QString output;
    output += currentLocation->description_of_area + "\n";
    for (const auto& exit : currentLocation->exits) {
        output += exit.second.description + "\n";
    }
    emit areaDescriptionChanged(output);
}

void Game::receive_from_gui(bool value)
{
    state = value;

    QString stateString = state ? "true" : "false";

    emit transmit_to_gui(stateString);
}
