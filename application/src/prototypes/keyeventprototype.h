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

#ifndef KEYEVENTPROTOTYPE_H
#define KEYEVENTPROTOTYPE_H

#include <QObject>
#include <QScriptable>
#include <QKeyEvent>

class KeyEventPrototype : public QObject, public QScriptable
{
    Q_OBJECT

    Q_PROPERTY(int count READ count CONSTANT)
    Q_PROPERTY(bool isAutoRepeat READ isAutoRepeat CONSTANT)
    Q_PROPERTY(int key READ key CONSTANT)
    Q_PROPERTY(Qt::KeyboardModifiers modifiers READ modifiers CONSTANT)
    Q_PROPERTY(QString text READ text CONSTANT)

public:
    explicit KeyEventPrototype(QObject *parent = 0);

    int count() const;

    bool isAutoRepeat() const;

    int key() const;

    Qt::KeyboardModifiers modifiers() const;

    QString text() const;

private:
    Q_DISABLE_COPY(KeyEventPrototype)
};

Q_DECLARE_METATYPE(QKeyEvent*)

#endif // KEYEVENTPROTOTYPE_H
