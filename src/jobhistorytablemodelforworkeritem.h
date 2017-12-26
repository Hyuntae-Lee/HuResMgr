#ifndef JOBHISTORYTABLEMODELFORWORKERITEM_H
#define JOBHISTORYTABLEMODELFORWORKERITEM_H

#include <QList>
#include <QDate>

class JobHistoryTableModelForWorkerItem
{
public:
    JobHistoryTableModelForWorkerItem();

public:
    QString workerName();
    void setWorkerName(QString value);
    int pay();
    void setPay(int value);
    QString companyName();
    void setCompanyName(QString value);
    QDate &date();
    void setDate(QDate& date);

private:
    QString m_workerName;
    int m_pay;
    QString m_companyName;
    QDate m_date;
};

#endif // JOBHISTORYTABLEMODELFORWORKERITEM_H
