/****************************************************************************
**
** KAlarmQueue, an alarm queue class
**
** Copyright (C) 2015 by KO Myung-Hun
** All rights reserved.
** Contact: KO Myung-Hun (komh@chollian.net)
**
** This file is part of K Alarm.
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

#ifndef KALARMQUEUE_H
#define KALARMQUEUE_H

#include <QObject>

#include <QTimer>
#include <QMap>
#include <QDateTime>

#include "kalarmitemwidget.h"

class KAlarmQueue : public QObject
{
    Q_OBJECT
public:
    explicit KAlarmQueue(QObject *parent = 0);
    ~KAlarmQueue();

    void add(const KAlarmItemWidget *w);
    void remove(const KAlarmItemWidget *w);
    void modify(const KAlarmItemWidget *w);

private:
    QTimer _timer;
    QMap<const KAlarmItemWidget *, QDateTime> _alarmMap;

    QDateTime findNextAlarm(const KAlarmItemWidget *w, const QDateTime &dt,
                            bool inclusive = false);

    void alarm(const KAlarmItemWidget *w, const QDateTime &dt);

private slots:
    void timerTimeout();
};

#endif // KALARMQUEUE_H
