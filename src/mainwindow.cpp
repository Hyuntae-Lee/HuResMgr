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
#include "joblisttablemodelforcompany.h"
#include "workerlistmodel.h"
#include "companylistmodel.h"
#include <QFileDialog>

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
    m_model_jobListForCompany = new JobListTableModelForCompany(m_jobList, m_workerList, m_companyList);

    ui->setupUi(this);

    ui->listView_worker->setModel(m_model_worker);
    ui->listView_company->setModel(m_model_company);
    ui->tableView_jobListForWorker->setModel(m_model_jobListForWorker);
    ui->tableView_jobListForStat->setModel(m_model_jobListForStat);
    ui->tableView_jobListForCompany->setModel(m_model_jobListForCompany);

    _init_jobListPeriod();
    _init_uiSizes();

    _refreshAllData();
}

MainWindow::~MainWindow()
{
    delete m_dbHdlr;
    delete m_model_worker;
    delete m_model_company;
    delete m_model_jobListForWorker;
    delete m_model_jobListForStat;
    delete m_model_jobListForCompany;
    delete ui;
}

void MainWindow::on_pushButton_refreshAllData_clicked()
{
    _refreshAllData();
}

void MainWindow::on_pushButton_addWorker_clicked()
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

    ui->listView_worker->reset();
    ui->listView_worker->setModel(m_model_worker);
}

void MainWindow::on_pushButton_removeWorker_clicked()
{
    if (m_workerList.count() <= 0) {
        return;
    }

    if (QMessageBox::warning(this, tr("경고"), tr("정말 삭제 하시겠습니까?"), QMessageBox::Ok,
                             QMessageBox::Cancel) != QMessageBox::Ok) {
        return;
    }

    QString rrNum = m_model_worker->rrNum(ui->listView_worker->currentIndex());
    m_dbHdlr->removeWorker(rrNum);

    _load_worker_list(m_workerList);
    m_model_worker->refresh();

    ui->listView_worker->reset();
    ui->listView_worker->setModel(m_model_worker);
}

void MainWindow::on_listView_worker_clicked(const QModelIndex &index)
{
    if (index.row() >= m_workerList.count()) {
        return;
    }

    Worker worker = m_workerList.at(index.row());

    ui->lineEdit_workerName->setText(worker.name());
    ui->lineEdit_workerRRNum->setText(worker.rrNum());
    ui->lineEdit_workerPhoneNum->setText(worker.phoneNum());
    ui->textEdit_workerAddress->setText(worker.address());
    ui->lineEdit_workerMajor->setText(worker.majorStr());
    ui->lineEdit_workerPay->setText(worker.payStr());

    QDate dateFrom = ui->dateEdit_worker_from->date();
    QDate dateTo = ui->dateEdit_worker_to->date();

    m_model_jobListForWorker->setPeriod(dateFrom, dateTo);
    m_model_jobListForWorker->setWorker(worker.rrNum());
    m_model_jobListForWorker->refresh();
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

    ui->listView_company->reset();
    ui->listView_company->setModel(m_model_company);
}

void MainWindow::on_pushButton_removeCompany_clicked()
{
    if (m_companyList.count() <= 0) {
        return;
    }

    if (QMessageBox::warning(this, tr("경고"), tr("정말 삭제 하시겠습니까?"), QMessageBox::Ok,
                             QMessageBox::Cancel) != QMessageBox::Ok) {
        return;
    }

    QString blNum = m_model_company->blNum(ui->listView_company->currentIndex());
    m_dbHdlr->removeCompany(blNum);

    _load_company_list(m_companyList);
    m_model_company->refresh();

    ui->listView_company->reset();
    ui->listView_company->setModel(m_model_company);
}

void MainWindow::on_listView_company_clicked(const QModelIndex &index)
{
    Company company = m_companyList.at(index.row());

    // conpany info. update
    ui->lineEdit_companyName->setText(company.name());
    ui->lineEdit_companyBlNum->setText(company.blNum());
    ui->lineEdit_companyOwner->setText(company.owner());
    ui->lineEdit_companyAddress->setText(company.address());
    ui->lineEdit_companyPhoneNum->setText(company.phoneNum());
    ui->lineEdit_companyAccount->setText(company.bankAccount());

    // job list update
    QDate dateFrom = ui->dateEdit_company_from->date();
    QDate dateTo = ui->dateEdit_company_to->date();

    m_model_jobListForCompany->setPeriod(dateFrom, dateTo);
    m_model_jobListForCompany->setCompany(company.blNum());
    m_model_jobListForCompany->refresh();
}

void MainWindow::on_pushButton_addJob_clicked()
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
    _update_job_list_for_stat();
    m_model_jobListForStat->refresh();

    ui->tableView_jobListForStat->reset();
    ui->tableView_jobListForStat->setModel(m_model_jobListForStat);

    _update_job_list();
}

void MainWindow::on_pushButton_removeJob_clicked()
{
    if (m_jobList.count() <= 0) {
        return;
    }

    if (QMessageBox::warning(this, tr("경고"), tr("정말 삭제 하시겠습니까?"), QMessageBox::Ok,
                             QMessageBox::Cancel) != QMessageBox::Ok) {
        return;
    }

    QModelIndex currentIndex = ui->tableView_jobListForStat->currentIndex();
    QString blNum = m_model_jobListForStat->companyBlNum(currentIndex);
    QString rrNum = m_model_jobListForStat->workerRRNum(currentIndex);
    QDate date = m_model_jobListForStat->workDate(currentIndex);

    if (!m_dbHdlr->removeJob(blNum, rrNum, date)) {
        return;
    }

    _load_job_list(m_jobList);
    m_model_jobListForStat->refresh();

    ui->tableView_jobListForStat->reset();
    ui->tableView_jobListForStat->setModel(m_model_jobListForStat);

    _update_job_list();
}

