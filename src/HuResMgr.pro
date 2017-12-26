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
    jobhistorytablemodelforworker.cpp \
    jobhistorytablemodelforworkeritem.cpp \
    job.cpp

HEADERS  += mainwindow.h \
    dbhdlr.h \
    worker.h \
    dialognewworker.h \
    company.h \
    dialognewcompany.h \
    dialogdatepicker.h \
    job.h \
    dialognewjob.h \
    jobhistorytablemodelforworker.h \
    jobhistorytablemodelforworkeritem.h

FORMS    += mainwindow.ui \
    dialognewworker.ui \
    dialognewcompany.ui \
    dialogdatepicker.ui \
    dialognewjob.ui
