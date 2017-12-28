#ifndef JOBLISTTABLEMODELFORSTATITEM_H
#define JOBLISTTABLEMODELFORSTATITEM_H

#include <QString>
#include <QDate>

class JobListTableModelForStatItem
{
public:
    JobListTableModelForStatItem();

public:
    int id();
    void setId(int value);
    QString companyName();
    void setCompanyName(QString value);
    QString workerName();
    void setWorkerName(QString value);
    long long pay();
    void setPay(long long value);
    QDate date();
    void setDate(QDate& value);

private:
    int m_id;
    QString m_companyName;
    QString m_workerName;
    long long m_pay;
    QDate m_date;
};

#endif // JOBLISTTABLEMODELFORSTATITEM_H
