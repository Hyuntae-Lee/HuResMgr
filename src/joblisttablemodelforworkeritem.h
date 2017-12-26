#ifndef JOBLISTTABLEMODELFORWORKERITEM_H
#define JOBLISTTABLEMODELFORWORKERITEM_H

#include <QList>
#include <QDate>

class JobListTableModelForWorkerItem
{
public:
    JobListTableModelForWorkerItem();

public:
    int pay();
    void setPay(int value);
    QString companyName();
    void setCompanyName(QString value);
    QDate &date();
    void setDate(QDate& date);

private:
    int m_pay;
    QString m_companyName;
    QDate m_date;
};

#endif // JOBLISTTABLEMODELFORWORKERITEM_H
