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

#ifndef DATEPROTOTYPE_H
#define DATEPROTOTYPE_H

#include <QObject>
#include <QScriptable>
#include <QDate>
#include <QMetaType>

class DatePrototype : public QObject, public QScriptable
{
    Q_OBJECT

    Q_PROPERTY(int day READ day)
    Q_PROPERTY(int month READ month)
    Q_PROPERTY(int year READ year)

public:
    explicit DatePrototype(QObject *parent = 0);

    int day() const;

    int month() const;

    int year() const;
    
private:
    Q_DISABLE_COPY(DatePrototype)
};

Q_DECLARE_METATYPE(QDate)

#endif // DATEPROTOTYPE_H
