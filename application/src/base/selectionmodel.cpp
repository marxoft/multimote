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
#include "selectionitem.h"

SelectionModel::SelectionModel(QObject *parent) :
    QAbstractListModel(parent)
{
    m_roleNames[SelectionItem::DataRole] = "data";
    m_roleNames[SelectionItem::IconSourceRole] = "iconSource";
    m_roleNames[SelectionItem::TextRole] = "text";
    m_roleNames[SelectionItem::TextAlignmentRole] = "textAlignment";
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

int SelectionModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)

    return m_list.size();
}

QVariant SelectionModel::data(const QModelIndex &index, int role) const {
    if (SelectionItem *item = this->itemAt(index.row())) {
        return item->data(role);
    }
    
    return QVariant();
}

void SelectionModel::addItem(const QString &text, const QVariant &data, Qt::Alignment textAlignment) {
    SelectionItem *item = new SelectionItem(text, data, textAlignment, this);
    this->connect(item, SIGNAL(dataChanged()), this, SLOT(onItemDataChanged()));
    const int size = m_list.size();
    this->beginInsertRows(QModelIndex(), size, size);
    m_list.append(item);
    this->endInsertRows();
    emit countChanged(this->rowCount());
}

void SelectionModel::addItem(const QString &iconSource, const QString &text, const QVariant &data, Qt::Alignment textAlignment) {
    SelectionItem *item = new SelectionItem(iconSource, text, data, textAlignment, this);
    this->connect(item, SIGNAL(dataChanged()), this, SLOT(onItemDataChanged()));
    const int size = m_list.size();
    this->beginInsertRows(QModelIndex(), size, size);
    m_list.append(item);
    this->endInsertRows();
    emit countChanged(this->rowCount());
}

void SelectionModel::insertItem(int row, const QString &text, const QVariant &data, Qt::Alignment textAlignment) {
    if ((row >= 0) && (row < m_list.size())) {
        SelectionItem *item = new SelectionItem(text, data, textAlignment, this);
        this->connect(item, SIGNAL(dataChanged()), this, SLOT(onItemDataChanged()));
        this->beginInsertRows(QModelIndex(), row, row);
        m_list.insert(row, item);
        this->endInsertRows();
        emit countChanged(this->rowCount());
    }
}

void SelectionModel::insertItem(int row, const QString &iconSource, const QString &text, const QVariant &data, Qt::Alignment textAlignment) {
    if ((row >= 0) && (row < this->rowCount() - 1)) {
        SelectionItem *item = new SelectionItem(iconSource, text, data, textAlignment, this);
        this->connect(item, SIGNAL(dataChanged()), this, SLOT(onItemDataChanged()));
        this->beginInsertRows(QModelIndex(), row, row);
        m_list.insert(row, item);
        this->endInsertRows();
        emit countChanged(this->rowCount());
    }
}

bool SelectionModel::removeItem(int row) {
    if ((row >= 0) && (row < m_list.size())) {
        delete m_list.takeAt(row);
        return true;
    }

    return false;
}

void SelectionModel::clear() {
    this->beginResetModel();
    qDeleteAll(m_list);
    m_list.clear();
    this->endResetModel();
}

SelectionItem* SelectionModel::itemAt(int row) const {
    if ((row >= 0) && (row < m_list.size())) {
        return m_list.at(row);
    }

    return 0;
}

void SelectionModel::onItemDataChanged() {
    if (SelectionItem* item = qobject_cast<SelectionItem*>(this->sender())) {
        const QModelIndex index = this->index(m_list.indexOf(item));
        emit dataChanged(index, index);
    }
}
