#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "worker.h"
#include "company.h"
#include "job.h"

namespace Ui {
class MainWindow;
}

class DBHdlr;
class CompanyListModel;
class WorkerListModel;
class JobListTableModelForCompany;
class JobListTableModelForWorker;
class JobListTableModelForStat;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_refreshAllData_clicked();
    void on_pushButton_addWorker_clicked();
    void on_pushButton_removeWorker_clicked();
    void on_listView_worker_clicked(const QModelIndex &index);
    void on_pushButton_newCompany_clicked();
    void on_pushButton_removeCompany_clicked();
    void on_listView_company_clicked(const QModelIndex &index);
    void on_pushButton_addJob_clicked();
    void on_pushButton_removeJob_clicked();
    void on_pushButton_refreshJobjist_clicked();
    void on_pushButton_refreshJobListForCompany_clicked();
    void on_dateEdit_stat_from_editingFinished();
    void on_dateEdit_stat_to_editingFinished();
    void on_dateEdit_company_from_editingFinished();
    void on_dateEdit_company_to_editingFinished();
    void on_dateEdit_worker_from_editingFinished();
    void on_dateEdit_worker_to_editingFinished();
    void on_pushButton_refreshJobListForWorker_clicked();
    void on_pushButton_editApply_clicked();
    void on_pushButton_companyEditApply_clicked();
    void on_pushButton_exportJobListForWorker_clicked();
    void on_pushButton_exportForStat_clicked();
    void on_pushButton_exportJobListForCompany_clicked();
    void on_pushButton_about_clicked();
    void on_pushButton_aboutQt_clicked();

private:
    void _load_worker_list(QList<Worker> &listValue);
    void _load_company_list(QList<Company> &listValue);
    void _update_job_list_for_stat();
    void _update_job_list_for_company();
    void _update_job_list_for_worker();
    void _load_job_list(QList<Job> &listValue);
    void _init_jobListPeriod();
    void _init_uiSizes();
    void _refreshAllData();
    void _update_job_list();

private:
    Ui::MainWindow *ui;
    DBHdlr* m_dbHdlr;
    WorkerListModel* m_model_worker;
    CompanyListModel* m_model_company;
    JobListTableModelForCompany* m_model_jobListForCompany;
    JobListTableModelForWorker* m_model_jobListForWorker;
    JobListTableModelForStat* m_model_jobListForStat;
    QList<Worker> m_workerList;
    QList<Company> m_companyList;
    QList<Job> m_jobList;
};

#endif // MAINWINDOW_H
