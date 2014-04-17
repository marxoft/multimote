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

#include "listview.h"
#include "../../base/selectionmodel.h"
#include <QStandardItem>

ListView::ListView(QWidget *parent) :
    QListView(parent),
    m_model(new SelectionModel(this))
{
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
    this->setEditTriggers(QListView::NoEditTriggers);
    this->setModel(m_model);
    this->connect(this, SIGNAL(activated(QModelIndex)), this, SLOT(onCurrentItemChanged()));
}

bool ListView::multiSelection() const {
    return this->selectionMode() == QListView::MultiSelection;
}

void ListView::setMultiSelection(bool multi) {
    this->setSelectionMode(multi ? QListView::MultiSelection : QListView::SingleSelection);
}

void ListView::onCurrentItemChanged() {
    emit currentItemChanged(this->currentItem());
}

void ListView::addItem(const QString &name, const QVariant &value, Qt::Alignment textAlignment) {
    m_model->addItem(name, value, textAlignment);
    emit countChanged(this->count());
}

void ListView::addItem(const QString &iconSource, const QString &name, const QVariant &value, Qt::Alignment textAlignment) {
    m_model->addItem(iconSource, name, value, textAlignment);
    emit countChanged(this->count());
}

void ListView::insertItem(int row, const QString &name, const QVariant &value, Qt::Alignment textAlignment) {
    m_model->insertItem(row, name, value, textAlignment);
    emit countChanged(this->count());
}

void ListView::insertItem(int row, const QString &iconSource, const QString &name, const QVariant &value, Qt::Alignment textAlignment) {
    m_model->insertItem(row, iconSource, name, value, textAlignment);
    emit countChanged(this->count());
}

bool ListView::removeItem(int row) {
    if (m_model->removeItem(row)) {
        emit countChanged(this->count());
        return true;
    }

    return false;
}

void ListView::clear() {
    m_model->clear();
    emit countChanged(this->count());
}

void ListView::sort(Qt::SortOrder order) {
    m_model->sort(0, order);
}

QStandardItem* ListView::itemAt(int row) const {
    return m_model->item(row);
}

int ListView::count() const {
    return m_model->rowCount();
}

QStandardItem* ListView::currentItem() const {
    return m_model->itemFromIndex(this->currentIndex());
}

int ListView::currentRow() const {
    return this->currentIndex().row();
}

void ListView::setCurrentRow(int row) {
    this->setCurrentIndex(m_model->index(row, 0));
}
