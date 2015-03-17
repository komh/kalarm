/****************************************************************************
**
** KAlarmConfigDialog, a configuration dialog for KAlarm
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

#include "kalarmconfigdialog.h"

#include <QtWidgets>

KAlarmConfigDialog::KAlarmConfigDialog(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f)
{
    // Initialize and place widgets
    _nameLabel = new QLabel(tr("Name:"));
    _nameLine = new QLineEdit(tr("Alarm"));
    _startTimeLabel = new QLabel(tr("Start time:"));
    _startTimeEdit = new QTimeEdit(QTime::currentTime());
    _useIntervalCheck = new QCheckBox(tr("Use interval alarm"));
    _intervalTimeLabel = new QLabel(tr("Interval time:"));
    _intervalTimeEdit = new QTimeEdit;

    _mondayCheck = new QCheckBox(tr("MON"));
    _tuesdayCheck= new QCheckBox(tr("TUE"));
    _wednesdayCheck = new QCheckBox(tr("WED"));
    _thursdayCheck = new QCheckBox(tr("THU"));
    _fridayCheck = new QCheckBox(tr("FRI"));
    _saturdayCheck = new QCheckBox(tr("SAT"));
    _sundayCheck = new QCheckBox(tr("SUN"));


    QHBoxLayout *repeatTimeLayout = new QHBoxLayout;
    repeatTimeLayout->addWidget(_mondayCheck);
    repeatTimeLayout->addWidget(_tuesdayCheck);
    repeatTimeLayout->addWidget(_wednesdayCheck);
    repeatTimeLayout->addWidget(_thursdayCheck);
    repeatTimeLayout->addWidget(_fridayCheck);
    repeatTimeLayout->addWidget(_saturdayCheck);
    repeatTimeLayout->addWidget(_sundayCheck);

    _repeatTimeGroup = new QGroupBox(tr("Weekly alarm"));
    _repeatTimeGroup->setLayout(repeatTimeLayout);

    QPushButton *okButton = new QPushButton(tr("OK"));
    QPushButton *cancelButton = new QPushButton(tr("Cancel"));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(_nameLabel, _nameLine);
    formLayout->addRow(_startTimeLabel, _startTimeEdit);
    formLayout->addRow(_useIntervalCheck);
    formLayout->addRow(_intervalTimeLabel, _intervalTimeEdit);
    formLayout->addRow(_repeatTimeGroup);
    formLayout->addRow(buttonLayout);

    // Disable resizing of a dialog
    formLayout->setSizeConstraint(QLayout::SetFixedSize);

    setLayout(formLayout);

    // Initial states
    _useIntervalCheck->setCheckState(Qt::Unchecked);
    _intervalTimeLabel->setEnabled(false);
    _intervalTimeEdit->setEnabled(false);
    _repeatTimeGroup->setEnabled(true);

    // Connect signals
    connect(_useIntervalCheck, SIGNAL(stateChanged(int)),
            this, SLOT(useIntervalStateChanged(int)));
    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

KAlarmConfigDialog::~KAlarmConfigDialog()
{

}

void KAlarmConfigDialog::accept()
{
    QString errorMsg;
    QWidget *errorWidget = 0;

    if (name().isEmpty())
    {
        errorMsg = tr("Please specify a name.");
        errorWidget = _nameLine;
    }
    else if (isUseIntervalChecked() &&
             intervalTime().hour() == 0 && intervalTime().minute() == 0)
    {
        errorMsg = tr("Please set an interval time(00:00 is not allowed).");
        errorWidget = _intervalTimeEdit;
    }

    if (errorWidget)
    {
        QMessageBox msgBox;
        msgBox.setText(errorMsg);
        msgBox.exec();

        errorWidget->setFocus();

        return;
    }

    QDialog::accept();
}

QString KAlarmConfigDialog::name() const
{
    return _nameLine->text();
}

void KAlarmConfigDialog::setName(const QString &name)
{
    _nameLine->setText(name);
}

QTime KAlarmConfigDialog::startTime() const
{
    return _startTimeEdit->time();
}

void KAlarmConfigDialog::setStartTime(const QTime &startTime)
{
    _startTimeEdit->setTime(startTime);
}
bool KAlarmConfigDialog::isUseIntervalChecked() const
{
    return _useIntervalCheck->isChecked();
}

void KAlarmConfigDialog::setUseIntervalChecked(bool useIntervalCheck)
{
    _useIntervalCheck->setChecked(useIntervalCheck);
}

QTime KAlarmConfigDialog::intervalTime() const
{
    return _intervalTimeEdit->time();
}

void KAlarmConfigDialog::setIntervalTime(const QTime &intervalTime)
{
    _intervalTimeEdit->setTime(intervalTime);
}

bool KAlarmConfigDialog::isMondayChecked() const
{
    return _mondayCheck->isChecked();
}

void KAlarmConfigDialog::setMondayChecked(bool checked)
{
    _mondayCheck->setChecked(checked);
}

bool KAlarmConfigDialog::isTuesdayChecked() const
{
    return _tuesdayCheck->isChecked();
}

void KAlarmConfigDialog::setTuesdayChecked(bool checked)
{
    _tuesdayCheck->setChecked(checked);
}

bool KAlarmConfigDialog::isWednesdayChecked() const
{
    return _wednesdayCheck->isChecked();
}

void KAlarmConfigDialog::setWednesdayChecked(bool checked)
{
    _wednesdayCheck->setChecked(checked);
}

bool KAlarmConfigDialog::isThursdayChecked() const
{
    return _thursdayCheck->isChecked();
}

void KAlarmConfigDialog::setThursdayChecked(bool checked)
{
    _thursdayCheck->setChecked(checked);
}
bool KAlarmConfigDialog::isFridayChecked() const
{
    return _fridayCheck->isChecked();
}

void KAlarmConfigDialog::setFridayChecked(bool checked)
{
    _fridayCheck->setChecked(checked);
}

bool KAlarmConfigDialog::isSaturdayChecked() const
{
    return _saturdayCheck->isChecked();
}

void KAlarmConfigDialog::setSaturdayChecked(bool checked)
{
    _saturdayCheck->setChecked(checked);
}

bool KAlarmConfigDialog::isSundayChecked() const
{
    return _sundayCheck->isChecked();
}

void KAlarmConfigDialog::setSundayChecked(bool checked)
{
    _sundayCheck->setChecked(checked);
}

void KAlarmConfigDialog::useIntervalStateChanged(int state)
{
    if (state == Qt::Checked)
    {
        _intervalTimeLabel->setEnabled(true);
        _intervalTimeEdit->setEnabled(true);
        _repeatTimeGroup->setEnabled(false);
    }
    else
    {
        _intervalTimeLabel->setEnabled(false);
        _intervalTimeEdit->setEnabled(false);
        _repeatTimeGroup->setEnabled(true);
    }
}

