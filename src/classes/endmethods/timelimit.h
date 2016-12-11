#ifndef TIMELIMIT_H
#define TIMELIMIT_H

#include <ctime>
#include <QtGlobal>
#include "endmethod.h"

class TimeLimit : public EndMethod
{
public:
    TimeLimit(quint64 duration);
    ~TimeLimit();
    virtual bool isOver();

private:
    time_t limitTime;
};

#endif // TIMELIMIT_H
