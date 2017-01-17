#ifndef ENDMETHOD_H
#define ENDMETHOD_H

#include <ctime>
#include <QtGlobal>
#include <QThread>

class EndMethod
{
public:
    EndMethod(quint64 maxNumber = 0, time_t duration = 0);
    ~EndMethod();
    bool isOver();
    bool isTimeOver();
    bool isNbVerticesOver();

    // Getters and setters
    quint64 getMaxNumber() const;
    time_t getLimitTime() const;
    quint64 getNbVertices() const;
    void setMaxNumber(const quint64 &value);
    void setDuration(const time_t &value);

    void reset();
    QString toString();

private:
    quint64 nbVertices;
    quint64 maxNumber;
    time_t duration;
    time_t startTime;

};

#endif // ENDMETHOD_H
