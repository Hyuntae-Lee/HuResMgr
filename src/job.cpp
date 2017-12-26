#include "job.h"

Job::Job()
{
}

Job::Job(int id)
{
    m_id = id;
}

int Job::id()
{
    return m_id;
}

QString Job::companyBlNum()
{
    return m_companyBlNum;
}

void Job::setCompanyBlNum(QString value)
{
    m_companyBlNum = value;
}

QString Job::workerRRNum()
{
    return m_workerRRNum;
}

void Job::setWorkerRRNum(QString value)
{
    m_workerRRNum = value;
}

QDate& Job::date()
{
    return m_date;
}

void Job::setDate(QDate value)
{
    m_date = value;
}
