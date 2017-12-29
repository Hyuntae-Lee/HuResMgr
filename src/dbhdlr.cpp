#include "dbhdlr.h"
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

const QString DB_DATE_FORMAT = "yyyyMMdd";
const QString DB_SEP_WORKINFO = ",";
const QString DB_SEP_WORKINFO_PROP = ";";
const QString DB_SEP_WORKINFO_DATE = "-";

const QString DRIVER("QSQLITE");

DBHdlr::DBHdlr(QObject *parent) : QObject(parent)
{
    m_db = QSqlDatabase::addDatabase(DRIVER);
}

bool DBHdlr::connectToDB(QString fileName)
{
    if(!QSqlDatabase::isDriverAvailable(DRIVER)) {
        return false;
    }

    m_db.setDatabaseName(fileName);
    if(!m_db.open()) {
        qWarning() << "Cannot open database!!";
        return false;
    }

    return true;
}

bool DBHdlr::getWorkerList(QList<Worker>& list)
{
    if (!m_db.isOpen()) {
        return false;
    }

    QString queryStr = QString("SELECT id, name, rr_num, major, picture_path, address, phone_num, bank_account, pay FROM Worker");

    QSqlQuery query(queryStr);
    if(!query.isActive()) {
        qWarning() << "getWorkerList - ERROR: " << query.lastError().text();
        return false;
    }

    while (query.next()) {
        int id_num = query.value("id").toInt();
        QString name = query.value("name").toString();
        QString rrNum = query.value("rr_num").toString();
        QString picturePath = query.value("picture_path").toString();
        QString address = query.value("address").toString();
        QString phoneNum = query.value("phone_num").toString();
        QString bankAccount = query.value("bank_account").toString();
        QStringList majorList = query.value("major").toString().split(",");
        QString payStr = query.value("pay").toString();

        Worker worker;
        worker.setIdNum(id_num);
        worker.setName(name);
        worker.setRrNum(rrNum);
        worker.setPicturePath(picturePath);
        worker.setAddress(address);
        worker.setPhoneNum(phoneNum);
        worker.setBankAccount(bankAccount);
        foreach(QString major, majorList) {
            worker.addMajor(major);
        }

        bool ok;
        int pay = payStr.toLongLong(&ok);
        if (ok) {
            worker.setPay(pay);
        }
        else {
            worker.setPay(0);
        }

        list.append(worker);
    }

    return true;
}

bool DBHdlr::addWorker(Worker worker)
{
    if (!m_db.isOpen()) {
        return false;
    }

    QString queryStr = QString("INSERT INTO Worker(rr_num, name, major, picture_path, address, phone_num, bank_account, pay) VALUES('%1','%2','%3','%4','%5','%6','%7','%8')")
            .arg(worker.rrNum()).arg(worker.name()).arg(worker.majorStr())
            .arg(worker.picturePath()).arg(worker.address()).arg(worker.phoneNum())
            .arg(worker.bankAccount()).arg(QString("%1").arg(worker.pay()));

    QSqlQuery query(queryStr);
    if(!query.isActive()) {
        qWarning() << "addWorker - ERROR: " << query.lastError().text();
        return false;
    }

    return true;
}

bool DBHdlr::updateWorker(QString rrNum, QString name, QString majorStr, QString phoneNum,
                          QString address, QString account, long long pay, QString picturePath)
{
    if (!m_db.isOpen()) {
        return false;
    }

    QString queryStr = QString("UPDATE Worker SET name = '%2', major = '%3', picture_path = '%4', address = '%5', phone_num = '%6', bank_account = '%7', pay = '%8' WHERE rr_num = '%1'")
            .arg(rrNum).arg(name).arg(majorStr).arg(picturePath).arg(address).arg(phoneNum)
            .arg(account).arg(QString("%1").arg(pay));

    QSqlQuery query(queryStr);
    if(!query.isActive()) {
        qWarning() << "updateWorker - ERROR: " << query.lastError().text();
        return false;
    }

    return true;
}

bool DBHdlr::removeWorker(QString rrNum)
{
    if (!m_db.isOpen()) {
        return false;
    }

    QString queryStr = QString("DELETE FROM Worker WHERE rr_num = '%1'").arg(rrNum);

    QSqlQuery query(queryStr);
    if(!query.isActive()) {
        qWarning() << "removeWorker - ERROR: " << query.lastError().text();
        return false;
    }

    return true;
}

