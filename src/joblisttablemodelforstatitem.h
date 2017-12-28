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
    QString companyBlNum();
    void setCompanyBlNum(QString value);
    QString workerRrNum();
    void setWorkerRrNum(QString value);

private:
    int m_id;
    QString m_companyName;
    QString m_companyBlNum;
    QString m_workerName;
    QString m_workerRrNum;
    long long m_pay;
    QDate m_date;
};

#endif // JOBLISTTABLEMODELFORSTATITEM_H
