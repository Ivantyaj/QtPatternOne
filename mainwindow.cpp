#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


//    connect(&bus, &Bus::signalTimeDepartureChanged, [=](const QTime &time){
//        ui->timeEditFrom->setTime(time);
//    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonRead_clicked()
{
    ui->tableViewBus->setModel(busTransport.readCSV());
}

void MainWindow::on_pushButtonFilter_clicked()
{
    QString dateFrom = ui->dateEditFrom->text();
    QString dateTo =ui->dateEditTo->text();
    QString timeFrom = ui->timeEditFrom->text();
    QString timeTo = ui->timeEditTo->text();

    Bus bus = busTransport.getBusList()->at(0);
    qDebug() << "arrival " << bus.getDateArrival();

    QList<Bus> busList;
    if(dateFrom != emptyDate && dateTo != emptyDate){
        busTransport.filter(busTransport.getBusList(),&busList,BusTransport::FilterType::Date, dateFrom, dateTo);
        auto model = BusTransport::getModel(&busList, busTransport.getHeaders());

        //auto model = BusTransport::getModel(busTransport.getBusList(), busTransport.getHeaders());

        ui->tableViewBus->setModel(model);
    }

}
