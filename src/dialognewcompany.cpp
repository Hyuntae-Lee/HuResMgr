#include "dialognewcompany.h"
#include "ui_dialognewcompany.h"
#include "company.h"

DialogNewCompany::DialogNewCompany(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewCompany)
{
    ui->setupUi(this);
}

DialogNewCompany::~DialogNewCompany()
{
    delete ui;
}

bool DialogNewCompany::getCompanyInfo(Company* company)
{
    if (!company) {
        return false;
    }

    QString name = ui->lineEdit_companyName->text();
    QString blNum = ui->lineEdit_companyBlNum->text();
    QString address = ui->lineEdit_companyAddress->text();
    QString phoneNum = ui->lineEdit_companyPhoneNum->text();
    QString bankAccount = ui->lineEdit_companyAccount->text();
    QString owner = ui->lineEdit_companyOwner->text();

    company->setBlNum(blNum);
    company->setName(name);
    company->setAddress(address);
    company->setPhoneNum(phoneNum);
    company->setBankAccount(bankAccount);
    company->setOwner(owner);

    return true;
}
