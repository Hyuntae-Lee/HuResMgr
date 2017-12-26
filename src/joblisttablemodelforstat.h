#ifndef JOBLISTTABLEMODELFORSTAT_H
#define JOBLISTTABLEMODELFORSTAT_H

#include <QAbstractTableModel>
#include "joblisttablemodelforstatitem.h"
#include "job.h"
#include "worker.h"
#include "company.h"

class JobListTableModelForStat : public QAbstractTableModel
{
    Q_OBJECT

public:
    JobListTableModelForStat(QList<Job>& jobList, QList<Worker>& workerList, QList<Company>& companyList);

public:
    void clearItems();
    void setPeriod(QDate& from, QDate& to);

public:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QList<JobListTableModelForStatItem> m_itemList;
    QList<Job>& m_jobList;
    QList<Worker>& m_workerList;
    QList<Company>& m_companyList;
};

#endif // JOBLISTTABLEMODELFORSTAT_H
