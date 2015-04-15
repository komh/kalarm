#-------------------------------------------------
#
# Project created by QtCreator 2015-01-20T14:52:30
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KAlarm
TEMPLATE = app


SOURCES += main.cpp\
        kalarm.cpp \
    kalarmitemwidget.cpp \
    kalarmconfigdialog.cpp \
    kalarmqueue.cpp

HEADERS  += kalarm.h \
    kalarmitemwidget.h \
    kalarmconfigdialog.h \
    kalarmqueue.h

FORMS    += kalarm.ui

RESOURCES += \
    kalarm.qrc

win32: RC_ICONS = kalarm_win32.ico

DISTFILES += \
    kalarm_win32.ico
