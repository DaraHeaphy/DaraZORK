#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Qstring>
#include <QObject>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void transmit_to_object(bool value);

public slots:
    void receive_from_object(QString output);
    void updateLocationImage(const QString& location_image);
    void update_gui_text(const QString& description);

private slots:

    void on_northButton_clicked();

    void on_southButton_clicked();

    void on_eastButton_clicked();

    void on_westButton_clicked();

    void on_areaDescriptionButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
