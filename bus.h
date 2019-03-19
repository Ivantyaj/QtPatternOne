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
    QString terminalDeparture;
    QString platform;
    QString terminalArrival;
    int cost;


//    void signalTimeDepartureChanged(QTime);
//    void signalDateDepartureChanged(QDate);
//    void signalTimeArrivalChanged(QTime);
//    void signalDateArrivalChanged(QDate);
public:
    Bus();
    //virtual ~Bus() {}

    void setBusFromCsv(const QStringList & string);

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
    QString getTerminalDeparture();
    QString getPlatform();
    QString getTerminalArrival();
    QString getCost();

//Iterator
    virtual QString getNext();
    virtual void initIteration();
};

#endif // BUS_H
