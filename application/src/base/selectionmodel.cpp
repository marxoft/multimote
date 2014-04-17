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

#include "selectionmodel.h"

SelectionModel::SelectionModel(QObject *parent) :
    QStandardItemModel(parent)
{
    m_roleNames[Qt::DisplayRole] = "name";
    m_roleNames[Qt::UserRole + 1] = "value";
#if QT_VERSION < 0x050000
    this->setRoleNames(m_roleNames);
#endif
}

SelectionModel::~SelectionModel() {}

#if QT_VERSION >= 0x050000
QHash<int, QByteArray> SelectionModel::roleNames() const {
    return m_roleNames;
}
#endif

void SelectionModel::addItem(const QString &name, const QVariant &value, Qt::Alignment textAlignment) {
    QStandardItem *item = new QStandardItem(name);
    item->setData(value);
    item->setTextAlignment(textAlignment);
    this->appendRow(item);
    emit countChanged(this->rowCount());
}

void SelectionModel::addItem(const QString &iconSource, const QString &name, const QVariant &value, Qt::Alignment textAlignment) {
    QStandardItem *item = new QStandardItem(iconSource.contains('/') ? QIcon(iconSource) : QIcon::fromTheme(iconSource), name);
    item->setData(value);
    item->setTextAlignment(textAlignment);
    this->appendRow(item);
    emit countChanged(this->rowCount());
}

void SelectionModel::insertItem(int row, const QString &name, const QVariant &value, Qt::Alignment textAlignment) {
    if ((row >= 0) && (row < this->rowCount() - 1)) {
        QStandardItem *item = new QStandardItem(name);
        item->setData(value);
        item->setTextAlignment(textAlignment);
        this->insertRow(row, item);
        emit countChanged(this->rowCount());
    }
}

void SelectionModel::insertItem(int row, const QString &iconSource, const QString &name, const QVariant &value, Qt::Alignment textAlignment) {
    if ((row >= 0) && (row < this->rowCount() - 1)) {
        QStandardItem *item = new QStandardItem(iconSource.contains('/') ? QIcon(iconSource) : QIcon::fromTheme(iconSource), name);
        item->setData(value);
        item->setTextAlignment(textAlignment);
        this->insertRow(row, item);
        emit countChanged(this->rowCount());
    }
}

bool SelectionModel::removeItem(int row) {
    return this->removeRow(row);
}

QStandardItem* SelectionModel::itemAt(int row) const {
    return this->item(row);
}
