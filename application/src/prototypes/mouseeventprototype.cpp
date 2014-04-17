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

#include "mouseeventprototype.h"
#include <QScriptEngine>

MouseEventPrototype::MouseEventPrototype(QObject *parent) :
    QObject(parent)
{
}

QPoint MouseEventPrototype::globalPos() const {
    if (QMouseEvent *event = qscriptvalue_cast<QMouseEvent*>(this->thisObject())) {
        return event->globalPos();
    }

    return QPoint();
}

int MouseEventPrototype::globalX() const {
    if (QMouseEvent *event = qscriptvalue_cast<QMouseEvent*>(this->thisObject())) {
        return event->globalX();
    }

    return -1;
}

int MouseEventPrototype::globalY() const {
    if (QMouseEvent *event = qscriptvalue_cast<QMouseEvent*>(this->thisObject())) {
        return event->globalY();
    }

    return -1;
}

QPoint MouseEventPrototype::pos() const {
    if (QMouseEvent *event = qscriptvalue_cast<QMouseEvent*>(this->thisObject())) {
        return event->pos();
    }

    return QPoint();
}

int MouseEventPrototype::x() const {
    if (QMouseEvent *event = qscriptvalue_cast<QMouseEvent*>(this->thisObject())) {
        return event->x();
    }

    return -1;
}

int MouseEventPrototype::y() const {
    if (QMouseEvent *event = qscriptvalue_cast<QMouseEvent*>(this->thisObject())) {
        return event->y();
    }

    return -1;
}
