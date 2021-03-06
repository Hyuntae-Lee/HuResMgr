#ifndef DBHDLR_H
#define DBHDLR_H

#include <QObject>
#include <QSqlDatabase>
#include "worker.h"
#include "company.h"
#include "job.h"

class DBHdlr : public QObject
{
    Q_OBJECT
public:
    explicit DBHdlr(QObject *parent = 0);
    bool connectToDB(QString fileName);
    bool getWorkerList(QList<Worker>& list);
    bool addWorker(Worker worker);
    bool updateWorker(QString rrNum, QString name, QString majorStr, QString phoneNum,
                      QString address, QString account, long long pay, QString picturePath);
    bool removeWorker(QString rrNum);
    bool getCompanyList(QList<Company>& list);
    bool addCompany(Company company);
    bool updateCompany(QString blNum, QString name, QString address, QString owner,
                       QString account, QString phoneNum);
    bool removeCompany(QString blNum);
    bool getJobList(QList<Job>& list);
    bool addJob(Job job);
    bool removeJob(QString blNum, QString rrNum, QDate date);

signals:

public slots:

private:
    QSqlDatabase m_db;
};

#endif // DBHDLR_H
