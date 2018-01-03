#include "joblisttablemodelforworker.h"
#include "util.h"
#include <QMessageBox>
#include <QDir>
#include "xlsxdocument.h"
#include <QDesktopServices>
#include <QProcess>
#include <QUrl>
#include <QFileDialog>

#define EXPORT_TEMPLATE_PATH_STAT "/data/report_template.xlsx"

static JobListTableModelForWorker::ModelItem_t s_model_item[] = {
    /*                    idx                    , label , size */
    { JobListTableModelForWorker::COL_NO         , "순번", 50   },
    { JobListTableModelForWorker::COL_DATE       , "일자", 100  },
    { JobListTableModelForWorker::COL_COMPANYNAME, "업체", 150  },
    { JobListTableModelForWorker::COL_PAY        , "일당", 150  },
};

JobListTableModelForWorker::JobListTableModelForWorker(QList<Job> &jobList, QList<Worker>& workerList, QList<Company>& companyList)
    : m_jobList(jobList), m_workerList(workerList), m_companyList(companyList)
{
}

void JobListTableModelForWorker::setWorker(QString rrNum)
{
    m_workerRRNum = rrNum;
}

void JobListTableModelForWorker::setPeriod(QDate& from, QDate& to)
{
    if (from > to) {
        return;
    }

    m_dateFrom = from;
    m_dateTo = to;
}

int JobListTableModelForWorker::columnSize(ModelItemColumnIdx idx)
{
    return s_model_item[idx].width;
}

void JobListTableModelForWorker::refresh()
{
    m_itemList.clear();
    foreach (Job job, m_jobList) {
        if (job.workerRRNum() != m_workerRRNum) {
            continue;
        }

        if (!(job.date() >= m_dateFrom && job.date() <= m_dateTo)) {
            continue;
        }

        QString companyName = Util::findCompanyNameWithBlNum(m_companyList, job.companyBlNum());
        long long pay = Util::findWorkerPayWithRRNum(m_workerList, job.workerRRNum());
        QDate date = job.date();

        JobListTableModelForWorkerItem item;
        item.setId(job.id());
        item.setCompanyName(companyName);
        item.setPay(pay);
        item.setDate(date);

        m_itemList.append(item);
    }

    emit layoutChanged();
}

void JobListTableModelForWorker::exportToExcelFile()
{
#ifndef QT_DEBUG
    QString curPath = QDir::currentPath();
#else
    QString curPath = "D:/projects/etc/HuResMgr";
#endif // QT_DEBUG

    // perpare contents
    QString workerName = Util::findWorkerNameWithRRNum(m_workerList, m_workerRRNum);
    QString dateStrFrom = m_dateFrom.toString(Qt::DefaultLocaleShortDate);
    QString dateStrTo = m_dateTo.toString(Qt::DefaultLocaleShortDate);
    QString title = QString("%1 업무내역 (%2 ~ %3)").arg(workerName).arg(dateStrFrom).arg(dateStrTo);

    // save to excel file

    // - get save directory
    QString newFilePathDefault = QDir::homePath() + "/" + title + ".xlsx";
    QString newFilePath = QFileDialog::getSaveFileName(NULL, tr("저장할 폴더 선택"), newFilePathDefault, tr("Excel File (*.xlsx)"));
    if (!newFilePath.length()) {
        return;
    }
    // - copy template file to home directory
    QString templatePath = curPath + EXPORT_TEMPLATE_PATH_STAT;
    if (!QFile::copy(templatePath, newFilePath)) {
        QMessageBox::critical(NULL, tr("Error"), tr("Cannot save template file!!"), tr("Ok"));
        return;
    }

    // - open new file
    QXlsx::Document xlsx(newFilePath);

    // title
    xlsx.write(1, 1, title);
    // - header
    for (int col = 0; col < columnCount(); col++) {
        int excel_col = col + 1;
        QString headerStr = s_model_item[col].label;
        xlsx.write(2, excel_col, headerStr);
    }
    // - contents
    for (int row = 0; row < rowCount(); row ++) {
        for (int col = 0; col < columnCount(); col++) {
            QString strTmp = _getItemData(row, col);

            int excel_row = row + 3;
            int excel_col = col + 1;
            xlsx.write(excel_row, excel_col, strTmp);
        }
    }
    // - save to file
    xlsx.saveAs(newFilePath);

    // - open file
    QDesktopServices::openUrl(QUrl(newFilePath.prepend("file:///")));
}

QVariant JobListTableModelForWorker::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        if (section >= COL_NUM) {
            return QVariant();
        }

        return s_model_item[section].label;
    }
    else {
        return QVariant();
    }
}

int JobListTableModelForWorker::rowCount(const QModelIndex &) const
{
    return m_itemList.count();
}

int JobListTableModelForWorker::columnCount(const QModelIndex &) const
{
    return COL_NUM;
}

QVariant JobListTableModelForWorker::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignCenter | Qt::AlignVCenter);
    }

    if (role == Qt::DisplayRole) {
        return _getItemData(index.row(), index.column());
    }

    return QVariant();
}

QString JobListTableModelForWorker::_getItemData(int row, int col) const
{
    JobListTableModelForWorkerItem item = m_itemList[row];

    if (col == COL_NO) {
        return QString("%1").arg(item.id());
    }
    else if (col == COL_DATE) {
        return item.date().toString(Qt::DefaultLocaleLongDate);
    }
    else if (col == COL_COMPANYNAME) {
        return item.companyName();
    }
    else if (col == COL_PAY) {
        return QString("%1").arg(item.pay());
    }
    else {
        return "";
    }
}
