#ifndef DIALOGNEWJOB_H
#define DIALOGNEWJOB_H

#include <QDialog>
#include "worker.h"
#include "company.h"
#include "job.h"

namespace Ui {
class DialogNewJob;
}

class CompanyListModelForNewJob;
class WorkerListModelForNewJob;
class DialogNewJob : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewJob(QList<Worker> &workerList, QList<Company> &companyList);
    ~DialogNewJob();

public:
    bool getJob(QList<Job>& out_jobList);

private:
    Ui::DialogNewJob *ui;
    WorkerListModelForNewJob* m_model_workerList;
    CompanyListModelForNewJob* m_model_companyList;
    QList<Worker> m_workerList;
    QList<Company> m_companyList;
};

#endif // DIALOGNEWJOB_H
