#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <QStandardItemModel>

class Transport
{
public:
    Transport();
    virtual QStandardItemModel * readCSV() = 0;
    virtual ~Transport();
};

#endif // TRANSPORT_H
