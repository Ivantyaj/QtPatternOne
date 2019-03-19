#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bus.h"
#include "busTransport.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonRead_clicked();

    void on_pushButtonFilter_clicked();

private:
    BusTransport busTransport;
    const QString emptyDate = "01.01.2000";

    Ui::MainWindow *ui;

    //Bus bus;
    Transport * transport;
};

#endif // MAINWINDOW_H
