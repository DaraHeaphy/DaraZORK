QT       += core gui
QT += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

CONFIG += console

TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    directions.cpp \
    game.cpp \
    gamemanager.cpp \
    locations.cpp \
    main.cpp \
    mainwindow.cpp \
    movement.cpp

HEADERS += \
    directions.h \
    game.h \
    gamemanager.h \
    locations.h \
    mainwindow.h \
    movement.h

FORMS += \
    mainwindow.ui
