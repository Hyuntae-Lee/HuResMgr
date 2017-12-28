#include "util.h"

Util::Util()
{

}

QString Util::findCompanyNameWithBlNum(QList<Company> list, QString blNum)
{
    foreach (Company company, list) {
        if (company.blNum() != blNum) {
            continue;
        }

        return company.name();
    }

    return "";
}

long long Util::findWorkerPayWithRRNum(QList<Worker> list, QString rrNum)
{
    foreach (Worker worker, list) {
        if (worker.rrNum() != rrNum) {
            continue;
        }

        return worker.pay();
    }

    return 0;
}

QString Util::findWorkerNameWithRRNum(QList<Worker> list, QString rrNum)
{
    foreach (Worker worker, list) {
        if (worker.rrNum() != rrNum) {
            continue;
        }

        return worker.name();
    }

    return 0;
}

bool Util::jobListForWorker(QList<Job>& out_list, QList<Job>& list, QString rrNum)
{
    if (list.count() <= 0) {
        return false;
    }

    foreach (Job job, list) {
        if (job.workerRRNum() != rrNum) {
            continue;
        }

        out_list.append(job);
    }

    return true;
}


