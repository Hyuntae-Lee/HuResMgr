#-------------------------------------------------
#
# Project created by QtCreator 2017-12-14T16:30:29
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HuResMgr
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dbhdlr.cpp \
    worker.cpp \
    dialognewworker.cpp \
    company.cpp \
    dialognewcompany.cpp \
    dialogdatepicker.cpp \
    dialognewjob.cpp \
    job.cpp \
    joblisttablemodelforworker.cpp \
    joblisttablemodelforworkeritem.cpp \
    joblisttablemodelforstat.cpp \
    joblisttablemodelforstatitem.cpp \
    util.cpp \
    workerlistmodelfornewjob.cpp \
    companylistmodelfornewjob.cpp \
    workerlistmodel.cpp \
    companylistmodel.cpp

HEADERS  += mainwindow.h \
    dbhdlr.h \
    worker.h \
    dialognewworker.h \
    company.h \
    dialognewcompany.h \
    dialogdatepicker.h \
    job.h \
    dialognewjob.h \
    joblisttablemodelforworker.h \
    joblisttablemodelforworkeritem.h \
    joblisttablemodelforstat.h \
    joblisttablemodelforstatitem.h \
    util.h \
    workerlistmodelfornewjob.h \
    companylistmodelfornewjob.h \
    workerlistmodel.h \
    companylistmodel.h

FORMS    += mainwindow.ui \
    dialognewworker.ui \
    dialognewcompany.ui \
    dialogdatepicker.ui \
    dialognewjob.ui
