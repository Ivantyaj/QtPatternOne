#ifndef TRAINTRANSPORT_H
#define TRAINTRANSPORT_H

#include "transportfactory.h"
#include <QTextStream>
#include <QList>
#include <QXmlStreamReader>
#include "train.h"

class TrainTransport: public TransportFactory
{
public:
    static TrainTransport & getInstance();
private:
    TrainTransport();
    TrainTransport(const TrainTransport &);
    TrainTransport& operator=(TrainTransport &);
private:
    QList<Train> trainList;
    QList<Train> trainListFiltered;
    QStringList headers;
public:

    QStandardItemModel * readCSV(QFile *file = nullptr);
    QStandardItemModel * readXML(QFile *file = nullptr);

    void filter(TransportFactory::FilterType type, const QString &from, const QString &to);
    QStandardItemModel * getModel();
    void resetFilter();

private:
    void addTrain(const QStringList &Train);
    QList<Train> * getTrainList();
    QStringList * getHeaders();
};

#endif // TRAINTRANSPORT_H
