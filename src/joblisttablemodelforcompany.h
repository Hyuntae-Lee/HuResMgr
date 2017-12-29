#ifndef JOBLISTTABLEMODELFORCOMPANY_H
#define JOBLISTTABLEMODELFORCOMPANY_H

#include <QAbstractTableModel>

#include "joblisttablemodelforcompanyitem.h"
#include "job.h"
#include "worker.h"
#include "company.h"

class JobListTableModelForCompany : public QAbstractTableModel
{
    Q_OBJECT

public:
    typedef enum {
        COL_NO = 0,
        COL_WORKERNAME,
        COL_PAY,
        COL_DATE,
        COL_NUM
    } ModelItemColumnIdx;

    typedef struct _ModelItem_t {
        ModelItemColumnIdx idx;
        QString label;
        int width;
    } ModelItem_t;

public:
    JobListTableModelForCompany(QList<Job>& jobList, QList<Worker>& workerList, QList<Company>& companyList);

public:
    void setCompany(QString blNum);
    void setPeriod(QDate& from, QDate& to);
    int columnSize(ModelItemColumnIdx idx);
    QString companyBlNum(const QModelIndex &index);
    QString workerRRNum(const QModelIndex &index);
    QDate workDate(const QModelIndex &index);
    void refresh();

public:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QList<JobListTableModelForCompanyItem> m_itemList;
    QList<Job>& m_jobList;
    QList<Worker>& m_workerList;
    QList<Company>& m_companyList;
    QDate m_dateFrom;
    QDate m_dateTo;
    QString m_companyBlNum;
};

#endif // JOBLISTTABLEMODELFORCOMPANY_H
