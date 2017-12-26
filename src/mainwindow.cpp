#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QMessageBox>
#include <QStringListModel>
#include "dbhdlr.h"
#include "dialognewworker.h"
#include "dialognewcompany.h"
#include "dialognewjob.h"
#include "joblisttablemodelforworker.h"

#define DB_FILE_PATH "/data/main.db"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_dbHdlr = new DBHdlr;
    m_model_worker = new QStringListModel;
    m_model_company = new QStringListModel;
    m_model_jobListForWorker = new JobListTableModelForWorker(m_jobList, m_workerList, m_companyList);

    ui->setupUi(this);

    ui->listView_worker->setModel(m_model_worker);
    ui->listView_company->setModel(m_model_company);
    ui->tableView_jobListForWorker->setModel(m_model_jobListForWorker);
}

MainWindow::~MainWindow()
{
    delete m_dbHdlr;
    delete m_model_worker;
    delete m_model_company;
    delete m_model_jobListForWorker;
    delete ui;
}

void MainWindow::on_pushButton_connectDB_clicked()
{
#ifndef QT_DEBUG
    QString curPath = QDir::currentPath();
#else
    QString curPath = "D:/projects/etc/HuResMgr";
#endif // QT_DEBUG

    if (!m_dbHdlr->connectToDB(curPath + DB_FILE_PATH)) {
        QMessageBox::critical(this, tr("Error"), tr("Cannot connect to database!!"), tr("Ok"));
        return;
    }

    _load_worker_list(m_workerList);
    _load_company_list(m_companyList);
    _load_job_list(m_jobList);

    _update_worker_list(m_workerList);
    _update_company_list(m_companyList);
    _update_job_list(m_jobList);
}

void MainWindow::on_pushButton_newHR_clicked()
{
    DialogNewWorker dlg;

    if (dlg.exec() != QDialog::Accepted) {
        return;
    }

    Worker worker;
    if (!dlg.getWorker(&worker)) {
        return;
    }

    if (!m_dbHdlr->addWorker(worker)) {
        return;
    }

    _load_worker_list(m_workerList);
    _update_worker_list(m_workerList);
}

void MainWindow::on_listView_worker_clicked(const QModelIndex &index)
{
    Worker worker = m_workerList.at(index.row());

    QString name = worker.name();
    QString rrNum = worker.rrNum();
    QString phoneNum = worker.phoneNum();
    QString address = worker.address();
    QString majorStr = worker.majorStr();

    ui->label_workerName->setText(name);
    ui->label_workerRrNum->setText(rrNum);
    ui->label_workerPhoneNum->setText(phoneNum);
    ui->label_workerAddr->setText(address);
    ui->label_workerMajor->setText(majorStr);

    m_model_jobListForWorker->setWorker(worker.rrNum());
}

void MainWindow::on_pushButton_newCompany_clicked()
{
    DialogNewCompany dlg;

    if (dlg.exec() != QDialog::Accepted) {
        return;
    }

    Company company;
    if (!dlg.getCompanyInfo(&company)) {
        return;
    }

    if (!m_dbHdlr->addCompany(company)) {
        return;
    }

    _load_company_list(m_companyList);
    _update_company_list(m_companyList);
}

void MainWindow::on_listView_company_clicked(const QModelIndex &index)
{
    Company company = m_companyList.at(index.row());

    QString name = company.name();
    QString blNum = company.blNum();
    QString phoneNum = company.phoneNum();
    QString address = company.address();
    QString owner = company.owner();
    QString bankAccount = company.bankAccount();

    ui->label_companyName->setText(name);
    ui->label_companyBlNum->setText(blNum);
    ui->label_companyOwner->setText(owner);
    ui->label_companyAddress->setText(address);
    ui->label_companyPhoneNum->setText(phoneNum);
    ui->label_companyAccount->setText(bankAccount);
}

void MainWindow::on_pushButton_workNew_clicked()
{
    DialogNewJob dlg(m_workerList, m_companyList);

    if (dlg.exec() != QDialog::Accepted) {
        return;
    }

    Job job;
    if (!dlg.getJob(&job)) {
        return;
    }

    if (!m_dbHdlr->addJob(job)) {
        return;
    }

    _load_job_list(m_jobList);
    _update_job_list(m_jobList);
}

void MainWindow::_update_worker_list(QList<Worker> listValue)
{
    QStringList strList;
    foreach (Worker worker, listValue) {
        QString lableStr = QString("%1").arg(worker.name());
        strList.append(lableStr);
    }

    m_model_worker->setStringList(strList);
}

void MainWindow::_load_worker_list(QList<Worker>& listValue)
{
    listValue.clear();
    if (!m_dbHdlr->getWorkerList(listValue)) {
        QMessageBox::critical(this, tr("Error"), tr("Cannot load data from!!"), tr("Ok"));
        return;
    }
}

void MainWindow::_update_company_list(QList<Company> listValue)
{
    QStringList strList;
    foreach (Company company, listValue) {
        QString lableStr = QString("%1").arg(company.name());
        strList.append(lableStr);
    }

    m_model_company->setStringList(strList);
}

void MainWindow::_load_company_list(QList<Company> &listValue)
{
    listValue.clear();
    if (!m_dbHdlr->getCompanyList(listValue)) {
        QMessageBox::critical(this, tr("Error"), tr("Cannot load data from!!"), tr("Ok"));
        return;
    }
}

void MainWindow::_update_job_list(QList<Job> listValue)
{
    // TODO
}

void MainWindow::_load_job_list(QList<Job> &listValue)
{
    listValue.clear();
    if (!m_dbHdlr->getJobList(listValue)) {
        QMessageBox::critical(this, tr("Error"), tr("업무 데이터를 읽을 수 없습니다."), tr("Ok"));
        return;
    }
}

QString MainWindow::_companyLabelStr(QString blNum)
{
    foreach (Company item, m_companyList) {
        if (item.blNum() == blNum) {
            return item.labelStr();
        }
    }

    return "";
}

QString MainWindow::_workerNameStr(QString rrNum)
{
    foreach (Worker item, m_workerList) {
        if (item.rrNum() == rrNum) {
            return item.name();
        }
    }

    return "";
}
