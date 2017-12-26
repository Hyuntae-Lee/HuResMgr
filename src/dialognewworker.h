#ifndef DIALOGNEWWORKER_H
#define DIALOGNEWWORKER_H

#include <QDialog>

namespace Ui {
class DialogNewWorker;
}

class Worker;
class DialogNewWorker : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewWorker(QWidget *parent = 0);
    ~DialogNewWorker();
    bool getWorkInfo(Worker* worker);

private:
    Ui::DialogNewWorker *ui;
};

#endif // DIALOGNEWWORKER_H
