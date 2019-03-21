#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "busTransport.h"
#include "traintransport.h"
#include "transportfactory.h"


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
    void on_pushButtonClosest_clicked();

private:
    const QString emptyDate = "01.01.2000";
    const QString emptyTime = "00:00";

    Ui::MainWindow *ui;

    //Bus bus;
    TransportFactory * transportFactory;
};

#endif // MAINWINDOW_H
