#ifndef COMPANYLISTMODELFORNEWJOB_H
#define COMPANYLISTMODELFORNEWJOB_H

#include <QAbstractListModel>
#include "company.h"

class CompanyListModelForNewJob : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit CompanyListModelForNewJob(QList<Company> &companyList);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QString blNum(const QModelIndex &index);

private:
    QList<Company> &m_itemList;
};

#endif // COMPANYLISTMODELFORNEWJOB_H
