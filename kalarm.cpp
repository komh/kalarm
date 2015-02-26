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

#include "kalarm.h"
#include "ui_kalarm.h"

#include <QtWidgets>

#include "kalarmconfigdialog.h"
#include "kalarmitemwidget.h"

KAlarm::KAlarm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::KAlarm)
{
    ui->setupUi(this);

    QPushButton *addButton = new QPushButton(tr("&Add"));
    QPushButton *modifyButton = new  QPushButton(tr("&Modify"));
    QPushButton *deleteButton = new QPushButton(tr("&Delete"));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(modifyButton);
    buttonLayout->addWidget(deleteButton);

    _listWidget = new QListWidget;

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addLayout(buttonLayout);
    vlayout->addWidget(_listWidget);

    centralWidget()->setLayout(vlayout);

    connect(addButton, SIGNAL(clicked()), this, SLOT(addItem()));
    connect(modifyButton, SIGNAL(clicked()), this, SLOT(modifyItem()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
}

KAlarm::~KAlarm()
{
    delete ui;
}

static void configDialogToItemWidget(const KAlarmConfigDialog &configDialog,
                                     KAlarmItemWidget *itemWidget)
{
    itemWidget->setName(configDialog.name());
    itemWidget->setStartTime(QTime(configDialog.startTime().hour(),
                                   configDialog.startTime().minute()));
    itemWidget->setIntervalTime(QTime(configDialog.intervalTime().hour(),
                                      configDialog.intervalTime().minute()));

    itemWidget->setWeekDayEnabled(KAlarmItemWidget::Monday,
                                  configDialog.isMondayChecked());

    itemWidget->setWeekDayEnabled(KAlarmItemWidget::Tuesday,
                                  configDialog.isTuesdayChecked());

    itemWidget->setWeekDayEnabled(KAlarmItemWidget::Wednesday,
                                  configDialog.isWednesdayChecked());

    itemWidget->setWeekDayEnabled(KAlarmItemWidget::Thursday,
                                  configDialog.isThursdayChecked());

    itemWidget->setWeekDayEnabled(KAlarmItemWidget::Friday,
                                  configDialog.isFridayChecked());

    itemWidget->setWeekDayEnabled(KAlarmItemWidget::Saturday,
                                  configDialog.isSaturdayChecked());

    itemWidget->setWeekDayEnabled(KAlarmItemWidget::Sunday,
                                  configDialog.isSundayChecked());

    KAlarmItemWidget::KAlarmType alarmType;

    if (configDialog.isUseIntervalChecked())
        alarmType = KAlarmItemWidget::IntervalAlarm;
    else if (itemWidget->weekDaysToString().isEmpty())
        alarmType = KAlarmItemWidget::SingleShotAlarm;
    else
        alarmType = KAlarmItemWidget::WeeklyAlarm;

    itemWidget->setAlarmType(alarmType);
}

void KAlarm::addItem()
{
    KAlarmConfigDialog configDialog;

    if (configDialog.exec() == QDialog::Accepted)
    {
        KAlarmItemWidget *itemWidget = new KAlarmItemWidget;

        configDialogToItemWidget(configDialog, itemWidget);

        itemWidget->setAlarmEnabled(true);

        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint(QSize(itemWidget->sizeHint()));

        _listWidget->addItem(item);
        _listWidget->setItemWidget(item, itemWidget);

        _alarmQueue.add(itemWidget);
    }
}

void KAlarm::modifyItem()
{
    KAlarmConfigDialog configDialog;

    QListWidgetItem *item= _listWidget->currentItem();
    if (!item)
        return;

    KAlarmItemWidget *itemWidget =
            qobject_cast<KAlarmItemWidget *>(_listWidget->itemWidget(item));
    configDialog.setName(itemWidget->name());
    configDialog.setStartTime(itemWidget->startTime());
    configDialog.setUseIntervalChecked(itemWidget->alarmType()
                                        ==  KAlarmItemWidget::IntervalAlarm);
    configDialog.setIntervalTime(itemWidget->intervalTime());
    configDialog.setMondayChecked(
                itemWidget->isWeekDayEnabled(KAlarmItemWidget::Monday));
    configDialog.setTuesdayChecked(
                itemWidget->isWeekDayEnabled(KAlarmItemWidget::Tuesday));
    configDialog.setWednesdayChecked(
                itemWidget->isWeekDayEnabled(KAlarmItemWidget::Wednesday));
    configDialog.setThursdayChecked(
                itemWidget->isWeekDayEnabled(KAlarmItemWidget::Thursday));
    configDialog.setFridayChecked(
                itemWidget->isWeekDayEnabled(KAlarmItemWidget::Friday));
    configDialog.setSaturdayChecked(
                itemWidget->isWeekDayEnabled(KAlarmItemWidget::Saturday));
    configDialog.setSundayChecked(
                itemWidget->isWeekDayEnabled(KAlarmItemWidget::Sunday));

    if (configDialog.exec() == QDialog::Accepted)
    {
        configDialogToItemWidget(configDialog, itemWidget);

        _alarmQueue.modify(itemWidget);
    }
}

void KAlarm::deleteItem()
{
    QListWidgetItem *item = _listWidget->currentItem();
    if (item)
    {
        _alarmQueue.remove(qobject_cast<KAlarmItemWidget *>
                                (_listWidget->itemWidget(item)));

        int row = _listWidget->currentRow();

        _listWidget->removeItemWidget(item);
        delete _listWidget->takeItem(row);
    }
}
