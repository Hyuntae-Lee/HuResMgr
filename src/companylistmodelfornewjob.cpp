#include "companylistmodelfornewjob.h"

CompanyListModelForNewJob::CompanyListModelForNewJob(QList<Company> &companyList)
    : m_itemList(companyList)
{
}

int CompanyListModelForNewJob::rowCount(const QModelIndex &) const
{
    return m_itemList.count();
}

QVariant CompanyListModelForNewJob::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        return m_itemList[index.row()].name();
    }
    else {
        return QVariant();
    }
}

QString CompanyListModelForNewJob::blNum(const QModelIndex &index)
{
    return m_itemList[index.row()].blNum();
}