bool DBHdlr::getCompanyList(QList<Company>& list)
{
    if (!m_db.isOpen()) {
        return false;
    }

    QString queryStr = QString("SELECT id, business_license, name, owner, address, phone_num, bank_account FROM Company");

    QSqlQuery query(queryStr);
    if(!query.isActive()) {
        qWarning() << "getCompanyList - ERROR: " << query.lastError().text();
        return false;
    }

    while (query.next()) {
        int id_num = query.value("id").toInt();
        QString name = query.value("name").toString();
        QString blNum = query.value("business_license").toString();
        QString address = query.value("address").toString();
        QString phoneNum = query.value("phone_num").toString();
        QString bankAccount = query.value("bank_account").toString();
        QString owner = query.value("owner").toString();

        Company company;
        company.setIdNum(id_num);
        company.setName(name);
        company.setBlNum(blNum);
        company.setAddress(address);
        company.setPhoneNum(phoneNum);
        company.setBankAccount(bankAccount);
        company.setOwner(owner);

        list.append(company);
    }

    return true;
}

bool DBHdlr::addCompany(Company company)
{
    if (!m_db.isOpen()) {
        return false;
    }

    QString queryStr = QString("INSERT INTO Company(business_license, name, owner, address, phone_num, bank_account) VALUES('%1','%2','%3','%4','%5','%6')")
            .arg(company.blNum()).arg(company.name()).arg(company.owner())
            .arg(company.address()).arg(company.phoneNum()).arg(company.bankAccount());

    QSqlQuery query(queryStr);
    if(!query.isActive()) {
        qWarning() << "addCompany - ERROR: " << query.lastError().text();
        return false;
    }

    return true;
}

bool DBHdlr::updateCompany(QString blNum, QString name, QString address, QString owner,
                           QString account, QString phoneNum)
{
    if (!m_db.isOpen()) {
        return false;
    }

    QString queryStr = QString("UPDATE Company SET name = '%2', owner = '%3', address = '%4', phone_num = '%5', bank_account = '%6' WHERE business_license = '%1'")
            .arg(blNum).arg(name).arg(owner).arg(address).arg(phoneNum).arg(account);

    QSqlQuery query(queryStr);
    if(!query.isActive()) {
        qWarning() << "updateCompany - ERROR: " << query.lastError().text();
        return false;
    }

    return true;
}

bool DBHdlr::removeCompany(QString blNum)
{
    if (!m_db.isOpen()) {
        return false;
    }

    QString queryStr = QString("DELETE FROM Company WHERE business_license = '%1'").arg(blNum);

    QSqlQuery query(queryStr);
    if(!query.isActive()) {
        qWarning() << "removeCompany - ERROR: " << query.lastError().text();
        return false;
    }

    return true;
}

bool DBHdlr::getJobList(QList<Job>& list)
{
    if (!m_db.isOpen()) {
        return false;
    }

    QString queryStr = QString("SELECT id, company_blNum, worker_rrnum, date FROM Job");

    QSqlQuery query(queryStr);
    if(!query.isActive()) {
        qWarning() << "getJobList - ERROR: " << query.lastError().text();
        return false;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        QString companyBlNum = query.value("company_blNum").toString();
        QString workerRRnum = query.value("worker_rrnum").toString();
        QString dateStr = query.value("date").toString();

        Job job(id);
        job.setCompanyBlNum(companyBlNum);
        job.setWorkerRRNum(workerRRnum);
        job.setDate(QDate::fromString(dateStr, DB_DATE_FORMAT));

        list.append(job);
    }

    return true;
}

bool DBHdlr::addJob(Job job)
{
    if (!m_db.isOpen()) {
        return false;
    }

    QString queryStr = QString("INSERT INTO Job(company_blNum, worker_rrnum, date) VALUES('%1','%2','%3')")
            .arg(job.companyBlNum()).arg(job.workerRRNum()).arg(job.date().toString(DB_DATE_FORMAT));

    QSqlQuery query(queryStr);
    if(!query.isActive()) {
        qWarning() << "addJob - ERROR: " << query.lastError().text();
        return false;
    }

    return true;
}

bool DBHdlr::removeJob(QString blNum, QString rrNum, QDate date)
{
    if (!m_db.isOpen()) {
        return false;
    }

    QString queryStr = QString("DELETE FROM Job WHERE company_blNum = '%1' AND worker_rrnum = '%2' AND date = '%3'")
            .arg(blNum).arg(rrNum).arg(date.toString(DB_DATE_FORMAT));

    QSqlQuery query(queryStr);
    if(!query.isActive()) {
        qWarning() << "removeJob - ERROR: " << query.lastError().text();
        return false;
    }

    return true;
}
