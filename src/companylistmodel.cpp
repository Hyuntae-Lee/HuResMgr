#include "companylistmodel.h"

CompanyListModel::CompanyListModel(QList<Company> &companyList)
    : m_itemList(companyList)
{
}

int CompanyListModel::rowCount(const QModelIndex &) const
{
    return m_itemList.count();
}

QVariant CompanyListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        return m_itemList[index.row()].name();
    }
    else {
        return QVariant();
    }
}

QString CompanyListModel::blNum(const QModelIndex &index)
{
    return m_itemList[index.row()].blNum();
}

void CompanyListModel::refresh()
{
    emit layoutChanged();
}
