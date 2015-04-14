/****************************************************************************
**
** KAlarm, main class of K Alarm
**
** Copyright (C) 2015 by KO Myung-Hun
** All rights reserved.
** Contact: KO Myung-Hun (komh@chollian.net)
**
** This file is part of K Alarm
**
** $BEGIN_LICENSE$
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** $END_LICENSE$
**
****************************************************************************/

#ifndef KALARM_H
#define KALARM_H

#include <QMainWindow>

#include <QtWidgets>

#include "kalarmqueue.h"

namespace Ui {
class KAlarm;
}

class KAlarm : public QMainWindow
{
    Q_OBJECT

public:
    explicit KAlarm(QWidget *parent = 0);
    ~KAlarm();

    static QString organization() { return tr("KO Myung-Hun"); }
    static QString title() { return tr("K Alarm"); }
    static QString version() { return tr("1.0.0"); }

protected:
    bool event(QEvent *e);
    void closeEvent(QCloseEvent *e);

private:
    Ui::KAlarm *ui;

    QListWidget *_listWidget;
    KAlarmQueue _alarmQueue;

    QMenu *_fileMenu;
    QMenu *_helpMenu;

    QMenu *_trayIconMenu;
    QSystemTrayIcon *_trayIcon;

private slots:
    void addItem();
    void modifyItem(const QModelIndex &index = QModelIndex());
    void deleteItem();

    void itemWidgetAlarmEnabledToggled(bool enabled);

    void saveAlarmItems() const;
    void loadAlarmItems();

    void about();
    void aboutQt();

    void openKAlarm();
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
};

#endif // KALARM_H
