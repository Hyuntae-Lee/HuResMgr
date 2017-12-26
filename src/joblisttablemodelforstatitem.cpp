#include "joblisttablemodelforstatitem.h"

JobListTableModelForStatItem::JobListTableModelForStatItem()
{

}

int JobListTableModelForStatItem::id()
{
    return m_id;
}

void JobListTableModelForStatItem::setId(int value)
{
    m_id = value;
}

QString JobListTableModelForStatItem::companyName()
{
    return m_companyName;
}

void JobListTableModelForStatItem::setCompanyName(QString value)
{
    m_companyName = value;
}

QString JobListTableModelForStatItem::workerName()
{
    return m_workerName;
}

void JobListTableModelForStatItem::setWorkerName(QString value)
{
    m_workerName = value;
}

int JobListTableModelForStatItem::pay()
{
    return m_pay;
}

void JobListTableModelForStatItem::setPay(int value)
{
    m_pay = value;
}

QDate JobListTableModelForStatItem::date()
{
    return m_date;
}

void JobListTableModelForStatItem::setDate(QDate& value)
{
    m_date = value;
}
