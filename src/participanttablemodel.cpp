#include "participanttablemodel.h"
#include <QMessageBox>

typedef enum {
    PARTICIPANT_COLUMN_LABEL = 0,
    PARTICIPANT_COLUMN_PAY,
    PARTICIPANT_COLUMN_DATES,
    PARTICIPANT_COLUMN_NUM
} ParticipantModelItemColumnIdx;

typedef struct _ParticipantModelItem_t {
    ParticipantModelItemColumnIdx idx;
    QString label;
} ParticipantModelItem_t;

static ParticipantModelItem_t s_model_item[] = {
    /*     idx    ,    label   */
    { PARTICIPANT_COLUMN_LABEL, "대상"     },
    { PARTICIPANT_COLUMN_PAY  , "수당(일)" },
    { PARTICIPANT_COLUMN_DATES, "일정"     }
};

ParticipantTableModel::ParticipantTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

void ParticipantTableModel::clearItems()
{
    m_itemList.clear();
}

void ParticipantTableModel::addItem(QString rrNum, QString name, int pay)
{
    if (_worker_in_participants(rrNum)) {
        return;
    }

    ParticipantTableModelItem item;
    item.setWorkerRrNum(rrNum);
    item.setWorkerName(name);
    item.setPayPerDay(pay);

    m_itemList.append(item);

    emit layoutChanged();
}

QString ParticipantTableModel::workerRrNum(int index)
{
    return m_itemList[index].workerRrNum();
}

bool ParticipantTableModel::setPay(int index, int pay)
{
    if (index >= m_itemList.count()) {
        return false;
    }

    m_itemList[index].setPayPerDay(pay);

    return true;
}

int ParticipantTableModel::pay(int index)
{
    if (index >= m_itemList.count()) {
        return false;
    }

    return m_itemList[index].payPerDay();
}

bool ParticipantTableModel::setDayList(int index, QList<QDate> list)
{
    if (index >= m_itemList.count()) {
        return false;
    }

    m_itemList[index].setWorkDayList(list);

    return true;
}

QList<QDate>& ParticipantTableModel::dayList(int index)
{
    return m_itemList[index].workDateList();
}

QVariant ParticipantTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        if (section >= PARTICIPANT_COLUMN_NUM) {
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

int ParticipantTableModel::rowCount(const QModelIndex &) const
{
    return m_itemList.count();
}

int ParticipantTableModel::columnCount(const QModelIndex &) const
{
    return PARTICIPANT_COLUMN_NUM;
}

QVariant ParticipantTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignCenter | Qt::AlignVCenter);
    }

    if (role == Qt::DisplayRole) {
        ParticipantTableModelItem item = m_itemList[index.row()];

        if (index.column() == PARTICIPANT_COLUMN_LABEL) {
            return item.labelStr();
        }

        if (index.column() == PARTICIPANT_COLUMN_PAY) {
            return QString("%1").arg(item.payPerDay());
        }

        if (index.column() == PARTICIPANT_COLUMN_DATES) {
            return item.daysStr();
        }
    }

    return QVariant();
}

bool ParticipantTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole && index.column() == PARTICIPANT_COLUMN_PAY) {
        QString strValue = value.toString();

        bool ok;
        int intValue = strValue.toInt(&ok);
        if (!ok) {
            QMessageBox::critical(NULL, QString("오류"), QString("숫자만 입력 가능 합니다."), QString("예"));
            return false;
        }

        m_itemList[index.row()].setPayPerDay(intValue);
        return true;
    }

    return false;
}

Qt::ItemFlags ParticipantTableModel::flags (const QModelIndex &index) const
{
    ParticipantTableModelItem item = m_itemList[index.row()];

    if (index.column() == PARTICIPANT_COLUMN_LABEL) {
        return Qt::ItemIsEnabled | Qt::ItemIsEditable;
    }

    if (index.column() == PARTICIPANT_COLUMN_PAY) {
        return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    }

    if (index.column() == PARTICIPANT_COLUMN_DATES) {
        return Qt::ItemIsEnabled | Qt::ItemIsEditable;
    }

    return Qt::NoItemFlags | Qt::ItemIsEditable;
}

bool ParticipantTableModel::_worker_in_participants(QString rrNum)
{
    foreach(ParticipantTableModelItem item, m_itemList) {
        if (rrNum == item.workerRrNum()) {
            return true;
        }
    }

    return false;
}
