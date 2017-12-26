#ifndef WORKER_H
#define WORKER_H

#include <QString>
#include <QList>

class Worker
{
public:
    Worker();

public:
    int idNum();
    void setIdNum(int value);
    QString name();
    void setName(QString value);
    QString rrNum();
    void setRrNum(QString value);
    QList<QString> majorList();
    QString majorStr();
    void addMajor(QString value);
    QString picturePath();
    void setPicturePath(QString value);
    QString address();
    void setAddress(QString value);
    QString phoneNum();
    void setPhoneNum(QString value);
    QString bankAccount();
    void setBankAccount(QString value);
    int pay();
    void setPay(int value);
    bool operator ==(Worker &w) const;

    QString labelStr();

private:
    int m_idNum;
    QString m_name;
    QString m_rrNum;
    QList<QString> m_majorList;
    QString m_picturePath;
    QString m_address;
    QString m_phoneNum;
    QString m_bankAccount;
    int m_pay;
};

#endif // WORKER_H
