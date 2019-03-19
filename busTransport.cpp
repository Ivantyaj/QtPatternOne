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

QStandardItemModel *BusTransport::readXML(QFile *file)
{
    file = new QFile();
    file->setFileName("E:\\Projects\\Qt\\pattern\\BusS.xml");
    QStringList stringList;
    if (!file->open(QFile::ReadOnly | QFile::Text))
    {
        return nullptr;
    } else {
        qDebug() << "XML reader";
        /* Создаем объект, с помощью которого осуществляется чтение из файла */
        QXmlStreamReader xmlReader;
        xmlReader.setDevice(file);
        //xmlReader.readNext();   // Переходит к первому элементу в файле
        QStandardItemModel * model = new QStandardItemModel();
        model->setColumnCount(10);
        while(!xmlReader.atEnd())
        {
            //qDebug() << "XML reader first";
            QXmlStreamReader::TokenType token = xmlReader.readNext();
            if (token == QXmlStreamReader::StartElement && xmlReader.name() == "record") {
                token = xmlReader.readNext();
                QStringList stringListBus;
                QList<QStandardItem *> stdItemList;
                while(token != QXmlStreamReader::EndElement && xmlReader.name() != "record"){
                    xmlReader.readNext();
                    //qDebug() << xmlReader.name() << xmlReader.readElementText();
                    QString element = xmlReader.readElementText();
                    if(element != "" && xmlReader.name() != "record"){
                        stringListBus << element;
                        stdItemList.append(new QStandardItem(element));
                        //qDebug() << stringListBus;
                    }
                }
                addBus(stringListBus);

                model->insertRow(model->rowCount(),stdItemList);

                //qDebug() << stdItemList;
                //qDebug() << "-----------";
            }

        }
        return model;
    }
}

void BusTransport::addBus(const QStringList &busStringList)
{
    Bus bus;
    bus.setBusFromStringList(busStringList);
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
    filterList->clear();
    switch(type){
    case BusTransport::FilterType::Date:

        for(Bus bus : *sourceList){

            if(QDate::fromString(bus.getDateDeparture(), "dd.MM.yyyy") >= QDate::fromString(from, "dd.MM.yyyy")
                    && QDate::fromString(bus.getDateArrival(), "dd.MM.yyyy") <= QDate::fromString(to, "dd.MM.yyyy")){
                filterList->append(bus);
            }
        }
        break;
    case BusTransport::FilterType::Time:
        for(Bus bus : *sourceList){
            qDebug() << from << " to " << to;
            qDebug() << QTime::fromString(bus.getTimeDeparture(), "hh:mm") << "  " << QTime::fromString(from, "hh:mm");
            if(QTime::fromString(bus.getTimeDeparture(), "hh:mm") >= QTime::fromString(from, "hh:mm")
                    && QTime::fromString(bus.getTimeArrival(), "hh:mm") <= QTime::fromString(to, "hh:mm")){
                filterList->append(bus);
            }
        }
        break;
    case BusTransport::FilterType::Destination:
        if(from == "" && to == ""){
            filterList = nullptr;
            return;
        }
        if(from != "" && to != ""){
            for(Bus bus: *sourceList){
                if(bus.getDeparturePlace() == from && bus.getArrivalPlace() == to){
                    filterList->append(bus);
                }
            }
            return;
        }
        if (from != "") {
            for(Bus bus: *sourceList){
                if(bus.getDeparturePlace() == from){
                    filterList->append(bus);
                }
            }
            return;
        }
        if (to != ""){
            for(Bus bus: *sourceList){
                if(bus.getArrivalPlace() == to){
                    filterList->append(bus);
                }
            }
        }

        break;
    case BusTransport::FilterType::Closest:
        for(Bus bus : *sourceList){

            if(QDate::fromString(bus.getDateDeparture(), "dd.MM.yyyy") >= QDate::fromString(from, "dd.MM.yyyy")
                    && QDate::fromString(bus.getDateDeparture(), "dd.MM.yyyy") <= QDate::fromString(to, "dd.MM.yyyy")){
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
        bus.initIteration();
        while(bus.isEnd()){
            QString field = bus.getNext();
            stdItemList.append(new QStandardItem(field));
        }
        model->insertRow(model->rowCount(),stdItemList);
    }

    return model;
}
