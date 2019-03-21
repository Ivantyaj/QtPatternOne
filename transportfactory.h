#ifndef TRANSPORTFACTORY_H
#define TRANSPORTFACTORY_H

#include <QStandardItemModel>
#include <QFile>
#include <QObject>
#include <QList>
#include "transport.h"


class TransportFactory// : public QObject
{
   // Q_OBJECT
public:
    enum FilterType {
        Date,
        Time,
        Destination,
        Closest
    };
public:
    TransportFactory();
    virtual QStandardItemModel * readCSV(QFile * = nullptr) = 0;
    virtual QStandardItemModel * readXML(QFile * = nullptr) = 0;
    virtual void filter(TransportFactory::FilterType type, const QString &from, const QString &to) = 0;
    virtual void resetFilter() = 0;
    virtual QStandardItemModel * getModel() = 0;
    virtual ~TransportFactory();
};

#endif // TRANSPORTFACTORY_H
