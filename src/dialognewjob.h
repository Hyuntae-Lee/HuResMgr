#ifndef DIALOGNEWJOB_H
#define DIALOGNEWJOB_H

#include <QDialog>
#include "worker.h"
#include "company.h"
#include "job.h"

namespace Ui {
class DialogNewJob;
}

class QStringListModel;
class DialogNewJob : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewJob(QList<Worker> &workerList, QList<Company> &companyList);
    ~DialogNewJob();

public:
    bool getJob(Job* out_job);

private:
    void _init_worker_list();
    void _init_company_list();

private:
    Ui::DialogNewJob *ui;
    QStringListModel* m_model_workerList;
    QStringListModel* m_model_companyList;
    QList<Worker> m_workerList;
    QList<Company> m_companyList;
};

#endif // DIALOGNEWJOB_H
