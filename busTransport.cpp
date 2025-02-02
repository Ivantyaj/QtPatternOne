#include "busTransport.h"
#include <QtDebug>


BusTransport &BusTransport::getInstance()
{
    static BusTransport instance;
    return instance;
}

BusTransport::BusTransport()
{

}

QStandardItemModel *BusTransport::readCSV(QFile *file)
{
    busList.clear();
    busListFiltered.clear();
    //TODO
    file = new QFile();
    file->setFileName("E:\\Projects\\Qt\\pattern\\bus.csv");
    file->open(QFile::ReadOnly | QFile::Text);

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

    busListFiltered = busList;

    return model;
}

QStandardItemModel *BusTransport::readXML(QFile *file)
{
    busList.clear();
    busListFiltered.clear();
    //TODO
    file = new QFile();
    file->setFileName("E:\\Projects\\Qt\\pattern\\BusS.xml");
    QStringList stringList;
    if (!file->open(QFile::ReadOnly | QFile::Text))
    {
        return nullptr;
    } else {
        qDebug() << "XML reader";

        QXmlStreamReader xmlReader;
        xmlReader.setDevice(file);

        QStandardItemModel * model = new QStandardItemModel();
        model->setColumnCount(10);
        while(!xmlReader.atEnd())
        {

            QXmlStreamReader::TokenType token = xmlReader.readNext();
            if (token == QXmlStreamReader::StartElement && xmlReader.name() == "record") {
                token = xmlReader.readNext();
                QStringList stringListBus;
                QList<QStandardItem *> stdItemList;
                while(token != QXmlStreamReader::EndElement && xmlReader.name() != "record"){
                    xmlReader.readNext();

                    QString element = xmlReader.readElementText();
                    if(element != "" && xmlReader.name() != "record"){
                        stringListBus << element;
                        stdItemList.append(new QStandardItem(element));

                    }
                }
                addBus(stringListBus);

                model->insertRow(model->rowCount(),stdItemList);
            }

        }
        busListFiltered = busList;

        return model;
    }
}

void BusTransport::addBus(const QStringList &busStringList)
{
    Bus bus;
    bus.setFromStringList(busStringList);
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

void BusTransport::filter(TransportFactory::FilterType type, const QString &from, const QString &to)
{
    busListFiltered.clear();
    switch(type){
    case TransportFactory::FilterType::Date:

        for(Bus bus : busList){

            if(QDate::fromString(bus.getDateDeparture(), "dd.MM.yyyy") >= QDate::fromString(from, "dd.MM.yyyy")
                    && QDate::fromString(bus.getDateArrival(), "dd.MM.yyyy") <= QDate::fromString(to, "dd.MM.yyyy")){
                busListFiltered.append(bus);
            }
        }
        break;
    case TransportFactory::FilterType::Time:
        for(Bus bus : busList){
            qDebug() << from << " to " << to;
            qDebug() << QTime::fromString(bus.getTimeDeparture(), "hh:mm") << "  " << QTime::fromString(from, "hh:mm");
            if(QTime::fromString(bus.getTimeDeparture(), "hh:mm") >= QTime::fromString(from, "hh:mm")
                    && QTime::fromString(bus.getTimeArrival(), "hh:mm") <= QTime::fromString(to, "hh:mm")){
                busListFiltered.append(bus);
            }
        }
        break;
    case TransportFactory::FilterType::Destination:
        if(from == "" && to == ""){
            busListFiltered.clear();
            return;
        }
        if(from != "" && to != ""){
            for(Bus bus: busList){
                if(bus.getDeparturePlace() == from && bus.getArrivalPlace() == to){
                    busListFiltered.append(bus);
                }
            }
            return;
        }
        if (from != "") {
            for(Bus bus: busList){
                if(bus.getDeparturePlace() == from){
                    busListFiltered.append(bus);
                }
            }
            return;
        }
        if (to != ""){
            for(Bus bus: busList){
                if(bus.getArrivalPlace() == to){
                    busListFiltered.append(bus);
                }
            }
        }

        break;
    case TransportFactory::FilterType::Closest:
        for(Bus bus : busList){

            if(QDate::fromString(bus.getDateDeparture(), "dd.MM.yyyy") >= QDate::fromString(from, "dd.MM.yyyy")
                    && QDate::fromString(bus.getDateDeparture(), "dd.MM.yyyy") <= QDate::fromString(to, "dd.MM.yyyy")){
                busListFiltered.append(bus);
            }
        }
        break;
    }
}

QStandardItemModel *BusTransport::getModel()
{
    QStandardItemModel * model = new QStandardItemModel();
    model->setColumnCount(10);
    model->setHorizontalHeaderLabels(headers);

    for(Bus bus: busListFiltered){
        QList<QStandardItem *> stdItemList;
        bus.initIteration();
        while(bus.isEnd()){
            QString field = bus.getNext();
            stdItemList.append(new QStandardItem(field));
        }
        model->insertRow(model->rowCount(),stdItemList);
    }

    return model;
}

void BusTransport::resetFilter()
{
    busListFiltered = busList;
}
