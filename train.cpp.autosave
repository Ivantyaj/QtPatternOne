#include "train.h"

Train::Train() : IteratorObject (10)
{

}

void Train::setFromStringList(const QStringList &stringList)
{
    if(stringList.size() < 10){
        return;
    }

    setNum(stringList[0]);
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

void Train::setNum(const QString num)
{
    this->num = num;
}

void Train::setTimeDeparture(const QTime & time)
{
    timeDeparture = time;
}

void Train::setDateDeparture(const QDate &date)
{
    dateDeparture = date;
}

void Train::setTimeArrival(const QTime & time)
{
    timeArrival = time;
}

void Train::setDateArrival(const QDate & date)
{
    dateArrival = date;
}

void Train::setCost(const int cost)
{
    this->cost = cost;
}

QString Train::getNum()
{
    return num;
}

QString Train::getTimeDeparture()
{
    return timeDeparture.toString("hh:mm");
}

QString Train::getDateDeparture()
{
    return dateDeparture.toString("dd.MM.yyyy");
}

QString Train::getTimeArrival()
{
    qDebug() << "time " << timeArrival;
    qDebug() << timeArrival.toString("hh:mm");
    return timeArrival.toString("hh:mm");
}

QString Train::getArrivalPlace()
{
    return arrivalPlace;
}

QString Train::getDeparturePlace()
{
    return departurePlace;
}

QString Train::getTerminalDeparture()
{
    return terminalDeparture;
}

QString Train::getTerminalArrival()
{
    return terminalArrival;
}

QString Train::getCost()
{
    return QString::number(cost);
}

QString Train::getDateArrival()
{
    return dateArrival.toString("dd.MM.yyyy");
}

QString Train::getNext()
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

void Train::initIteration()
{
    iteration = 0;
}
