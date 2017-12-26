#include "dialognewjob.h"
#include "ui_dialognewjob.h"
#include <QStringListModel>

DialogNewJob::DialogNewJob(QList<Worker> &workerList, QList<Company> &companyList) :
    ui(new Ui::DialogNewJob)
{
    ui->setupUi(this);

    m_model_workerList = new QStringListModel;
    m_model_companyList = new QStringListModel;
    m_workerList.append(workerList);
    m_companyList.append(companyList);

    ui->listView_newJob_worker->setModel(m_model_workerList);
    ui->listView_newJob_company->setModel(m_model_companyList);

    _init_worker_list();
    _init_company_list();
}

DialogNewJob::~DialogNewJob()
{
    delete m_model_workerList;
    delete m_model_companyList;
    delete ui;
}

bool DialogNewJob::getJob(Job* out_job)
{
    if (!out_job) {
        return false;
    }

    int companyIdx = ui->listView_newJob_company->currentIndex().row();
    int workerIdx = ui->listView_newJob_worker->currentIndex().row();
    QDate date = ui->calendarWidget_newJob_date->selectedDate();

    out_job->setCompanyBlNum(m_companyList[companyIdx].blNum());
    out_job->setWorkerRRNum(m_workerList[workerIdx].rrNum());
    out_job->setDate(date);

    return true;
}

void DialogNewJob::_init_worker_list()
{
    QStringList itemList;
    foreach(Worker worker, m_workerList) {
        QString lableStr = QString("%1(%2)").arg(worker.name()).arg(worker.rrNum());
        itemList.append(lableStr);
    }
    m_model_workerList->setStringList(itemList);
}

void DialogNewJob::_init_company_list()
{
    QStringList itemList;
    foreach(Company company, m_companyList) {
        itemList.append(company.name());
    }
    m_model_companyList->setStringList(itemList);
}
