#include "workerlistmodel.h"

WorkerListModel::WorkerListModel(QList<Worker> &workList)
    : m_itemList(workList)
{
}

int WorkerListModel::rowCount(const QModelIndex &) const
{
    return m_itemList.count();
}

QVariant WorkerListModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        return m_itemList[index.row()].name();
    }
    else {
        return QVariant();
    }
}

QString WorkerListModel::rrNum(const QModelIndex &index)
{
    return m_itemList[index.row()].rrNum();
}

void WorkerListModel::refresh()
{
    emit layoutChanged();
}
