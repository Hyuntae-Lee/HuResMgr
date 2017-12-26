#ifndef JOBHISTORYTABLEMODELFORWORKER_H
#define JOBHISTORYTABLEMODELFORWORKER_H

#include <QAbstractTableModel>
#include "job.h"
#include "worker.h"
#include "company.h"
#include "jobhistorytablemodelforworkeritem.h"

class JobHistoryTableModelForWorker : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit JobHistoryTableModelForWorker(QList<Job>& jobList, QList<Worker>& workerList, QList<Company>& companyList);

public:
    void clearItems();
    void setWorker(QString rrNum);

public:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    bool jobListForWorker(QList<Job>& out_list, QString rrNum);
    QString findCompanyNameWithBlNum(QString blNum);
    int findWorkerPayWithRRNum(QString rrNum);

private:
    QList<JobHistoryTableModelForWorkerItem> m_itemList;
    QList<Job>& m_jobList;
    QList<Worker>& m_workerList;
    QList<Company>& m_companyList;
};

#endif // JOBHISTORYTABLEMODELFORWORKER_H
