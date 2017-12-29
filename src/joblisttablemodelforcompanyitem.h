#ifndef JOBLISTTABLEMODELFORCOMPANYITEM_H
#define JOBLISTTABLEMODELFORCOMPANYITEM_H

#include <QString>
#include <QDate>

class JobListTableModelForCompanyItem
{
public:
    JobListTableModelForCompanyItem();

public:
    int id();
    void setId(int value);
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
    QString m_companyBlNum;
    QString m_workerName;
    QString m_workerRrNum;
    long long m_pay;
    QDate m_date;
};

#endif // JOBLISTTABLEMODELFORCOMPANYITEM_H
