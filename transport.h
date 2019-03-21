#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <QStringList>

class Transport
{
public:
    Transport();
    virtual void setFromStringList(const QStringList & string) = 0;
    virtual ~Transport() = 0;
};

#endif // TRANSPORT_H
