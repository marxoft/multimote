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

#include "standarditemprototype.h"
#include <QScriptEngine>

StandardItemPrototype::StandardItemPrototype(QObject *parent) :
    QObject(parent)
{
}

QString StandardItemPrototype::text() const {
    if (QStandardItem *item = qscriptvalue_cast<QStandardItem*>(this->thisObject())) {
        return item->text();
    }

    return QString();
}

void StandardItemPrototype::setText(const QString &text) {
    if (QStandardItem *item = qscriptvalue_cast<QStandardItem*>(this->thisObject())) {
        return item->setText(text);
    }
}

QString StandardItemPrototype::iconSource() const {
    if (QStandardItem *item = qscriptvalue_cast<QStandardItem*>(this->thisObject())) {
        return item->icon().name();
    }

    return QString();
}

void StandardItemPrototype::setIconSource(const QString &path) {
    if (QStandardItem *item = qscriptvalue_cast<QStandardItem*>(this->thisObject())) {
        return item->setIcon(path.contains('/') ? QIcon(path) : QIcon::fromTheme(path));
    }
}

QVariant StandardItemPrototype::data() const {
    if (QStandardItem *item = qscriptvalue_cast<QStandardItem*>(this->thisObject())) {
        return item->data();
    }

    return QVariant();
}

void StandardItemPrototype::setData(const QVariant &data) {
    if (QStandardItem *item = qscriptvalue_cast<QStandardItem*>(this->thisObject())) {
        return item->setData(data);
    }
}
