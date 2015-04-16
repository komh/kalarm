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

#ifdef CONFIG_QT5
#include <QtWidgets>
#include <QSoundEffect>
#else
#include <QtGui>
#endif

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
    okButton->setDefault(true); // Set OK button to a default button

    QPushButton *cancelButton = new QPushButton(tr("Cancel"));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    _showAlarmWindowCheck = new QCheckBox(tr("Show an alarm window"));

    _playSoundCheck = new QCheckBox(tr("Play sound"));
    _soundFileLine = new QLineEdit;
    _soundPlayPush = new QPushButton(tr("Play"));
    _soundFileBrowsePush = new QPushButton(tr("Browse..."));

    QHBoxLayout *soundFileLayout = new QHBoxLayout;
    soundFileLayout->addWidget(_soundFileLine, 1);
    soundFileLayout->addWidget(_soundPlayPush);
    soundFileLayout->addWidget(_soundFileBrowsePush);

    _execProgramCheck = new QCheckBox(tr("Execute a program"));
    _execProgramNameLine = new QLineEdit;
    _execProgramNameBrowsePush = new QPushButton(tr("Browse..."));
    _execProgramParamsLabel = new QLabel(tr("Parameters for a program:"));
    _execProgramParamsLine = new QLineEdit;

    QHBoxLayout *execProgramLayout = new QHBoxLayout;
    execProgramLayout->addWidget(_execProgramNameLine, 1);
    execProgramLayout->addWidget(_execProgramNameBrowsePush);

    QVBoxLayout *onAlarmLayout = new QVBoxLayout;
    onAlarmLayout->addWidget(_showAlarmWindowCheck);
    onAlarmLayout->addWidget(_playSoundCheck);
    onAlarmLayout->addLayout(soundFileLayout);
    onAlarmLayout->addWidget(_execProgramCheck);
    onAlarmLayout->addLayout(execProgramLayout);
    onAlarmLayout->addWidget(_execProgramParamsLabel);
    onAlarmLayout->addWidget(_execProgramParamsLine);

    _onAlarmGroup = new QGroupBox(tr("On alarm"));
    _onAlarmGroup->setLayout(onAlarmLayout);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(_nameLabel, _nameLine);
    formLayout->addRow(_startTimeLabel, _startTimeEdit);
    formLayout->addRow(_useIntervalCheck);
    formLayout->addRow(_intervalTimeLabel, _intervalTimeEdit);
    formLayout->addRow(_repeatTimeGroup);
    formLayout->addRow(_onAlarmGroup);
    formLayout->addRow(buttonLayout);

    // Disable resizing of a dialog
    formLayout->setSizeConstraint(QLayout::SetFixedSize);

    setLayout(formLayout);

    // Initial states
    _useIntervalCheck->setCheckState(Qt::Unchecked);
    _intervalTimeLabel->setEnabled(false);
    _intervalTimeEdit->setEnabled(false);
    _repeatTimeGroup->setEnabled(true);
    _showAlarmWindowCheck->setChecked(true);
    _playSoundCheck->setChecked(false);
    _soundFileLine->setEnabled(false);
    _soundPlayPush->setEnabled(false);
    _soundFileBrowsePush->setEnabled(false);
    _execProgramCheck->setChecked(false);
    _execProgramNameLine->setEnabled(false);
    _execProgramNameBrowsePush->setEnabled(false);
    _execProgramParamsLabel->setEnabled(false);
    _execProgramParamsLabel->setEnabled(false);

    // Connect signals
    connect(_useIntervalCheck, SIGNAL(stateChanged(int)),
            this, SLOT(useIntervalStateChanged(int)));
    connect(_playSoundCheck, SIGNAL(stateChanged(int)),
            this, SLOT(useSoundStateChanged(int)));
    connect(_soundPlayPush, SIGNAL(clicked()), this, SLOT(playClicked()));
    connect(_soundFileBrowsePush, SIGNAL(clicked()),
            this, SLOT(browseClicked()));
    connect(_execProgramCheck, SIGNAL(stateChanged(int)),
            this, SLOT(execProgramStateChanged(int)));
    connect(_execProgramNameBrowsePush, SIGNAL(clicked()),
            this, SLOT(execProgramNameBrowseClicked()));
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
        QMessageBox msgBox(this);
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
bool KAlarmConfigDialog::isShowAlarmWindowChecked() const
{
    return _showAlarmWindowCheck->isChecked();
}

void KAlarmConfigDialog::setShowAlarmWindowChecked(bool checked)
{
    _showAlarmWindowCheck->setChecked(checked);
}

bool KAlarmConfigDialog::isPlaySoundChecked() const
{
    return _playSoundCheck->isChecked();
}

