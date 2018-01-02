#ifndef JOBLISTTABLEMODELFORWORKER_H
#define JOBLISTTABLEMODELFORWORKER_H

#include <QAbstractTableModel>
#include "job.h"
#include "worker.h"
#include "company.h"
#include "joblisttablemodelforworkeritem.h"

class JobListTableModelForWorker : public QAbstractTableModel
{
    Q_OBJECT

public:
    typedef enum {
        COL_COMPANYNAME = 0,
        COL_PAY,
        COL_DATE,
        COL_NUM
    } ModelItemColumnIdx;

    typedef struct _ModelItem_t {
        JobListTableModelForWorker::ModelItemColumnIdx idx;
        QString label;
        int width;
    } ModelItem_t;

public:
    explicit JobListTableModelForWorker(QList<Job>& jobList, QList<Worker>& workerList, QList<Company>& companyList);

public:
    void setWorker(QString rrNum);
    void setPeriod(QDate& from, QDate& to);
    int columnSize(ModelItemColumnIdx idx);
    void refresh();
    void exportToExcelFile(QString path);

public:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QString _getItemData(int row, int col) const;

private:
    QList<JobListTableModelForWorkerItem> m_itemList;
    QList<Job>& m_jobList;
    QList<Worker>& m_workerList;
    QList<Company>& m_companyList;
    QDate m_dateFrom;
    QDate m_dateTo;
    QString m_workerRRNum;
};

#endif // JOBLISTTABLEMODELFORWORKER_H
