#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <QStandardItemModel>
#include <QFile>
#include <QObject>

class Transport// : public QObject
{
   // Q_OBJECT
public:
    Transport();
    virtual QStandardItemModel * readCSV(QFile *) = 0;
    virtual ~Transport();
};

#endif // TRANSPORT_H
