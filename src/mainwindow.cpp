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
#include "joblisttablemodelforstat.h"
#include "workerlistmodel.h"
#include "companylistmodel.h"

#define DB_FILE_PATH "/data/main.db"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_dbHdlr = new DBHdlr;
    m_model_worker = new WorkerListModel(m_workerList);
    m_model_company = new CompanyListModel(m_companyList);
    m_model_jobListForWorker = new JobListTableModelForWorker(m_jobList, m_workerList, m_companyList);
    m_model_jobListForStat = new JobListTableModelForStat(m_jobList, m_workerList, m_companyList);

    ui->setupUi(this);

    ui->listView_worker->setModel(m_model_worker);
    ui->listView_company->setModel(m_model_company);
    ui->tableView_jobListForWorker->setModel(m_model_jobListForWorker);
    ui->tableView_jobListForStat->setModel(m_model_jobListForStat);

    _init_jobListPeriod();
    _init_uiSizes();
}

MainWindow::~MainWindow()
{
    delete m_dbHdlr;
    delete m_model_worker;
    delete m_model_company;
    delete m_model_jobListForWorker;
    delete m_model_jobListForStat;
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
    m_model_worker->refresh();
}

void MainWindow::on_pushButton_removeWorker_clicked()
{
    if (m_workerList.count() <= 0) {
        return;
    }

    QString rrNum = m_model_worker->rrNum(ui->listView_worker->currentIndex());
    m_dbHdlr->removeWorker(rrNum);

    _load_worker_list(m_workerList);
    m_model_worker->refresh();
}

void MainWindow::on_listView_worker_clicked(const QModelIndex &index)
{
    if (index.row() >= m_workerList.count()) {
        return;
    }

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
    m_model_company->refresh();
}

void MainWindow::on_pushButton_removeCompany_clicked()
{
    if (m_companyList.count() <= 0) {
        return;
    }

    QString blNum = m_model_company->blNum(ui->listView_company->currentIndex());
    m_dbHdlr->removeCompany(blNum);

    _load_company_list(m_companyList);
    m_model_company->refresh();
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

    QList<Job> jobList;
    if (!dlg.getJob(jobList)) {
        return;
    }

    foreach (Job job, jobList) {
        m_dbHdlr->addJob(job);
    }

    _load_job_list(m_jobList);
    _update_job_list(m_jobList);
}

void MainWindow::_load_worker_list(QList<Worker>& listValue)
{
    listValue.clear();
    if (!m_dbHdlr->getWorkerList(listValue)) {
        QMessageBox::critical(this, tr("Error"), tr("Cannot load data from!!"), tr("Ok"));
        return;
    }

    m_model_worker->refresh();
}

void MainWindow::_load_company_list(QList<Company> &listValue)
{
    listValue.clear();
    if (!m_dbHdlr->getCompanyList(listValue)) {
        QMessageBox::critical(this, tr("Error"), tr("Cannot load data from!!"), tr("Ok"));
        return;
    }

    m_model_company->refresh();
}

void MainWindow::_update_job_list(QList<Job>)
{
    QDate dateFrom = ui->dateEdit_stat_from->date();
    QDate dateTo = ui->dateEdit_stat_to->date();

    m_model_jobListForStat->setPeriod(dateFrom, dateTo);
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

void MainWindow::_init_jobListPeriod()
{
    QDate dateTo = QDate::currentDate();

    QDate dateFrom;
    QDate dateTmp = QDate(dateTo.year(), dateTo.month() - 1, 1);
    if (dateTo.day() > dateTmp.daysInMonth()) {
        dateFrom = QDate(dateTo.year(), dateTo.month() - 1, dateTmp.daysInMonth());
    }
    else {
        dateFrom = QDate(dateTo.year(), dateTo.month() - 1, dateTo.day());
    }

    ui->dateEdit_stat_from->setDate(dateFrom);
    ui->dateEdit_stat_to->setDate(dateTo);
}

void MainWindow::_init_uiSizes()
{
    // job list table for selected period
    for (int i = 0; i < JobListTableModelForStat::COL_NUM; i++) {
        JobListTableModelForStat::ModelItemColumnIdx idx = (JobListTableModelForStat::ModelItemColumnIdx)i;
        ui->tableView_jobListForStat->setColumnWidth(idx, m_model_jobListForStat->columnSize(idx));
    }

    // job list table for selected worker
    for (int i = 0; i < JobListTableModelForWorker::COL_NUM; i++) {
        JobListTableModelForWorker::ModelItemColumnIdx idx = (JobListTableModelForWorker::ModelItemColumnIdx)i;
        ui->tableView_jobListForWorker->setColumnWidth(idx, m_model_jobListForWorker->columnSize(idx));
    }
}
