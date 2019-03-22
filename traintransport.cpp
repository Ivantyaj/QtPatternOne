#include "traintransport.h"

TrainTransport &TrainTransport::getInstance()
{
    static TrainTransport instance;
    return instance;
}

TrainTransport::TrainTransport()
{

}

QStandardItemModel *TrainTransport::readCSV(QFile *file)
{
    trainList.clear();
    trainListFiltered.clear();
    //TODO
    file = new QFile();
    file->setFileName("E:\\Projects\\Qt\\pattern\\train.csv");
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
        QStringList stringListTrain;
        for(QString item : line.split(";")){
            stringListTrain << item;
            stdItemList.append(new QStandardItem(item));
        }
        addTrain(stringListTrain);


        model->insertRow(model->rowCount(),stdItemList);
        qDebug() << stdItemList;
    }
    file->close();

    trainListFiltered = trainList;

    return model;
}

QStandardItemModel *TrainTransport::readXML(QFile *file)
{
    trainList.clear();
    trainListFiltered.clear();
    //TODO
    file = new QFile();
    file->setFileName("E:\\Projects\\Qt\\pattern\\TrainS.xml");
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
                QStringList stringListTrain;
                QList<QStandardItem *> stdItemList;
                while(token != QXmlStreamReader::EndElement && xmlReader.name() != "record"){
                    xmlReader.readNext();
                    //qDebug() << xmlReader.name() << xmlReader.readElementText();
                    QString element = xmlReader.readElementText();
                    if(element != "" && xmlReader.name() != "record"){
                        stringListTrain << element;
                        stdItemList.append(new QStandardItem(element));
                        //qDebug() << stringListTrain;
                    }
                }
                addTrain(stringListTrain);

                model->insertRow(model->rowCount(),stdItemList);

                //qDebug() << stdItemList;
                //qDebug() << "-----------";
            }

        }
        trainListFiltered = trainList;

        return model;
    }
}

void TrainTransport::addTrain(const QStringList &trainStringList)
{
    Train train;
    train.setFromStringList(trainStringList);
    trainList.append(train);
}

QList<Train> * TrainTransport::getTrainList()
{
    return &trainList;
}

QStringList *TrainTransport::getHeaders()
{
    return &headers;
}

void TrainTransport::filter(TransportFactory::FilterType type, const QString &from, const QString &to)
{
    trainListFiltered.clear();
    switch(type){
    case TransportFactory::FilterType::Date:

        for(Train train : trainList){

            if(QDate::fromString(train.getDateDeparture(), "dd.MM.yyyy") >= QDate::fromString(from, "dd.MM.yyyy")
                    && QDate::fromString(train.getDateArrival(), "dd.MM.yyyy") <= QDate::fromString(to, "dd.MM.yyyy")){
                trainListFiltered.append(train);
            }
        }
        break;
    case TransportFactory::FilterType::Time:
        for(Train train : trainList){
            qDebug() << from << " to " << to;
            qDebug() << QTime::fromString(train.getTimeDeparture(), "hh:mm") << "  " << QTime::fromString(from, "hh:mm");
            if(QTime::fromString(train.getTimeDeparture(), "hh:mm") >= QTime::fromString(from, "hh:mm")
                    && QTime::fromString(train.getTimeArrival(), "hh:mm") <= QTime::fromString(to, "hh:mm")){
                trainListFiltered.append(train);
            }
        }
        break;
    case TransportFactory::FilterType::Destination:
        if(from == "" && to == ""){
            trainListFiltered.clear();
            return;
        }
        if(from != "" && to != ""){
            for(Train train: trainList){
                if(train.getDeparturePlace() == from && train.getArrivalPlace() == to){
                    trainListFiltered.append(train);
                }
            }
            return;
        }
        if (from != "") {
            for(Train train: trainList){
                if(train.getDeparturePlace() == from){
                    trainListFiltered.append(train);
                }
            }
            return;
        }
        if (to != ""){
            for(Train train: trainList){
                if(train.getArrivalPlace() == to){
                    trainListFiltered.append(train);
                }
            }
        }

        break;
    case TransportFactory::FilterType::Closest:
        for(Train train : trainList){

            if(QDate::fromString(train.getDateDeparture(), "dd.MM.yyyy") >= QDate::fromString(from, "dd.MM.yyyy")
                    && QDate::fromString(train.getDateDeparture(), "dd.MM.yyyy") <= QDate::fromString(to, "dd.MM.yyyy")){
                trainListFiltered.append(train);
            }
        }
        break;
    }
}

QStandardItemModel *TrainTransport::getModel()
{
    QStandardItemModel * model = new QStandardItemModel();
    model->setColumnCount(10);
    model->setHorizontalHeaderLabels(headers);

    for(Train train: trainListFiltered){
        QList<QStandardItem *> stdItemList;
        train.initIteration();
        while(train.isEnd()){
            QString field = train.getNext();
            stdItemList.append(new QStandardItem(field));
        }
        model->insertRow(model->rowCount(),stdItemList);
    }

    return model;
}

void TrainTransport::resetFilter()
{
    trainListFiltered = trainList;
}

