#include "dialognewjob.h"
#include "ui_dialognewjob.h"
#include <QStringListModel>
#include "workerlistmodelfornewjob.h"
#include "companylistmodelfornewjob.h"

DialogNewJob::DialogNewJob(QList<Worker> &workerList, QList<Company> &companyList) :
    ui(new Ui::DialogNewJob)
{
    ui->setupUi(this);

    m_model_workerList = new WorkerListModelForNewJob(m_workerList);
    m_model_companyList = new CompanyListModelForNewJob(m_companyList);
    m_workerList.append(workerList);
    m_companyList.append(companyList);

    ui->listView_newJob_worker->setModel(m_model_workerList);
    ui->listView_newJob_company->setModel(m_model_companyList);
}

DialogNewJob::~DialogNewJob()
{
    delete m_model_workerList;
    delete m_model_companyList;
    delete ui;
}

bool DialogNewJob::getJob(QList<Job>& out_jobList)
{
    QModelIndexList companyIdxList = ui->listView_newJob_company->selectionModel()->selectedIndexes();
    QModelIndexList workerIdxList = ui->listView_newJob_worker->selectionModel()->selectedIndexes();

    QString blNum = m_model_companyList->blNum(companyIdxList.first());
    QDate date = ui->calendarWidget_newJob_date->selectedDate();
    QStringList workerRRNumList;
    foreach (QModelIndex index, workerIdxList) {
        QString rrNum = m_model_workerList->rrNum(index);
        workerRRNumList.append(rrNum);
    }

    for (int i = 0; i < workerRRNumList.count(); i++) {
        Job job;

        job.setCompanyBlNum(blNum);
        job.setDate(date);
        job.setWorkerRRNum(workerRRNumList[i]);

        out_jobList.append(job);
    }

    return true;
}
