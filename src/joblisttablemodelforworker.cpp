#include "joblisttablemodelforworker.h"
#include <QMessageBox>

typedef enum {
    COLUMN_COMPANY = 0,
    COLUMN_PAY,
    COLUMN_DATE,
    COLUMN_NUM
} WorkHistoryModelItemColumnIdx;

typedef struct _WorkHistoryModelItem_t {
    WorkHistoryModelItemColumnIdx idx;
    QString label;
} WorkHistoryModelItem_t;

static WorkHistoryModelItem_t s_model_item[] = {
    /*       idx      ,   label   */
    { COLUMN_COMPANY  , "업체"     },
    { COLUMN_PAY      , "일당"     },
    { COLUMN_DATE     , "일자"     },
};

JobListTableModelForWorker::JobListTableModelForWorker(QList<Job> &jobList, QList<Worker>& workerList, QList<Company>& companyList)
    : m_jobList(jobList), m_workerList(workerList), m_companyList(companyList)
{
}

void JobListTableModelForWorker::clearItems()
{
    m_itemList.clear();
}

void JobListTableModelForWorker::setWorker(QString rrNum)
{
    clearItems();

    QList<Job> jobList;
    if (!jobListForWorker(jobList, rrNum)) {
        return;
    }

    foreach (Job job, jobList) {
        JobListTableModelForWorkerItem modelItem;

        QString companyName = findCompanyNameWithBlNum(job.companyBlNum());
        int pay = findWorkerPayWithRRNum(job.workerRRNum());
        QDate date = job.date();

        modelItem.setCompanyName(companyName);
        modelItem.setPay(pay);
        modelItem.setDate(date);

        m_itemList.append(modelItem);
    }

    emit layoutChanged();
}

QVariant JobListTableModelForWorker::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        if (section >= COLUMN_NUM) {
            return QVariant();
        }

        return s_model_item[section].label;
    }
    else if (orientation == Qt::Vertical) {
        return QString("%1").arg(section);
    }
    else {
        return QVariant();
    }
}

int JobListTableModelForWorker::rowCount(const QModelIndex &) const
{
    return m_itemList.count();
}

int JobListTableModelForWorker::columnCount(const QModelIndex &) const
{
    return COLUMN_NUM;
}

QVariant JobListTableModelForWorker::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignCenter | Qt::AlignVCenter);
    }

    if (role == Qt::DisplayRole) {
        JobListTableModelForWorkerItem item = m_itemList[index.row()];

        if (index.column() == COLUMN_DATE) {
            return item.date().toString(Qt::DefaultLocaleLongDate);
        }

        if (index.column() == COLUMN_COMPANY) {
            return item.companyName();
        }

        if (index.column() == COLUMN_PAY) {
            return QString("%1").arg(item.pay());
        }
    }

    return QVariant();
}

bool JobListTableModelForWorker::jobListForWorker(QList<Job>& out_list, QString rrNum)
{
    if (m_jobList.count() <= 0) {
        return false;
    }

    foreach (Job job, m_jobList) {
        if (job.workerRRNum() != rrNum) {
            continue;
        }

        out_list.append(job);
    }

    return true;
}

QString JobListTableModelForWorker::findCompanyNameWithBlNum(QString blNum)
{
    foreach (Company company, m_companyList) {
        if (company.blNum() != blNum) {
            continue;
        }

        return company.name();
    }

    return "";
}

int JobListTableModelForWorker::findWorkerPayWithRRNum(QString rrNum)
{
    foreach (Worker worker, m_workerList) {
        if (worker.rrNum() != rrNum) {
            continue;
        }

        return worker.pay();
    }

    return 0;
}
