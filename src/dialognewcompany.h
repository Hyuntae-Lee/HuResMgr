#ifndef DIALOGNEWCOMPANY_H
#define DIALOGNEWCOMPANY_H

#include <QDialog>

namespace Ui {
class DialogNewCompany;
}

class Company;
class DialogNewCompany : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewCompany(QWidget *parent = 0);
    ~DialogNewCompany();

public:
    bool getCompanyInfo(Company* company);

private:
    Ui::DialogNewCompany *ui;
};

#endif // DIALOGNEWCOMPANY_H
