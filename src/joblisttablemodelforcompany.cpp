#include "joblisttablemodelforcompany.h"

#include "util.h"

static JobListTableModelForCompany::ModelItem_t s_model_item[] = {
    /*                   idx                   , label , size  */
    { JobListTableModelForCompany::COL_NO         , "순번", 50    },
    { JobListTableModelForCompany::COL_WORKERNAME , "인재", 100   },
    { JobListTableModelForCompany::COL_PAY        , "일당", 150   },
    { JobListTableModelForCompany::COL_DATE       , "일자", 100   },
};

JobListTableModelForCompany::JobListTableModelForCompany(QList<Job> &jobList, QList<Worker> &workerList, QList<Company> &companyList)
    : m_jobList(jobList), m_workerList(workerList), m_companyList(companyList)
{
}

void JobListTableModelForCompany::clearItems()
{
    m_itemList.clear();
}

void JobListTableModelForCompany::setPeriod(QDate& from, QDate& to)
{
    if (from > to) {
        return;
    }

    m_dateFrom = from;
    m_dateTo = to;

    refresh();
}

int JobListTableModelForCompany::columnSize(ModelItemColumnIdx idx)
{
    return s_model_item[idx].width;
}

QString JobListTableModelForCompany::companyBlNum(const QModelIndex &index)
{
    return m_itemList[index.row()].companyBlNum();
}

QString JobListTableModelForCompany::workerRRNum(const QModelIndex &index)
{
    return m_itemList[index.row()].workerRrNum();
}

QDate JobListTableModelForCompany::workDate(const QModelIndex &index)
{
    return m_itemList[index.row()].date();
}

void JobListTableModelForCompany::refresh()
{
    m_itemList.clear();
    foreach (Job job, m_jobList) {
        if (job.date() >= m_dateFrom && job.date() <= m_dateTo) {

            int id = job.id();
            QString companyName = Util::findCompanyNameWithBlNum(m_companyList, job.companyBlNum());
            QString workerName = Util::findWorkerNameWithRRNum(m_workerList, job.workerRRNum());
            long long pay = Util::findWorkerPayWithRRNum(m_workerList, job.workerRRNum());
            QDate date = job.date();

            JobListTableModelForCompanyItem item;
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

int JobListTableModelForCompany::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int JobListTableModelForCompany::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant JobListTableModelForCompany::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
