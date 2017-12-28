#ifndef WORKERLISTMODELFORNEWJOB_H
#define WORKERLISTMODELFORNEWJOB_H

#include <QAbstractListModel>
#include "worker.h"

class WorkerListModelForNewJob : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit WorkerListModelForNewJob(QList<Worker>& workList);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QString rrNum(const QModelIndex &index);

private:
    QList<Worker>& m_itemList;
};

#endif // WORKERLISTMODELFORNEWJOB_H
