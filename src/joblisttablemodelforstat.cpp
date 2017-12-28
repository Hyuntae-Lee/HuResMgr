#include "joblisttablemodelforstat.h"
#include "util.h"

static JobListTableModelForStat::ModelItem_t s_model_item[] = {
    /*                   idx                   , label , size  */
    { JobListTableModelForStat::COL_NO         , "순번", 50    },
    { JobListTableModelForStat::COL_COMPANYNAME, "업체", 150   },
    { JobListTableModelForStat::COL_WORKERNAME , "인재", 100   },
    { JobListTableModelForStat::COL_PAY        , "일당", 150   },
    { JobListTableModelForStat::COL_DATE       , "일자", 100   },
};

JobListTableModelForStat::JobListTableModelForStat(QList<Job>& jobList, QList<Worker>& workerList, QList<Company>& companyList)
    : m_jobList(jobList), m_workerList(workerList), m_companyList(companyList)
{

}

void JobListTableModelForStat::clearItems()
{
    m_itemList.clear();
}

void JobListTableModelForStat::setPeriod(QDate& from, QDate& to)
{
    clearItems();

    if (from > to) {
        return;
    }

    foreach (Job job, m_jobList) {
        if (job.date() >= from && job.date() <= to) {

            int id = job.id();
            QString companyName = Util::findCompanyNameWithBlNum(m_companyList, job.companyBlNum());
            QString workerName = Util::findWorkerNameWithRRNum(m_workerList, job.workerRRNum());
            long long pay = Util::findWorkerPayWithRRNum(m_workerList, job.workerRRNum());
            QDate date = job.date();

            JobListTableModelForStatItem item;
            item.setId(id);
            item.setCompanyName(companyName);
            item.setWorkerName(workerName);
            item.setPay(pay);
            item.setDate(date);
            item.setCompanyBlNum(job.companyBlNum());
            item.setWorkerRrNum(job.workerRRNum());

            m_itemList.append(item);
        }
    }

    emit layoutChanged();
}

int JobListTableModelForStat::columnSize(ModelItemColumnIdx idx)
{
    return s_model_item[idx].width;
}

QString JobListTableModelForStat::companyBlNum(const QModelIndex &index)
{
    return m_itemList[index.row()].companyBlNum();
}

QString JobListTableModelForStat::workerRRNum(const QModelIndex &index)
{
    return m_itemList[index.row()].workerRrNum();
}

QDate JobListTableModelForStat::workDate(const QModelIndex &index)
{
    return m_itemList[index.row()].date();
}

void JobListTableModelForStat::refresh()
{
    emit layoutChanged();
}

QVariant JobListTableModelForStat::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        if (section >= COL_NUM) {
            return QVariant();
        }

        return s_model_item[section].label;
    }
    else {
        return QVariant();
    }
}

int JobListTableModelForStat::rowCount(const QModelIndex&) const
{
    return m_itemList.count();
}

int JobListTableModelForStat::columnCount(const QModelIndex&) const
{
    return COL_NUM;
}

QVariant JobListTableModelForStat::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignCenter | Qt::AlignVCenter);
    }

    if (role == Qt::DisplayRole) {
        JobListTableModelForStatItem item = m_itemList[index.row()];

        if (index.column() == COL_NO) {
            return item.id();
        }

        if (index.column() == COL_COMPANYNAME) {
            return item.companyName();
        }

        if (index.column() == COL_WORKERNAME) {
            return item.workerName();
        }

        if (index.column() == COL_PAY) {
            return QString("%1").arg(item.pay());
        }

        if (index.column() == COL_DATE) {
            return item.date().toString(Qt::DefaultLocaleLongDate);
        }
    }

    return QVariant();
}
