#include "busTransport.h"
#include <QtDebug>


BusTransport::BusTransport()
{

}

QStandardItemModel *BusTransport::readCSV(QFile *file)
{
    //TODO
    file = new QFile();
    file->setFileName("E:\\Projects\\Qt\\pattern\\bus.csv");
    file->open(QFile::ReadOnly | QFile::Text);

    qDebug() << "Hi read CSV";
    QStandardItemModel * model = new QStandardItemModel();
    model->setColumnCount(10);

    QTextStream in(file);
    if(!in.atEnd()){
        QString line = in.readLine();
        QStringList stringList;
        for(QString item : line.split(";")){
            stringList << item;
        }
        model->setHorizontalHeaderLabels(stringList);
        headers = stringList;
        qDebug() << stringList;
    }

    while(!in.atEnd()){
        QString line = in.readLine();
        QList<QStandardItem *> stdItemList;
        QStringList stringListBus;
        for(QString item : line.split(";")){
            stringListBus << item;
            stdItemList.append(new QStandardItem(item));
        }
        addBus(stringListBus);


        model->insertRow(model->rowCount(),stdItemList);
        qDebug() << stdItemList;
    }
    file->close();

    return model;
}

void BusTransport::addBus(const QStringList &busStringList)
{
    Bus bus;
    bus.setBusFromCsv(busStringList);
    busList.append(bus);
}

QList<Bus> * BusTransport::getBusList()
{
    return &busList;
}

QStringList *BusTransport::getHeaders()
{
    return &headers;
}

void BusTransport::filter(const QList<Bus> * sourceList, QList<Bus> *filterList, BusTransport::FilterType type, const QString &from, const QString &to)
{
    qDebug() << "hello filter";

    filterList->clear();
    switch(type){
    case BusTransport::FilterType::Date:

        for(Bus bus : *sourceList){

            if(QDate::fromString(bus.getDateDeparture(), "dd.MM.yyyy") >= QDate::fromString(from, "dd.MM.yyyy")
                    && QDate::fromString(bus.getDateArrival(), "dd.MM.yyyy") <= QDate::fromString(to, "dd.MM.yyyy")){
                filterList->append(bus);
                qDebug() << "filtered  " << bus.getNum();
            }
        }

        break;
    case BusTransport::FilterType::Time:
        for(Bus bus : *sourceList){
            if(bus.getTimeDeparture() >= from && bus.getTimeArrival() <= to){
                filterList->append(bus);
            }
        }
        break;
    }
}

QStandardItemModel *BusTransport::getModel(QList<Bus> * busSource, QStringList *headers)
{
    if(!busSource){
        return nullptr;
    }

    QStandardItemModel * model = new QStandardItemModel();
    model->setColumnCount(9);

    model->setHorizontalHeaderLabels(*headers);

    for(Bus bus: *busSource){
        QList<QStandardItem *> stdItemList;
        //TODO ITERATOR
        bus.initIteration();
        while(bus.isEnd()){
            QString field = bus.getNext();

            qDebug() << field;
            stdItemList.append(new QStandardItem(field));

            //qDebug() << "end " << bus.isEnd() << "  " << bus.iteration << " " << bus.fieldCount;
            //stdItemList.append(new QStandardItem(bus.getNext()));
        }
        model->insertRow(model->rowCount(),stdItemList);
    }

    return model;
}
