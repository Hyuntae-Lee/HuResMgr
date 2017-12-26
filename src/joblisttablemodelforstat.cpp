#include "joblisttablemodelforstat.h"

typedef enum {
    COLUMN_NO = 0,
    COLUMN_COMPANYNAME,
    COLUMN_WORKERNAME,
    COLUMN_PAY,
    COLUMN_DATE,
    COLUMN_NUM
} WorkHistoryModelItemColumnIdx;

typedef struct _WorkHistoryModelItem_t {
    WorkHistoryModelItemColumnIdx idx;
    QString label;
} WorkHistoryModelItem_t;

static WorkHistoryModelItem_t s_model_item[] = {
    /*       idx        , label  */
    { COLUMN_NO         , "순번" },
    { COLUMN_COMPANYNAME, "업체" },
    { COLUMN_WORKERNAME , "인재" },
    { COLUMN_PAY        , "일당" },
    { COLUMN_DATE       , "일자" },
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

}

QVariant JobListTableModelForStat::headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    Error : 여기부터

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

int JobListTableModelForStat::rowCount(const QModelIndex &parent = QModelIndex()) const override
{
    return m_itemList.count();
}

int JobListTableModelForStat::columnCount(const QModelIndex &parent = QModelIndex()) const
{
    return COLUMN_NUM;
}

QVariant JobListTableModelForStat::data(const QModelIndex &index, int role = Qt::DisplayRole) const
{

}
