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

#include "selectionitemprototype.h"
#include <QScriptEngine>

SelectionItemPrototype::SelectionItemPrototype(QObject *parent) :
    QObject(parent)
{
}

QString SelectionItemPrototype::iconSource() const {
    if (SelectionItem *item = qscriptvalue_cast<SelectionItem*>(this->thisObject())) {
        return item->iconSource();
    }

    return QString();
}

void SelectionItemPrototype::setIconSource(const QString &source) {
    if (SelectionItem *item = qscriptvalue_cast<SelectionItem*>(this->thisObject())) {
        item->setIconSource(source);
        emit dataChanged();
    }
}

QString SelectionItemPrototype::text() const {
    if (SelectionItem *item = qscriptvalue_cast<SelectionItem*>(this->thisObject())) {
        return item->text();
    }

    return QString();
}

void SelectionItemPrototype::setText(const QString &text) {
    if (SelectionItem *item = qscriptvalue_cast<SelectionItem*>(this->thisObject())) {
        item->setText(text);
        emit dataChanged();
    }
}

QVariant SelectionItemPrototype::data() const {
    if (SelectionItem *item = qscriptvalue_cast<SelectionItem*>(this->thisObject())) {
        return item->data();
    }

    return QVariant();
}

void SelectionItemPrototype::setData(const QVariant &data) {
    if (SelectionItem *item = qscriptvalue_cast<SelectionItem*>(this->thisObject())) {
        item->setData(data);
        emit dataChanged();
    }
}

Qt::Alignment SelectionItemPrototype::textAlignment() const {
    if (SelectionItem *item = qscriptvalue_cast<SelectionItem*>(this->thisObject())) {
        return item->textAlignment();
    }

    return 0;
}

void SelectionItemPrototype::setTextAlignment(Qt::Alignment alignment) {
    if (SelectionItem *item = qscriptvalue_cast<SelectionItem*>(this->thisObject())) {
        item->setTextAlignment(alignment);
        emit dataChanged();
    }
}
