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

#include "timeprototype.h"
#include <QScriptEngine>

TimePrototype::TimePrototype(QObject *parent) :
    QObject(parent)
{
}

int TimePrototype::hour() const {
    return this->thisObject().toDateTime().time().hour();
}

int TimePrototype::minute() const {
    return this->thisObject().toDateTime().time().minute();
}

int TimePrototype::second() const {
    return this->thisObject().toDateTime().time().second();
}

int TimePrototype::msec() const {
    return this->thisObject().toDateTime().time().msec();
}
