#ifndef COMPANYLISTMODEL_H
#define COMPANYLISTMODEL_H

#include <QAbstractListModel>
#include "company.h"

class CompanyListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit CompanyListModel(QList<Company> &companyList);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QString blNum(const QModelIndex &index);
    void refresh();

private:
    QList<Company> &m_itemList;
};

#endif // COMPANYLISTMODEL_H
