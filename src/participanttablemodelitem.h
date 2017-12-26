#ifndef PARTICIPANTTABLEMODELITEM_H
#define PARTICIPANTTABLEMODELITEM_H

#include <QString>
#include <QList>
#include <QDate>

class ParticipantTableModelItem
{
public:
    ParticipantTableModelItem();

public:
    QString workerRrNum();
    void setWorkerRrNum(QString value);
    QString workerName();
    void setWorkerName(QString value);
    int payPerDay();
    void setPayPerDay(int value);
    QList<QDate>& workDateList();
    void addWorkDay(QDate value);
    void setWorkDayList(QList<QDate> value);
    QString labelStr();
    QString daysStr();

private:
    QString m_workerRrNum;
    QString m_workerName;
    int m_payPerDay;
    QList<QDate> m_workDateList;
};

#endif // PARTICIPANTTABLEMODELITEM_H
