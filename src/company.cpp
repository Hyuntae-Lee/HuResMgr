#include "company.h"

Company::Company()
{

}

int Company::idNum()
{
    return m_idNum;
}

void Company::setIdNum(int value)
{
    m_idNum = value;
}

QString Company::name()
{
    return m_name;
}

void Company::setName(QString value)
{
    m_name = value;
}

QString Company::blNum()
{
    return m_blNum;
}

void Company::setBlNum(QString value)
{
    m_blNum = value;
}

QString Company::address()
{
    return m_address;
}

void Company::setAddress(QString value)
{
    m_address = value;
}

QString Company::owner()
{
    return m_owner;
}

void Company::setOwner(QString value)
{
    m_owner = value;
}

QString Company::bankAccount()
{
    return m_bankAccount;
}

void Company::setBankAccount(QString value)
{
    m_bankAccount = value;
}

QString Company::phoneNum()
{
    return m_phoneNum;
}

void Company::setPhoneNum(QString value)
{
    m_phoneNum = value;
}

bool Company::operator ==(Company &w) const
{
    return (m_idNum == w.idNum() && m_name == w.name());
}

QString Company::labelStr()
{
     return QString("%1").arg(name());
}
