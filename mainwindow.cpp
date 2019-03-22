#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qdebug.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{    
    ui->setupUi(this);

    chartView = new QChartView();
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->verticalLayout->addWidget(chartView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonRead_clicked()
{
    if(ui->tabWidget->currentWidget() == ui->tabBus){
        //transportFactory = new BusTransport();
        transportFactory = &BusTransport::getInstance();
        if(ui->comboBoxFile->currentText() == "CSV")
            ui->tableViewBus->setModel(transportFactory->readCSV());
        if(ui->comboBoxFile->currentText() == "XML")
            ui->tableViewBus->setModel(transportFactory->readXML());
    }
    if(ui->tabWidget->currentWidget() == ui->tabTrain){
        transportFactory = new TrainTransport();
        if(ui->comboBoxFile->currentText() == "CSV")
            ui->tableViewBus->setModel(transportFactory->readCSV());
        if(ui->comboBoxFile->currentText() == "XML")
            ui->tableViewBus->setModel(transportFactory->readXML());
    }
    reloadChart();
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
    if(!transportFactory)
        return;

    QDate currentFrom = QDate::currentDate();
    QDate currentTo = QDate::currentDate().addMonths(2);

    transportFactory->filter(TransportFactory::FilterType::Closest,
                             currentFrom.toString("dd.MM.yyyy"), currentTo.toString("dd.MM.yyyy"));
    auto model = transportFactory->getModel();
    ui->tableViewBus->setModel(model);

}

void MainWindow::reloadChart()
{
    int busCount;
    int trainCount;

    if(ui->tableViewBus->model()){
        busCount = ui->tableViewBus->model()->rowCount();
    } else {
        busCount = 0;
    }

    if(ui->tableViewTrain->model()){
        trainCount = ui->tableViewTrain->model()->rowCount();
    } else {
        trainCount = 0;
    }

    QPieSeries *series = new QPieSeries();
    series->append("Bus", busCount);
    series->append("Train", trainCount);


    QPieSlice *slice = series->slices().at(0);
    slice->setExploded();
    slice->setLabelVisible();
    slice->setPen(QPen(Qt::darkGreen, 2));
    slice->setBrush(Qt::green);

    QPieSlice *sliceTrain = series->slices().at(1);
    sliceTrain->setExploded();
    sliceTrain->setLabelVisible();

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Количество транспорта");
    chart->legend()->hide();

    //chartView = new QChartView(chart);
    chartView->setChart(chart);
}
