#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qdebug.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonRead_clicked()
{
    if(ui->tabWidget->currentWidget() == ui->tabBus){
        transportFactory = new BusTransport();
        if(ui->comboBoxFile->currentText() == "CSV")
            ui->tableViewBus->setModel(transportFactory->readCSV());
        if(ui->comboBoxFile->currentText() == "XML")
            ui->tableViewBus->setModel(transportFactory->readXML());
    }
    if(ui->tabWidget->cornerWidget() == ui->tabTrain){
        transportFactory = new TrainTransport();
        if(ui->comboBoxFile->currentText() == "CSV")
            ui->tableViewBus->setModel(transportFactory->readCSV());
        if(ui->comboBoxFile->currentText() == "XML")
            ui->tableViewBus->setModel(transportFactory->readXML());
    }
}

void MainWindow::on_pushButtonFilter_clicked()
{
    QString dateFrom = ui->dateEditFrom->text();
    QString dateTo =ui->dateEditTo->text();
    QString timeFrom = ui->timeEditFrom->text();
    QString timeTo = ui->timeEditTo->text();
    QString placeFrom = ui->lineEditFrom->text();
    QString placeTo = ui->lineEditTo->text();

    if(!transportFactory)
        return;

    transportFactory->resetFilter();
    if(dateFrom != emptyDate && dateTo != emptyDate){
        transportFactory->filter(TransportFactory::FilterType::Date, dateFrom, dateTo);
        auto model = transportFactory->getModel();
        ui->tableViewBus->setModel(model);
    }
    if(timeFrom != emptyTime && timeTo != emptyTime){
        transportFactory->filter(TransportFactory::FilterType::Time, timeFrom, timeTo);
        auto model = transportFactory->getModel();
        ui->tableViewBus->setModel(model);
    }
    if(placeFrom != "" || placeTo != ""){
        transportFactory->filter(TransportFactory::FilterType::Destination, placeFrom, placeTo);
        auto model = transportFactory->getModel();
        ui->tableViewBus->setModel(model);
    }

}

void MainWindow::on_pushButtonClosest_clicked()
{
    QDate currentFrom = QDate::currentDate();
    QDate currentTo = QDate::currentDate().addMonths(2);

    transportFactory->filter(TransportFactory::FilterType::Closest,
                        currentFrom.toString("dd.MM.yyyy"), currentTo.toString("dd.MM.yyyy"));
    auto model = transportFactory->getModel();
    ui->tableViewBus->setModel(model);

}
