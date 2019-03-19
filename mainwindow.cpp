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
    if(ui->comboBoxFile->currentText() == "CSV")
        ui->tableViewBus->setModel(busTransport.readCSV());
    if(ui->comboBoxFile->currentText() == "XML")
        ui->tableViewBus->setModel(busTransport.readXML());
}

void MainWindow::on_pushButtonFilter_clicked()
{
    QString dateFrom = ui->dateEditFrom->text();
    QString dateTo =ui->dateEditTo->text();
    QString timeFrom = ui->timeEditFrom->text();
    QString timeTo = ui->timeEditTo->text();
    QString placeFrom = ui->lineEditFrom->text();
    QString placeTo = ui->lineEditTo->text();

    QList<Bus> busList;
    if(dateFrom != emptyDate && dateTo != emptyDate){
        busTransport.filter(busTransport.getBusList(),&busList,BusTransport::FilterType::Date, dateFrom, dateTo);
        auto model = BusTransport::getModel(&busList, busTransport.getHeaders());
        ui->tableViewBus->setModel(model);
    }
    if(timeFrom != emptyTime && timeTo != emptyTime){
        busTransport.filter(busTransport.getBusList(),&busList,BusTransport::FilterType::Time, timeFrom, timeTo);
        auto model = BusTransport::getModel(&busList, busTransport.getHeaders());
        ui->tableViewBus->setModel(model);
    }
    if(placeFrom != "" || placeTo != ""){
        busTransport.filter(busTransport.getBusList(),&busList,BusTransport::FilterType::Destination, placeFrom, placeTo);
        auto model = BusTransport::getModel(&busList, busTransport.getHeaders());
        ui->tableViewBus->setModel(model);
    }

}

void MainWindow::on_pushButtonClosest_clicked()
{
    QList<Bus> busList;

    QDate currentFrom = QDate::currentDate();
    QDate currentTo = QDate::currentDate().addMonths(2);

    busTransport.filter(busTransport.getBusList(),&busList,BusTransport::FilterType::Closest,
                        currentFrom.toString("dd.MM.yyyy"), currentTo.toString("dd.MM.yyyy"));
    auto model = BusTransport::getModel(&busList, busTransport.getHeaders());
    ui->tableViewBus->setModel(model);

}
