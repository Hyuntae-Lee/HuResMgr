#ifndef JOB_H
#define JOB_H

#include <QString>
#include <QDate>

class Job
{
public:
    Job();
    Job(int id);

public:
    int id();
    QString companyBlNum();
    void setCompanyBlNum(QString value);
    QString workerRRNum();
    void setWorkerRRNum(QString value);
    QDate& date();
    void setDate(QDate value);

private:
    int m_id;
    QString m_companyBlNum;
    QString m_workerRRNum;
    QDate m_date;
};

#endif // JOB_H
