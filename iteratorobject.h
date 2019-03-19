#ifndef ITERATOROBJECT_H
#define ITERATOROBJECT_H

#include <QString>

class IteratorObject
{
protected:
    int fieldCount;
    int iteration = 0;
public:
    IteratorObject(int count);

    virtual QString getNext() = 0;
    virtual bool isEnd ();
    virtual void initIteration() = 0;

    virtual ~IteratorObject() {}
};

#endif // ITERATOROBJECT_H
