#include "dialognewworker.h"
#include "ui_dialognewworker.h"
#include "worker.h"

DialogNewWorker::DialogNewWorker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewWorker)
{
    ui->setupUi(this);
}

DialogNewWorker::~DialogNewWorker()
{
    delete ui;
}

bool DialogNewWorker::getWorkInfo(Worker* worker)
{
    if (!worker) {
        return false;
    }

    QString name = ui->lineEdit_name->text();
    QString rrNum = ui->lineEdit_workerRrNum->text();
    QStringList majorListStr = ui->lineEdit_major->text().split(",");
    QString address = ui->lineEdit_address->text();
    QString phoneNum = ui->lineEdit_phoneNum->text();
    QString bankAccount = ui->lineEdit_bankAccount->text();

    worker->setRrNum(rrNum);
    worker->setName(name);
    worker->setAddress(address);
    worker->setPhoneNum(phoneNum);
    worker->setBankAccount(bankAccount);
    foreach(QString major, majorListStr) {
        worker->addMajor(major);
    }

    return true;
}
