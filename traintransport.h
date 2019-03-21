#ifndef TRAINTRANSPORT_H
#define TRAINTRANSPORT_H

#include "transportfactory.h"
#include <QTextStream>
#include <QList>
#include <QXmlStreamReader>
#include <train.h>

class TrainTransport: public TransportFactory
{
public:

private:
    QList<Train> trainList;
    QList<Train> trainListFiltered;
    QStringList headers;

public:
    TrainTransport();

    QStandardItemModel * readCSV(QFile *file = nullptr);
    QStandardItemModel * readXML(QFile *file = nullptr);

    void filter(TransportFactory::FilterType type, const QString &from, const QString &to);
    QStandardItemModel * getModel();
    void resetFilter();

private:
    void addTrain(const QStringList &train);
    QList<Train> * getTrainList();
    QStringList * getHeaders();
};

#endif // TRAINTRANSPORT_H
