#include "dialogdatepicker.h"
#include "ui_dialogdatepicker.h"
#include <QStringListModel>

DialogDatePicker::DialogDatePicker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDatePicker)
{
    m_model_selectedDates = new QStringListModel;

    ui->setupUi(this);

    ui->listView_selectedDates->setModel(m_model_selectedDates);
}

DialogDatePicker::~DialogDatePicker()
{
    delete m_model_selectedDates;
    delete ui;
}

bool DialogDatePicker::getSelectedDates(QList<QDate>& list)
{
    if (!m_clickedDateList.count()) {
        return false;
    }

    list.append(m_clickedDateList);
    return true;
}

void DialogDatePicker::on_calendarWidget_clicked(const QDate &date)
{
    foreach(QDate d, m_clickedDateList) {
        if (d.year() == date.year() && d.month() == date.month() && d.day() == date.day()) {
            return;
        }
    }

    m_clickedDateList.append(date);

    _update_date_list();
}

void DialogDatePicker::_update_date_list()
{
    QStringList dateStrList;
    foreach(QDate d, m_clickedDateList) {
        dateStrList.append(d.toString(Qt::DefaultLocaleLongDate));
    }

    m_model_selectedDates->setStringList(dateStrList);
}