void MainWindow::on_pushButton_refreshJobjist_clicked()
{
    _update_job_list_for_stat();
}

void MainWindow::on_pushButton_refreshJobListForCompany_clicked()
{
    _update_job_list_for_company();
}

void MainWindow::on_dateEdit_stat_from_editingFinished()
{
    _update_job_list_for_stat();
}

void MainWindow::on_dateEdit_stat_to_editingFinished()
{
    _update_job_list_for_stat();
}

void MainWindow::on_dateEdit_company_from_editingFinished()
{
    _update_job_list_for_company();
}

void MainWindow::on_dateEdit_company_to_editingFinished()
{
    _update_job_list_for_company();
}

void MainWindow::on_dateEdit_worker_from_editingFinished()
{
    _update_job_list_for_worker();
}

void MainWindow::on_dateEdit_worker_to_editingFinished()
{
    _update_job_list_for_worker();
}

void MainWindow::on_pushButton_refreshJobListForWorker_clicked()
{
    _update_job_list_for_worker();
}

void MainWindow::on_pushButton_editApply_clicked()
{
    QString name = ui->lineEdit_workerName->text();
    QString majorStr = ui->lineEdit_workerMajor->text();
    QString rrNum = ui->lineEdit_workerRRNum->text();
    QString phoneNum = ui->lineEdit_workerPhoneNum->text();
    QString address = ui->textEdit_workerAddress->toPlainText();
    QString account = ui->lineEdit_workerAccount->text();
    QString payStr = ui->lineEdit_workerPay->text();
    int pay = 0;

    bool ok;
    pay = payStr.toInt(&ok);
    if (!ok) {
        pay = 0;
    }

    if (!m_dbHdlr->updateWorker(rrNum, name, majorStr, phoneNum, address, account, pay, "")) {
        QMessageBox::critical(this, tr("Error"), tr("Cannot update worker data!!"), tr("Ok"));
        return;
    }

    _load_worker_list(m_workerList);
    m_model_worker->refresh();

    ui->listView_worker->reset();
    ui->listView_worker->setModel(m_model_worker);

    _update_job_list();
}

void MainWindow::on_pushButton_companyEditApply_clicked()
{
    QString owner = ui->lineEdit_companyOwner->text();
    QString name = ui->lineEdit_companyName->text();
    QString blNum = ui->lineEdit_companyBlNum->text();
    QString phoneNum = ui->lineEdit_companyPhoneNum->text();
    QString address = ui->lineEdit_companyAddress->text();
    QString account = ui->lineEdit_companyAccount->text();

    if (!m_dbHdlr->updateCompany(blNum, name, address, owner, account, phoneNum)) {
        QMessageBox::critical(this, tr("Error"), tr("Cannot update company data!!"), tr("Ok"));
        return;
    }

    _load_company_list(m_companyList);
    m_model_company->refresh();

    ui->listView_company->reset();
    ui->listView_company->setModel(m_model_company);

    _update_job_list();
}

void MainWindow::on_pushButton_exportJobListForWorker_clicked()
{
    QString curDir = QDir::currentPath();

    // get save file path
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save file"), curDir, tr("Excel files (*.xlsx)"));
    if (!filePath.length()) {
        return;
    }

    // export
    m_model_jobListForWorker->exportToExcelFile(filePath);
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

void MainWindow::_update_job_list_for_stat()
{
    QDate dateFrom = ui->dateEdit_stat_from->date();
    QDate dateTo = ui->dateEdit_stat_to->date();

    m_model_jobListForStat->setPeriod(dateFrom, dateTo);
    m_model_jobListForStat->refresh();
}

void MainWindow::_update_job_list_for_company()
{
    QDate dateFrom = ui->dateEdit_company_from->date();
    QDate dateTo = ui->dateEdit_company_to->date();

    m_model_jobListForCompany->setPeriod(dateFrom, dateTo);
    m_model_jobListForCompany->refresh();
}

void MainWindow::_update_job_list_for_worker()
{
    QDate dateFrom = ui->dateEdit_worker_from->date();
    QDate dateTo = ui->dateEdit_worker_to->date();

    m_model_jobListForWorker->setPeriod(dateFrom, dateTo);
    m_model_jobListForWorker->refresh();
}

void MainWindow::_load_job_list(QList<Job> &listValue)
{
    listValue.clear();
    if (!m_dbHdlr->getJobList(listValue)) {
        QMessageBox::critical(this, tr("Error"), tr("업무 데이터를 읽을 수 없습니다."), tr("Ok"));
        return;
    }
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
    ui->dateEdit_company_from->setDate(dateFrom);
    ui->dateEdit_company_to->setDate(dateTo);
    ui->dateEdit_worker_from->setDate(dateFrom);
    ui->dateEdit_worker_to->setDate(dateTo);
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

void MainWindow::_refreshAllData()
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

    _update_job_list();
}

void MainWindow::_update_job_list()
{
    _update_job_list_for_stat();
    _update_job_list_for_company();
    _update_job_list_for_worker();
}
