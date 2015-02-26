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

#include "kalarmitemwidget.h"

KAlarmItemWidget::KAlarmItemWidget(QWidget *parent) : QWidget(parent)
{
    _alarmEnabledCheck = new QCheckBox;
    _startTimeLabel = new QLabel;
    _alarmConditionLabel = new QLabel;

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(_alarmEnabledCheck, 1);
    mainLayout->addWidget(_startTimeLabel, 1);
    mainLayout->addWidget(_alarmConditionLabel, 4);

    setLayout(mainLayout);

    connect(_alarmEnabledCheck, SIGNAL(toggled(bool)),
            this, SIGNAL(alarmEnabledToggled(bool)));
}

KAlarmItemWidget::~KAlarmItemWidget()
{

}

bool KAlarmItemWidget::isAlarmEnabled() const
{
    return _alarmEnabledCheck->isChecked();
}

void KAlarmItemWidget::setAlarmEnabled(bool enabled)
{
    _alarmEnabledCheck->setChecked(enabled);
}

QString KAlarmItemWidget::name() const
{
    return _name;
}

void KAlarmItemWidget::setName(const QString &name)
{
    _name = name;

    _alarmEnabledCheck->setText(_name);
}

QTime KAlarmItemWidget::startTime() const
{
    return _startTime;
}

void KAlarmItemWidget::setStartTime(const QTime &startTime)
{
    _startTime = startTime;

    _startTimeLabel->setText(_startTime.toString("HH:mm"));
}

KAlarmItemWidget::KAlarmType KAlarmItemWidget::alarmType() const
{
    return _alarmType;
}

void KAlarmItemWidget::setAlarmType(
        const KAlarmItemWidget::KAlarmType &alarmType)
{
    _alarmType = alarmType;
}

QTime KAlarmItemWidget::intervalTime() const
{
    return _intervalTime;
}

void KAlarmItemWidget::setIntervalTime(const QTime &intervalTime)
{
    _intervalTime = intervalTime;
}

bool KAlarmItemWidget::isWeekDayEnabled(KAlarmItemWidget::KWeekDay weekDay)
        const
{
    return _weekDaysMap.value(weekDay);
}

void KAlarmItemWidget::setWeekDayEnabled(KAlarmItemWidget::KWeekDay weekDay,
                                         bool enabled)
{
    _weekDaysMap.insert(weekDay, enabled);

    _alarmConditionLabel->setText(weekDaysToString());
}

QString KAlarmItemWidget::weekDaysToString() const
{
    QString s;

    if (isWeekDayEnabled(Monday))
        s.append(tr("Mon")).append(" ");

    if (isWeekDayEnabled(Tuesday))
        s.append(tr("Tue")).append(" ");

    if (isWeekDayEnabled(Wednesday))
        s.append(tr("Wed")).append(" ");

    if (isWeekDayEnabled(Thursday))
        s.append(tr("Thu")).append(" ");

    if (isWeekDayEnabled(Friday))
        s.append(tr("Fri")).append(" ");

    if (isWeekDayEnabled(Saturday))
        s.append(tr("Sat")).append(" ");

    if (isWeekDayEnabled(Sunday))
        s.append(tr("Sun"));

    return s;
}

KAlarmItemWidget::KWeekDay KAlarmItemWidget::numToWeekDay(int n)
{
    // 1 to Monday
    // ...
    // 7 to Sunday
    return static_cast<KWeekDay>(n - 1);
}
