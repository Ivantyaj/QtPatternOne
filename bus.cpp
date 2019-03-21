#include "bus.h"

Bus::Bus() : IteratorObject (10)
{

}

void Bus::setFromStringList(const QStringList &stringList)
{
    if(stringList.size() < 10){
        return;
    }

    //qDebug() << "list " << stringList;
    //qDebug() << "time " << stringList[3] << " sd " <<QTime::fromString(stringList[3], "hh:mm");
    setNum(stringList[0].toInt());
    setDateDeparture(QDate::fromString(stringList[1], "dd.MM.yyyy"));
    setDateArrival(QDate::fromString(stringList[2], "dd.MM.yyyy"));
    setTimeDeparture(QTime::fromString(stringList[3], "hh:mm"));
    setTimeArrival(QTime::fromString(stringList[4], "hh:mm"));
    departurePlace = stringList[5];
    arrivalPlace = stringList[6];
    terminalDeparture = stringList[7];
    terminalArrival = stringList[8];
    setCost(stringList[9].toInt());
}

void Bus::setNum(const int num)
{
    this->num = num;
    qDebug() << "setNum " << this->num;
}

void Bus::setTimeDeparture(const QTime & time)
{
    timeDeparture = time;
    //emit signalTimeDepartureChanged(time);
}

void Bus::setDateDeparture(const QDate &date)
{
    dateDeparture = date;
    //emit signalDateDepartureChanged(date);
}

void Bus::setTimeArrival(const QTime & time)
{
    timeArrival = time;
    //emit signalTimeArrivalChanged(time);
}

void Bus::setDateArrival(const QDate & date)
{
    dateArrival = date;
    //emit signalDateArrivalChanged(date);
}

void Bus::setCost(const int cost)
{
    this->cost = cost;
}

QString Bus::getNum()
{
    return QString::number(num);
}

QString Bus::getTimeDeparture()
{
    return timeDeparture.toString("hh:mm");
}

QString Bus::getDateDeparture()
{
    return dateDeparture.toString("dd.MM.yyyy");
}

QString Bus::getTimeArrival()
{
    qDebug() << "time " << timeArrival;
    qDebug() << timeArrival.toString("hh:mm");
    return timeArrival.toString("hh:mm");
}

QString Bus::getArrivalPlace()
{
    return arrivalPlace;
}

QString Bus::getDeparturePlace()
{
    return departurePlace;
}

QString Bus::getTerminalDeparture()
{
    return terminalDeparture;
}

QString Bus::getTerminalArrival()
{
    return terminalArrival;
}

QString Bus::getCost()
{
    return QString::number(cost);
}

QString Bus::getDateArrival()
{
    return dateArrival.toString("dd.MM.yyyy");
}

QString Bus::getNext()
{
    switch(iteration){
    case 0:
        iteration++;
        return getNum();
    case 1:
        iteration++;
        return getDateDeparture();
    case 2:
        iteration++;
        return getDateArrival();
    case 3:
        iteration++;
        return getTimeDeparture();
    case 4:
        iteration++;
        return getTimeArrival();
    case 5:
        iteration++;
        return getDeparturePlace();
    case 6:
        iteration++;
        return getArrivalPlace();
    case 7:
        iteration++;
        return getTerminalDeparture();
    case 8:
        iteration++;
        return getTerminalArrival();
    case 9:
        iteration++;
        return getCost();
    default:
        return "";
    }

}

void Bus::initIteration()
{
    iteration = 0;
}
