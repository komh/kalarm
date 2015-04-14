/****************************************************************************
**
** Entry module of K Alarm
**
** Copyright (C) 2015 by KO Myung-Hun
** All rights reserved.
** Contact: KO Myung-Hun (komh@chollian.net)
**
** This file is part of K Alarm
**
** $BEGIN_LICENSE$
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** $END_LICENSE$
**
****************************************************************************/

#include "kalarm.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QIcon icon;
    icon.addFile(":/icons/candy_clock_16.png");
    icon.addFile(":/icons/candy_clock_24.png");
    icon.addFile(":/icons/candy_clock_32.png");
    icon.addFile(":/icons/candy_clock_48.png");
    icon.addFile(":/icons/candy_clock_64.png");
    icon.addFile(":/icons/candy_clock_128.png");
    icon.addFile(":/icons/candy_clock_256.png");
    QApplication::setWindowIcon(icon);

    QApplication::setQuitOnLastWindowClosed(false);

    KAlarm w;
    w.show();

    return a.exec();
}
