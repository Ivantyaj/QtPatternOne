#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <QStandardItemModel>
#include <QFile>

class Transport
{
public:
    Transport();
    virtual QStandardItemModel * readCSV(QFile *) = 0;
    virtual ~Transport();
};

#endif // TRANSPORT_H
