#ifndef BUSTRANSPORT_H
#define BUSTRANSPORT_H
#include "transportfactory.h"
#include <QTextStream>
#include <QList>
#include <QXmlStreamReader>
#include "bus.h"

class BusTransport : public TransportFactory
{
public:

private:
    QList<Bus> busList;
    QList<Bus> busListFiltered;
    QStringList headers;
public:
    BusTransport();

    QStandardItemModel * readCSV(QFile *file = nullptr);
    QStandardItemModel * readXML(QFile *file = nullptr);

    void filter(TransportFactory::FilterType type, const QString &from, const QString &to);
    QStandardItemModel * getModel();
    void resetFilter();

private:
    void addBus(const QStringList &bus);
    QList<Bus> * getBusList();
    QStringList * getHeaders();
};

#endif // BUSTRANSPORT_H
