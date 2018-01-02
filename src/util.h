#ifndef UTIL_H
#define UTIL_H

#include "job.h"
#include "worker.h"
#include "company.h"

class Util
{
public:
    Util();

public:
    static QString findCompanyNameWithBlNum(QList<Company> list, QString blNum);
    static long long findWorkerPayWithRRNum(QList<Worker> list, QString rrNum);
    static QString findWorkerNameWithRRNum(QList<Worker> list, QString rrNum);
    static int findWorkerIdWithRRNum(QList<Worker> list, QString rrNum);
    static bool jobListForWorker(QList<Job>& out_list, QList<Job>& list, QString rrNum);
};

#endif // UTIL_H
