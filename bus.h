#ifndef BUS_H
#define BUS_H
#include "transport.h"
#include <QTextStream>
#include <QList>

class Bus : public Transport
{
private:
    QFile *fileCsv;
public:
    Bus();
    QStandardItemModel * readCSV(QFile *file = nullptr);
};

#endif // BUS_H
