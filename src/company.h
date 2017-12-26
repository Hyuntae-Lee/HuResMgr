#ifndef COMPANY_H
#define COMPANY_H

#include <QString>\

class Company
{
public:
    Company();

public:
    int idNum();
    void setIdNum(int value);
    QString name();
    void setName(QString value);
    QString blNum();
    void setBlNum(QString value);
    QString address();
    void setAddress(QString value);
    QString owner();
    void setOwner(QString value);
    QString bankAccount();
    void setBankAccount(QString value);
    QString phoneNum();
    void setPhoneNum(QString value);
    bool operator ==(Company &w) const;
    QString labelStr();

private:
    int m_idNum;
    QString m_name;
    QString m_blNum;
    QString m_address;
    QString m_owner;
    QString m_bankAccount;
    QString m_phoneNum;
};

#endif // COMPANY_H
