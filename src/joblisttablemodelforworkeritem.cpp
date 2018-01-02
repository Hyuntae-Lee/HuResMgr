#include "joblisttablemodelforworkeritem.h"

JobListTableModelForWorkerItem::JobListTableModelForWorkerItem()
{

}

int JobListTableModelForWorkerItem::id()
{
    return m_id;
}

void JobListTableModelForWorkerItem::setId(int value)
{
    m_id = value;
}

long long JobListTableModelForWorkerItem::pay()
{
    return m_pay;
}

void JobListTableModelForWorkerItem::setPay(long long value)
{
    m_pay = value;
}

QString JobListTableModelForWorkerItem::companyName()
{
    return m_companyName;
}

void JobListTableModelForWorkerItem::setCompanyName(QString value)
{
    m_companyName = value;
}

QDate& JobListTableModelForWorkerItem::date()
{
    return m_date;
}

void JobListTableModelForWorkerItem::setDate(QDate& date)
{
    m_date = date;
}
