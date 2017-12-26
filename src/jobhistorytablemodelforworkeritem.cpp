#include "jobhistorytablemodelforworkeritem.h"

JobHistoryTableModelForWorkerItem::JobHistoryTableModelForWorkerItem()
{

}

QString JobHistoryTableModelForWorkerItem::workerName()
{
    return m_workerName;
}

void JobHistoryTableModelForWorkerItem::setWorkerName(QString value)
{
    m_workerName = value;
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
