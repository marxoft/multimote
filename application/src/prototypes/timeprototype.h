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

#ifndef TIMEPROTOTYPE_H
#define TIMEPROTOTYPE_H

#include <QObject>
#include <QScriptable>
#include <QTime>
#include <QMetaType>

class TimePrototype : public QObject, public QScriptable
{
    Q_OBJECT

    Q_PROPERTY(int hour READ hour)
    Q_PROPERTY(int minute READ minute)
    Q_PROPERTY(int second READ second)
    Q_PROPERTY(int msec READ msec)

public:
    explicit TimePrototype(QObject *parent = 0);

    int hour() const;

    int minute() const;

    int second() const;

    int msec() const;
    
private:
    Q_DISABLE_COPY(TimePrototype)
};

Q_DECLARE_METATYPE(QTime)

#endif // TIMEPROTOTYPE_H
