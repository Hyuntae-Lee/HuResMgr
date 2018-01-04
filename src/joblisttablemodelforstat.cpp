#include "joblisttablemodelforstat.h"
#include "xlsxdocument.h"
#include "util.h"
#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>
#include <QMessageBox>

#define EXPORT_TEMPLATE_PATH_STAT "/data/report_template.xlsx"

static JobListTableModelForStat::ModelItem_t s_model_item[] = {
    /*                   idx                   , label , size  */
    { JobListTableModelForStat::COL_DATE       , "일자", 250   },
    { JobListTableModelForStat::COL_COMPANYNAME, "업체", 150   },
    { JobListTableModelForStat::COL_WORKERNAME , "인력", 100   },
    { JobListTableModelForStat::COL_PAY        , "일당", 150   },
};

JobListTableModelForStat::JobListTableModelForStat(QList<Job>& jobList, QList<Worker>& workerList, QList<Company>& companyList)
    : m_jobList(jobList), m_workerList(workerList), m_companyList(companyList)
{

}

void JobListTableModelForStat::setPeriod(QDate& from, QDate& to)
{
    if (from > to) {
        return;
    }

    m_dateFrom = from;
    m_dateTo = to;
}

int JobListTableModelForStat::columnSize(ModelItemColumnIdx idx)
{
    return s_model_item[idx].width;
}

QString JobListTableModelForStat::companyBlNum(const QModelIndex &index)
{
    return m_itemList[index.row()].companyBlNum();
}

QString JobListTableModelForStat::workerRRNum(const QModelIndex &index)
{
    return m_itemList[index.row()].workerRrNum();
}

QDate JobListTableModelForStat::workDate(const QModelIndex &index)
{
    return m_itemList[index.row()].date();
}

void JobListTableModelForStat::refresh()
{
    m_itemList.clear();
    foreach (Job job, m_jobList) {
        if (job.date() >= m_dateFrom && job.date() <= m_dateTo) {

            int id = job.id();
            QString companyName = Util::findCompanyNameWithBlNum(m_companyList, job.companyBlNum());
            QString workerName = Util::findWorkerNameWithRRNum(m_workerList, job.workerRRNum());
            long long pay = Util::findWorkerPayWithRRNum(m_workerList, job.workerRRNum());
            QDate date = job.date();

            JobListTableModelForStatItem item;
            item.setId(id);
            item.setCompanyName(companyName);
            item.setWorkerName(workerName);
            item.setPay(pay);
            item.setDate(date);
            item.setCompanyBlNum(job.companyBlNum());
            item.setWorkerRrNum(job.workerRRNum());

            m_itemList.append(item);
        }
    }

    emit layoutChanged();
}

void JobListTableModelForStat::exportToExcelFile()
{
    // fill and save
    QString title = _getExportTitle();
    QString excelFilePath = _getExportFilePath(title);
    if (!excelFilePath.length()) {
        return;
    }

    _fillExportFile(excelFilePath, title);

    // open
    QDesktopServices::openUrl(QUrl(excelFilePath.prepend("file:///")));
}

QVariant JobListTableModelForStat::headerData(int section, Qt::Orientation orientation, int role) const
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

int JobListTableModelForStat::rowCount(const QModelIndex&) const
{
    return m_itemList.count();
}

int JobListTableModelForStat::columnCount(const QModelIndex&) const
{
    return COL_NUM;
}

QVariant JobListTableModelForStat::data(const QModelIndex &index, int role) const
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

QVariant JobListTableModelForStat::_getItemData(int row, int col) const
{
    JobListTableModelForStatItem item = m_itemList[row];

    if (col == COL_COMPANYNAME) {
        return item.companyName();
    }
    else if (col == COL_WORKERNAME) {
        return item.workerName();
    }
    else if (col == COL_PAY) {
        return item.pay();
    }
    else if (col == COL_DATE) {
        return item.date().toString(Qt::DefaultLocaleLongDate);
    }
    else {
        return "";
    }
}

QString JobListTableModelForStat::_getExportTitle()
{
    QString dateStrFrom = m_dateFrom.toString(Qt::DefaultLocaleShortDate);
    QString dateStrTo = m_dateTo.toString(Qt::DefaultLocaleShortDate);

    return QString("업무내역 (%2 ~ %3)").arg(dateStrFrom).arg(dateStrTo);
}

QString JobListTableModelForStat::_getExportFilePath(QString defaultFileName)
{
#ifndef QT_DEBUG
    QString curPath = QDir::currentPath();
#else
    QString curPath = "D:/projects/etc/HuResMgr";
#endif // QT_DEBUG

    // get save directory
    QString newFilePathDefault = QDir::homePath() + "/" + defaultFileName + ".xlsx";
    QString newFilePath = QFileDialog::getSaveFileName(NULL, tr("저장할 폴더 선택"), newFilePathDefault, tr("Excel File (*.xlsx)"));
    if (!newFilePath.length()) {
        return "";
    }
    if (QFile::exists(newFilePath)) {
        QFile::remove(newFilePath);
    }

    // copy template file to home directory
    QString templatePath = curPath + EXPORT_TEMPLATE_PATH_STAT;
    if (!QFile::copy(templatePath, newFilePath)) {
        QMessageBox::critical(NULL, tr("Error"), tr("Cannot save template file!!"), tr("Ok"));
        return "";
    }

    return newFilePath;
}

void JobListTableModelForStat::_fillExportFile(QString filePath, QString title)
{
    // open file
    QXlsx::Document xlsx(filePath);

    // title
    xlsx.write(1, 1, title);
    // header
    for (int col = 0; col < columnCount(); col++) {
        int excel_col = col + 1;
        QString headerStr = s_model_item[col].label;
        xlsx.write(2, excel_col, headerStr);
    }
    // contents
    for (int row = 0; row < rowCount(); row ++) {
        for (int col = 0; col < columnCount(); col++) {
            QVariant dataTmp = _getItemData(row, col);

            int excel_row = row + 3;
            int excel_col = col + 1;
            xlsx.write(excel_row, excel_col, dataTmp);
        }
    }
    // save
    xlsx.save();
}
