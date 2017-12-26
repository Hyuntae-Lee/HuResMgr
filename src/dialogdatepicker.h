#ifndef DIALOGDATEPICKER_H
#define DIALOGDATEPICKER_H

#include <QDialog>

namespace Ui {
class DialogDatePicker;
}

class QStringListModel;
class DialogDatePicker : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDatePicker(QWidget *parent = 0);
    ~DialogDatePicker();

public:
    bool getSelectedDates(QList<QDate>& list);

private slots:
    void on_calendarWidget_clicked(const QDate &date);

private:
    void _update_date_list();

private:
    Ui::DialogDatePicker *ui;
    QList<QDate> m_clickedDateList;
    QStringListModel* m_model_selectedDates;
};

#endif // DIALOGDATEPICKER_H
