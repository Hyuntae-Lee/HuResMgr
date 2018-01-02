#ifndef JOBLISTTABLEMODELFORWORKERITEM_H
#define JOBLISTTABLEMODELFORWORKERITEM_H

#include <QList>
#include <QDate>

class JobListTableModelForWorkerItem
{
public:
    JobListTableModelForWorkerItem();

public:
    int id();
    void setId(int value);
    long long pay();
    void setPay(long long value);
    QString companyName();
    void setCompanyName(QString value);
    QDate &date();
    void setDate(QDate& date);

private:
    int m_id;
    long long m_pay;
    QString m_companyName;
    QDate m_date;
};

#endif // JOBLISTTABLEMODELFORWORKERITEM_H
