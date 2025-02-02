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

    transportFactory = &BusTransport::getInstance();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonRead_clicked()
{

    if(ui->tabWidget->currentWidget() == ui->tabBus){
        if(ui->comboBoxFile->currentText() == "CSV")
            ui->tableViewBus->setModel(transportFactory->readCSV());
        if(ui->comboBoxFile->currentText() == "XML")
            ui->tableViewBus->setModel(transportFactory->readXML());
    }
    if(ui->tabWidget->currentWidget() == ui->tabTrain){
        if(ui->comboBoxFile->currentText() == "CSV")
            ui->tableViewTrain->setModel(transportFactory->readCSV());
        if(ui->comboBoxFile->currentText() == "XML")
            ui->tableViewTrain->setModel(transportFactory->readXML());
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

    transportFactory->resetFilter();
    if(dateFrom != emptyDate && dateTo != emptyDate){
        transportFactory->filter(TransportFactory::FilterType::Date, dateFrom, dateTo);
    }
    if(timeFrom != emptyTime && timeTo != emptyTime){
        transportFactory->filter(TransportFactory::FilterType::Time, timeFrom, timeTo);
    }
    if(placeFrom != "" || placeTo != ""){
        transportFactory->filter(TransportFactory::FilterType::Destination, placeFrom, placeTo);
    }
    auto model = transportFactory->getModel();

    if(ui->tabWidget->currentWidget() == ui->tabBus){
        ui->tableViewBus->setModel(model);
    }
    if(ui->tabWidget->currentWidget() == ui->tabTrain){
        ui->tableViewTrain->setModel(model);
    }
}

void MainWindow::on_pushButtonClosest_clicked()
{
    QDate currentFrom = QDate::currentDate();
    QDate currentTo = QDate::currentDate().addMonths(2);

    transportFactory->filter(TransportFactory::FilterType::Closest,
                             currentFrom.toString("dd.MM.yyyy"), currentTo.toString("dd.MM.yyyy"));
    auto model = transportFactory->getModel();

    if(ui->tabWidget->currentWidget() == ui->tabBus){
        ui->tableViewBus->setModel(model);
    }
    if(ui->tabWidget->currentWidget() == ui->tabTrain){
        ui->tableViewTrain->setModel(model);
    }
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

    chartView->setChart(chart);
}

void MainWindow::on_pushButtonFavorite_clicked()
{
    if(ui->tabWidget->currentWidget() == ui->tabBus){
        int tableBusSelectedRow = ui->tableViewBus->currentIndex().row();
        QModelIndex busModelIndex = ui->tableViewBus->model()->index(tableBusSelectedRow,0);
        ui->listWidgetBus->addItem(ui->tableViewBus->model()->data(busModelIndex).toString());
    }
    if(ui->tabWidget->currentWidget() == ui->tabTrain){
        int tableTrainSelectedRow = ui->tableViewTrain->currentIndex().row();
        QModelIndex trainModelIndex = ui->tableViewTrain->model()->index(tableTrainSelectedRow,0);
        ui->listWidgetTrain->addItem(ui->tableViewTrain->model()->data(trainModelIndex).toString());
    }
}

void MainWindow::on_pushButtonClearFavorite_clicked()
{
    if(ui->tabWidget->currentWidget() == ui->tabBus){
        ui->listWidgetBus->clear();
    }
    if(ui->tabWidget->currentWidget() == ui->tabTrain){
        ui->listWidgetTrain->clear();
    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    switch (index) {
    case 0:
        transportFactory = &BusTransport::getInstance();
        break;
    case 1:
        transportFactory = &TrainTransport::getInstance();
        break;
    }
}
