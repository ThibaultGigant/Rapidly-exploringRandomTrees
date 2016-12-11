#ifndef VERTICESNUMBER_H
#define VERTICESNUMBER_H

#include <QtGlobal>
#include "endmethod.h"

class VerticesNumber : public EndMethod
{
public:
    VerticesNumber(quint64 maxNumber);
    ~VerticesNumber();
    virtual bool isOver();

private:
    quint64 nbVertices;
    quint64 maxNumber;
};

#endif // VERTICESNUMBER_H
