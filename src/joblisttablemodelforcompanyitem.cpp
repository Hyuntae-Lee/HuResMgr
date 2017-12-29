#include "joblisttablemodelforcompanyitem.h"

JobListTableModelForCompanyItem::JobListTableModelForCompanyItem()
{

}

int JobListTableModelForCompanyItem::id()
{
    return m_id;
}

void JobListTableModelForCompanyItem::setId(int value)
{
    m_id = value;
}

QString JobListTableModelForCompanyItem::workerName()
{
    return m_workerName;
}

void JobListTableModelForCompanyItem::setWorkerName(QString value)
{
    m_workerName = value;
}

long long JobListTableModelForCompanyItem::pay()
{
    return m_pay;
}

void JobListTableModelForCompanyItem::setPay(long long value)
{
    m_pay = value;
}

QDate JobListTableModelForCompanyItem::date()
{
    return m_date;
}

void JobListTableModelForCompanyItem::setDate(QDate& value)
{
    m_date = value;
}

QString JobListTableModelForCompanyItem::companyBlNum()
{
    return m_companyBlNum;
}

void JobListTableModelForCompanyItem::setCompanyBlNum(QString value)
{
    m_companyBlNum = value;
}

QString JobListTableModelForCompanyItem::workerRrNum()
{
    return m_workerRrNum;
}

void JobListTableModelForCompanyItem::setWorkerRrNum(QString value)
{
    m_workerRrNum = value;
}
