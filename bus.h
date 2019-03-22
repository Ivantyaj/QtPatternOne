#ifndef BUS_H
#define BUS_H

#include <QDate>
#include <QTime>
#include <QStringList>
#include <QString>
#include <QDebug>

#include "iteratorobject.h"

class Bus : public IteratorObject
{

private:
    int num;
    QDate dateDeparture;
    QDate dateArrival;
    QTime timeDeparture;
    QTime timeArrival;
    QString arrivalPlace;
    QString departurePlace;
    QString terminalDeparture;
    QString terminalArrival;
    int cost;

public:
    Bus();

    void setFromStringList(const QStringList & string);

//Setters
    void setNum(const int);

    void setTimeDeparture(const QTime &);
    void setDateDeparture(const QDate &);
    void setTimeArrival(const QTime &);
    void setDateArrival(const QDate &);
    void setCost(const int);

//Getters
    QString getNum();
    QString getDateDeparture();
    QString getDateArrival();
    QString getTimeDeparture();
    QString getTimeArrival();
    QString getArrivalPlace();
    QString getDeparturePlace();
    QString getTerminalDeparture();
    QString getTerminalArrival();
    QString getCost();

//Iterator
    virtual QString getNext();
    virtual void initIteration();
};

#endif // BUS_H
