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

#ifndef KALARMCONFIGDIALOG_H
#define KALARMCONFIGDIALOG_H

#include <QDialog>

#include <QtWidgets>

class KAlarmConfigDialog : public QDialog
{
    Q_OBJECT

public:
    KAlarmConfigDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~KAlarmConfigDialog();

    QString name() const;
    void setName(const QString &name);

    QTime startTime() const;
    void setStartTime(const QTime &startTime);

    bool isUseIntervalChecked() const;
    void setUseIntervalChecked(bool useIntervalCheck);

    QTime intervalTime() const;
    void setIntervalTime(const QTime &intervalTime);

    bool isMondayChecked() const;
    void setMondayChecked(bool checked);

    bool isTuesdayChecked() const;
    void setTuesdayChecked(bool checked);

    bool isWednesdayChecked() const;
    void setWednesdayChecked(bool checked);

    bool isThursdayChecked() const;
    void setThursdayChecked(bool checked);

    bool isFridayChecked() const;
    void setFridayChecked(bool checked);

    bool isSaturdayChecked() const;
    void setSaturdayChecked(bool checked);

    bool isSundayChecked() const;
    void setSundayChecked(bool checked);

private:
    QLabel    *_nameLabel;
    QLineEdit *_nameLine;
    QLabel    *_startTimeLabel;
    QTimeEdit *_startTimeEdit;
    QCheckBox *_useIntervalCheck;
    QLabel    *_intervalTimeLabel;
    QTimeEdit *_intervalTimeEdit;
    QCheckBox *_mondayCheck;
    QCheckBox *_tuesdayCheck;
    QCheckBox *_wednesdayCheck;
    QCheckBox *_thursdayCheck;
    QCheckBox *_fridayCheck;
    QCheckBox *_saturdayCheck;
    QCheckBox *_sundayCheck;
    QGroupBox *_repeatTimeGroup;

private slots:
    void useIntervalStateChanged(int state);
};

#endif // KALARMCONFIGDIALOG_H
