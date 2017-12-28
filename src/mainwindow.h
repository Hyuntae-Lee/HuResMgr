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
class QStringListModel;
class WorkerListModel;
class JobListTableModelForWorker;
class JobListTableModelForStat;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_connectDB_clicked();
    void on_pushButton_newHR_clicked();
    void on_pushButton_removeWorker_clicked();
    void on_listView_worker_clicked(const QModelIndex &index);
    void on_pushButton_newCompany_clicked();
    void on_listView_company_clicked(const QModelIndex &index);
    void on_pushButton_workNew_clicked();

private:
    void _load_worker_list(QList<Worker> &listValue);
    void _update_company_list(QList<Company> listValue);
    void _load_company_list(QList<Company> &listValue);
    void _update_job_list(QList<Job>);
    void _load_job_list(QList<Job> &listValue);
    QString _companyLabelStr(QString blNum);
    QString _workerNameStr(QString rrNum);

    void _init_jobListPeriod();
    void _init_uiSizes();

private:
    Ui::MainWindow *ui;
    DBHdlr* m_dbHdlr;
    WorkerListModel* m_model_worker;
    QStringListModel* m_model_company;
    JobListTableModelForWorker* m_model_jobListForWorker;
    JobListTableModelForStat* m_model_jobListForStat;
    QList<Worker> m_workerList;
    QList<Company> m_companyList;
    QList<Job> m_jobList;
};

#endif // MAINWINDOW_H
