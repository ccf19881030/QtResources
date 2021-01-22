#-------------------------------------------------
#
# Project created by QtCreator 2017-02-15T11:06:55
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = client
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    worker_log.cpp \
    worker_init.cpp \
    deal_user.cpp \
    user_init.cpp \
    user_close.cpp \
    user_save_money.cpp \
    user_getmoney.cpp \
    user_tranaccounts.cpp \
    user_lookmoney.cpp \
    user_changepassward.cpp \
    user_account_detail.cpp \
    bankbook.cpp \
    user_tranrecord.cpp \
    record.cpp

HEADERS  += widget.h \
    worker_log.h \
    worker_init.h \
    connect.h \
    deal_user.h \
    user_init.h \
    user_close.h \
    user_save_money.h \
    user_getmoney.h \
    user_tranaccounts.h \
    user_lookmoney.h \
    user_changepassward.h \
    user_account_detail.h \
    bankbook.h \
    user_tranrecord.h \
    record.h

FORMS    += widget.ui \
    logging.ui \
    init_worker.ui \
    deal_user.ui \
    user_init.ui \
    user_close.ui \
    user_save_money.ui \
    user_getmoney.ui \
    user_tranaccounts.ui \
    user_lookmoney.ui \
    user_changepassward.ui \
    user_account_detail.ui \
    bankbook.ui \
    user_tranrecord.ui \
    record.ui

RESOURCES += \
    res.qrc
QT        += network
QT        += sql
