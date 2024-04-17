#include <iostream>
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QIODevice>
#include <QDebug>
#include <unordered_map>
#include "game.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

Game::Game(Location* startLocation) : currentLocation(nullptr), JsonFilePath("Locations.json"), File(JsonFilePath) {
    if (!startLocation) {
        qDebug() << "Error: Start location is null";
        return;
    }
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

    if (locationsObj.contains("start")) {
        QJsonObject startLocationObj = locationsObj["start"].toObject();

        Location startLocation;
        startLocation.description = startLocationObj.value("description").toString().toStdString();
        startLocation.description_of_area = startLocationObj.value("description-of-area").toString().toStdString();

        QJsonObject startExitsObj = startLocationObj["exits"].toObject();
        for (const QString& exitKey : startExitsObj.keys()) {
            QJsonObject exitDetailsObj = startExitsObj[exitKey].toObject();
            if (exitDetailsObj.contains("id")) {
                string exitId = exitDetailsObj["id"].toString().toStdString();
                if (locations.find(exitId) != locations.end()) {
                    startLocation.exits[exitKey.toStdString()] = &locations[exitId];
                } else {
                    qDebug() << "Exit location not found for exit:" << exitKey;
                }
            }
        }

        currentLocation = &startLocation;
    } else {
        qDebug() << "Start location not found in JSON data.";
    }

    for (const QString &locationKey : locationsObj.keys()) {
        QJsonObject locationObj = locationsObj[locationKey].toObject();

        Location loc;
        loc.description = locationObj.value("description").toString().toStdString();
        loc.description_of_area = locationObj.value("description-of-area").toString().toStdString();

        QJsonObject exitsObj = locationObj["exits"].toObject();
        for (const QString &exitKey : exitsObj.keys()) {
            QJsonObject exitDetailsObj = exitsObj[exitKey].toObject();
            if (exitDetailsObj.contains("id")) {
                Location* exitLocation = &locations[exitDetailsObj["id"].toString().toStdString()];
                if (exitLocation) {
                    loc.exits[exitKey.toStdString()] = exitLocation;
                }
            }
        }
        locations[locationKey.toStdString()] = loc;
    }




    QString fileName("Locations.json");

    qDebug() << Q_FUNC_INFO << "Reading from file: " << fileName;

    QFile jsonFile;
    jsonFile.setFileName(fileName);

    if(!jsonFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << Q_FUNC_INFO << "Failed to open file";
    }
    else
    {
        QJsonDocument jsonDoc;
        QString jsonText = jsonFile.readAll();
        jsonFile.close();
        qDebug() << Q_FUNC_INFO << "File contents" << jsonText;
        QJsonParseError error;
        jsonDoc.fromJson(jsonText.toLocal8Bit(), &error);

        if(error.error == QJsonParseError::NoError)
        {
            QVariant variant = jsonDoc.object().toVariantMap();

            unordered_map<string, Location> data = variant.value<unordered_map<string, Location>>();

            fillInMap(data);
        }
        else
        {
            qWarning() << Q_FUNC_INFO << "JSON Parse Error: " << error.errorString();
        }
    }

}

void Game::fillInMap(const unordered_map<string, Location>& data) {
    locations = data;
}

void Game::setCurrentLocationToStart() {
    if (locations.find("start") != locations.end()) {
        currentLocation = &locations["start"];
        cout << "Current location set to start." << endl;
    } else {
        cout << "Start location not found." << endl;
    }
}

void Game::moveToLocation(const string& exit) {
    if (currentLocation->exits.find(exit) != currentLocation->exits.end()) {
        currentLocation = currentLocation->exits[exit];
        printAreaDescription();
    } else {
        cout << "Cannot move in that direction!" << endl;
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
}

string Game::getCurrentLocationDescription() {
    if (currentLocation != nullptr) {
        return currentLocation->description;
    } else {
        return "No current location set.";
    }
}

void Game::getCurrentLocationExits() {
    cout << "Exits: ";
    for (const auto& exit : currentLocation->exits) {
        cout << exit.first << ", ";
    }
    cout << endl;
}

void Game::printAreaDescription() {
    cout << currentLocation->description_of_area << endl;
    cout << "Exits:" << endl;
    cout << "Number of exits: " << currentLocation->exits.size() << endl;
    for (const auto& exit : currentLocation->exits) {
        if (exit.second != nullptr && !exit.second->description.empty()) {
            cout << "  " << exit.first << ": " << exit.second->description << endl;
            cout << "    Action Text: " << exit.second->actionText << endl; // Corrected
        } else {
            cout << "  " << exit.first << ": (No exit description)" << endl;
        }
    }
}
