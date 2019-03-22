#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
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

    void on_pushButtonFavorite_clicked();

    void on_pushButtonClearFavorite_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    void reloadChart();

private:
    const QString emptyDate = "01.01.2000";
    const QString emptyTime = "00:00";

    Ui::MainWindow *ui;
    QChartView *chartView;

    TransportFactory * transportFactory;
};

#endif // MAINWINDOW_H
