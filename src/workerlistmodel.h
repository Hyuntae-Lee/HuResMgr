#ifndef WORKERLISTMODEL_H
#define WORKERLISTMODEL_H

#include <QAbstractListModel>
#include "worker.h"

class WorkerListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit WorkerListModel(QList<Worker>& workList);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QString rrNum(const QModelIndex &index);
    void refresh();

private:
    QList<Worker>& m_itemList;
};

#endif // WORKERLISTMODEL_H