void KAlarmConfigDialog::setPlaySoundChecked(bool checked)
{
    _playSoundCheck->setChecked(checked);
}
QString KAlarmConfigDialog::soundFile() const
{
    return _soundFileLine->text();
}

void KAlarmConfigDialog::setSoundFile(const QString &soundFile)
{
    _soundFileLine->setText(soundFile);
}
QString KAlarmConfigDialog::execProgramName() const
{
    return _execProgramNameLine->text();
}

void KAlarmConfigDialog::setExecProgramName(const QString &program)
{
    _execProgramNameLine->setText(program);
}

bool KAlarmConfigDialog::isExecProgramChecked() const
{
    return _execProgramCheck->isChecked();
}

void KAlarmConfigDialog::setExecProgramChecked(bool checked)
{
    _execProgramCheck->setChecked(checked);
}

QString KAlarmConfigDialog::execProgramParams() const
{
    return _execProgramParamsLine->text();
}

void KAlarmConfigDialog::setExecProgramParams(const QString &params)
{
    _execProgramParamsLine->setText(params);
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

void KAlarmConfigDialog::useSoundStateChanged(int state)
{
    bool enabled = state == Qt::Checked;

    _soundFileLine->setEnabled(enabled);
    _soundPlayPush->setEnabled(enabled);
    _soundFileBrowsePush->setEnabled(enabled);
}

#ifndef CONFIG_QT5
// FIXME: Ugly.
class Sleep : public QThread
{
public:
    static void msleep(unsigned long msecs)
    {
        QThread::msleep(msecs);
    }
};
#endif

void KAlarmConfigDialog::playClicked()
{
    static QString playingMsg(tr("Playing sound..."));

#ifdef CONFIG_QT5
    QSoundEffect effect;
    effect.setSource(QUrl::fromLocalFile(_soundFileLine->text()));
    // Source is not set ?
    if (effect.status() == QSoundEffect::Null)
        return;

    effect.setLoopCount(1);
    effect.setVolume(0.25f);

    QEventLoop waitPlay;
    connect(&effect, SIGNAL(statusChanged()), &waitPlay, SLOT(quit()));
    effect.play();
    // Wait for QSoundEffect::Error or QSoundEffect::Ready
    waitPlay.exec();

    if (effect.status() != QSoundEffect::Error)
    {
        QMessageBox msgBox(this);
        connect(&effect, SIGNAL(playingChanged()), &msgBox, SLOT(reject()));
        msgBox.setText(playingMsg);
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.exec();
    }
    else
        QMessageBox::warning(this, tr("KAlarm"), tr("Not playable"));
#else
    if (_soundFileLine->text().isEmpty())
        return;

    QSound sound(_soundFileLine->text());
    sound.setLoops(1);
    sound.play();

    if (!sound.isFinished())
    {
        QMessageBox msgBox(this);
        msgBox.setText(playingMsg);
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.show();

        // FIXME: Avoid polling and time consumption loop. Use event loop.
        while (!sound.isFinished() && msgBox.isVisible())
        {
            QApplication::processEvents();
            Sleep::msleep(10);
        }
    }
#endif
}

void KAlarmConfigDialog::browseClicked()
{
    QStringList filters;
    filters << "WAV files (*.wav)";
    filters << "All files (*)";

    QSettings settings;

    QFileDialog fileDlg(this);
    fileDlg.setNameFilters(filters);
    fileDlg.setDirectory(settings.value("LastSoundDirectory").toString());
    if (fileDlg.exec() == QDialog::Accepted)
    {
        QString soundFile(QDir::toNativeSeparators(
                              fileDlg.selectedFiles().first()));

        _soundFileLine->setText(soundFile);

        settings.setValue("LastSoundDirectory", fileDlg.directory().path());
    }
}

void KAlarmConfigDialog::execProgramStateChanged(int state)
{
    bool enabled = state == Qt::Checked;

    _execProgramNameLine->setEnabled(enabled);
    _execProgramNameBrowsePush->setEnabled(enabled);
    _execProgramParamsLabel->setEnabled(enabled);
    _execProgramParamsLine->setEnabled(enabled);
}

void KAlarmConfigDialog::execProgramNameBrowseClicked()
{
    QStringList filters;
    filters << "Executable files (*.exe; *.cmd; *.btm; *.com; *.bat)";
    filters << "All files (*)";

    QSettings settings;

    QFileDialog fileDlg(this);
    fileDlg.setNameFilters(filters);
    fileDlg.setDirectory(settings.value("LastExecuteProgramDirectory")
                         .toString());
    if (fileDlg.exec() == QDialog::Accepted)
    {
        QString program(QDir::toNativeSeparators(
                            fileDlg.selectedFiles().first()));
        _execProgramNameLine->setText(program);

        settings.setValue("LastExecuteProgramDirectory",
                          fileDlg.directory().path());
    }
}
