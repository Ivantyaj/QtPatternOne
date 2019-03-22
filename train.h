#ifndef TRAIN_H
#define TRAIN_H


#include <QDate>
#include <QTime>
#include <QStringList>
#include <QString>
#include <QDebug>

#include "iteratorobject.h"
#include "transport.h"

class Train : public IteratorObject//, public Transport
{

private:
    QString num;
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
    Train();

    void setFromStringList(const QStringList & string);

//Setters
    void setNum(const QString);

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

#endif // TRAIN_H
