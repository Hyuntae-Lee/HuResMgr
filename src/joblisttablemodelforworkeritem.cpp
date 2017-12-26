#include "joblisttablemodelforworkeritem.h"

JobListTableModelForWorkerItem::JobListTableModelForWorkerItem()
{

}

int JobListTableModelForWorkerItem::pay()
{
    return m_pay;
}

void JobListTableModelForWorkerItem::setPay(int value)
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
