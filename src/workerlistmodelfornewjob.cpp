#include "workerlistmodelfornewjob.h"

WorkerListModelForNewJob::WorkerListModelForNewJob(QList<Worker> &workList)
    : m_itemList(workList)
{
}

int WorkerListModelForNewJob::rowCount(const QModelIndex &) const
{
    return m_itemList.count();
}

QVariant WorkerListModelForNewJob::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        return m_itemList[index.row()].name();
    }
    else {
        return QVariant();
    }
}

QString WorkerListModelForNewJob::rrNum(const QModelIndex &index)
{
    return m_itemList[index.row()].rrNum();
}
