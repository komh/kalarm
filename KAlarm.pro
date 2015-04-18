#-------------------------------------------------
#
# Project created by QtCreator 2015-01-20T14:52:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets multimedia
    DEFINES += CONFIG_QT5
}

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

TRANSLATIONS = translations/kalarm_ko.ts

lrelease.input = TRANSLATIONS
lrelease.output = ${OBJECTS_DIR}/${QMAKE_FILE_BASE}.qm
lrelease.commands = lrelease ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_OUT}
lrelease.CONFIG += no_link target_predeps
QMAKE_EXTRA_COMPILERS += lrelease

win32: RC_ICONS = kalarm_win32.ico
os2: RC_FILE = kalarm_os2.rc

DISTFILES += \
    kalarm_win32.ico

OTHER_FILES += \
    kalarm_os2.rc \
    kalarm_os2.ico
