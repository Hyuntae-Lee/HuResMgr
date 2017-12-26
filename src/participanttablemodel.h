#ifndef PARTICIPANTTABLEMODEL_H
#define PARTICIPANTTABLEMODEL_H

#include <QAbstractTableModel>
#include <QDate>
#include <QList>
#include "participanttablemodelitem.h"

class ParticipantTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ParticipantTableModel(QObject *parent = 0);

public:
    void clearItems();
    void addItem(QString rrNum, QString name, int pay);
    QString workerRrNum(int index);
    bool setPay(int index, int pay);
    int pay(int index);
    bool setDayList(int index, QList<QDate> list);
    QList<QDate>& dayList(int index);

public:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    bool _worker_in_participants(QString rrNum);

private:
    QList<ParticipantTableModelItem> m_itemList;
};

#endif // PARTICIPANTTABLEMODEL_H
