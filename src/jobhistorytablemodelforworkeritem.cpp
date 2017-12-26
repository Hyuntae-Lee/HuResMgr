#include "jobhistorytablemodelforworkeritem.h"

JobHistoryTableModelForWorkerItem::JobHistoryTableModelForWorkerItem()
{

}

int JobHistoryTableModelForWorkerItem::pay()
{
    return m_pay;
}

void JobHistoryTableModelForWorkerItem::setPay(int value)
{
    m_pay = value;
}

QString JobHistoryTableModelForWorkerItem::companyName()
{
    return m_companyName;
}

void JobHistoryTableModelForWorkerItem::setCompanyName(QString value)
{
    m_companyName = value;
}

QDate& JobHistoryTableModelForWorkerItem::date()
{
    return m_date;
}

void JobHistoryTableModelForWorkerItem::setDate(QDate& date)
{
    m_date = date;
}
