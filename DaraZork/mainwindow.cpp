#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QPlainTextEdit>
#include <Qstring>
#include <QTextStream>
#include <QObject>
#include "movement.h"
#include "game.h"

using namespace std;

Movement movement;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&game, &Game::areaDescriptionChanged, this, &MainWindow::update_gui_text);
    connect(&game, &Game::invalidDirection, this, &MainWindow::update_gui_text);
    connect(&game, &Game::locationImageChanged, this, &MainWindow::updateLocationImage);


    QPlainTextEdit gameText;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_gui_text(const QString& description)
{
    qApp->processEvents();
    ui->textEdit->setText(description);
    ui->textEdit->update();
}

void MainWindow::receive_from_object(QString output)
{
    if (!output.isEmpty())
    {
        ui->textEdit->setText("true");
    }
    else
    {
        ui->textEdit->setText("false");
    }
}

void MainWindow::updateLocationImage(const QString& location_image) {
    QPixmap image(location_image);

    QSize size = ui->locationLabel->size();
    QPixmap scaledImage = image.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    ui->locationLabel->setPixmap(image);
}

void MainWindow::on_northButton_clicked()
{
    movement.goNorth();
}

void MainWindow::on_southButton_clicked()
{
    movement.goSouth();
}

void MainWindow::on_eastButton_clicked()
{
    movement.goEast();
}

void MainWindow::on_westButton_clicked()
{
    movement.goWest();
}


void MainWindow::on_areaDescriptionButton_clicked()
{
    game.printAreaDescription();
}

