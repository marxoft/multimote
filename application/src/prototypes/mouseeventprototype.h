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

#ifndef MOUSEEVENTPROTOTYPE_H
#define MOUSEEVENTPROTOTYPE_H

#include <QObject>
#include <QScriptable>
#include <QMouseEvent>

class MouseEventPrototype : public QObject, public QScriptable
{
    Q_OBJECT

    Q_PROPERTY(QPoint globalPos READ globalPos CONSTANT)
    Q_PROPERTY(int globalX READ globalX CONSTANT)
    Q_PROPERTY(int globalY READ globalY CONSTANT)
    Q_PROPERTY(QPoint pos READ pos CONSTANT)
    Q_PROPERTY(int x READ x CONSTANT)
    Q_PROPERTY(int y READ y CONSTANT)

public:
    explicit MouseEventPrototype(QObject *parent = 0);

    QPoint globalPos() const;
    int globalX() const;
    int globalY() const;

    QPoint pos() const;
    int x() const;
    int y() const;

private:
    Q_DISABLE_COPY(MouseEventPrototype)
};

Q_DECLARE_METATYPE(QMouseEvent*)

#endif // MOUSEEVENTPROTOTYPE_H
