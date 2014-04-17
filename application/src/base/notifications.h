/*
 * Copyright (C) 2014 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 3, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H

#include <QObject>

class Notifications : public QObject
{
    Q_OBJECT

public:
    explicit Notifications(QObject *parent = 0);
    ~Notifications();
        
public slots:
#ifdef Q_WS_MAEMO_5
    static void information(const QString &message, QWidget *parent = 0);
    static void error(const QString &message, QWidget *parent = 0);
    static bool confirm(const QString &message, QWidget *parent = 0);
#else
    static void information(const QString &message, QObject *parent = 0);
    static void error(const QString &message, QObject *parent = 0);
    static bool confirm(const QString &message, QObject *parent = 0);
#endif

private:
    Q_DISABLE_COPY(Notifications)
};

#endif // NOTIFICATIONS_H
