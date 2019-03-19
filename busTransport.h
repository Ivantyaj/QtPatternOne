#ifndef BUSTRANSPORT_H
#define BUSTRANSPORT_H
#include "transport.h"
#include <QTextStream>
#include <QList>
#include <QXmlStreamReader>
#include "bus.h"

class BusTransport : public Transport
{
   // Q_OBJECT
public:
    enum FilterType {
        Date,
        Time,
        Destination,
        Closest
    };
private:
    QList<Bus> busList;
    QStringList headers;
public:
    BusTransport();

    QStandardItemModel * readCSV(QFile *file = nullptr);
    QStandardItemModel * readXML(QFile *file = nullptr);

    void addBus(const QStringList &bus);
    QList<Bus> * getBusList();
    QStringList * getHeaders();
    void filter(const QList<Bus> * sourceList, QList<Bus> *filterList, BusTransport::FilterType type, const QString &from, const QString &to);
    static QStandardItemModel * getModel(QList<Bus> *, QStringList *);
};

#endif // BUSTRANSPORT_H
