/****************************************************************************
**
** KAlarmItemWidget, item widget for KAlarm
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

#ifndef KALARMITEMWIDGET_H
#define KALARMITEMWIDGET_H

#include <QWidget>

#include <QtCore>
#include <QtWidgets>

class KAlarmItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KAlarmItemWidget(QWidget *parent = 0);
    ~KAlarmItemWidget();

    bool isAlarmEnabled() const;
    void setAlarmEnabled(bool enabled);

    QString name() const;
    void setName(const QString &name);

    QTime startTime() const;
    void setStartTime(const QTime &startTime);

    enum KAlarmType
    {
        IntervalAlarm = 0,
        WeeklyAlarm,
        SingleShotAlarm
    };

    enum KWeekDay
    {
        FirstDay = 0,
        Monday = 0,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday,
        LastDay = Sunday
    };

    KAlarmType alarmType() const;
    void setAlarmType(const KAlarmType &alarmType);

    QTime intervalTime() const;
    void setIntervalTime(const QTime &intervalTime);

    bool isWeekDayEnabled(KWeekDay weekDay) const;
    void setWeekDayEnabled(KWeekDay weekDay, bool enabled );

    QString weekDaysToString() const;

    static KWeekDay numToWeekDay(int n);

signals:
    void alarmEnabledToggled(bool checked);

private:
    QCheckBox *_alarmEnabledCheck;
    QString _name;

    QLabel *_startTimeLabel;
    QTime _startTime;

    QLabel *_alarmConditionLabel;
    KAlarmType _alarmType;

    QTime _intervalTime;
    QMap<KWeekDay, bool> _weekDaysMap;
};

#endif // KALARMITEMWIDGET_H
