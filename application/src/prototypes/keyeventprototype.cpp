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

#include "keyeventprototype.h"
#include <QScriptEngine>

KeyEventPrototype::KeyEventPrototype(QObject *parent) :
    QObject(parent)
{
}

int KeyEventPrototype::count() const {
    if (QKeyEvent *event = qscriptvalue_cast<QKeyEvent*>(this->thisObject())) {
        return event->count();
    }

    return -1;
}

bool KeyEventPrototype::isAutoRepeat() const {
    if (QKeyEvent *event = qscriptvalue_cast<QKeyEvent*>(this->thisObject())) {
        return event->isAutoRepeat();
    }

    return false;
}

int KeyEventPrototype::key() const {
    if (QKeyEvent *event = qscriptvalue_cast<QKeyEvent*>(this->thisObject())) {
        return event->key();
    }

    return -1;
}

Qt::KeyboardModifiers KeyEventPrototype::modifiers() const {
    if (QKeyEvent *event = qscriptvalue_cast<QKeyEvent*>(this->thisObject())) {
        return event->modifiers();
    }

    return Qt::NoModifier;
}

QString KeyEventPrototype::text() const {
    if (QKeyEvent *event = qscriptvalue_cast<QKeyEvent*>(this->thisObject())) {
        return event->text();
    }

    return QString();
}
