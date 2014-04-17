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

#include "listselector.h"
#include "listview.h"
#include <QStandardItem>
#include <QMaemo5ListPickSelector>

ListSelector::ListSelector(QWidget *parent) :
    QMaemo5ValueButton(parent),
    ControlWidget(),
    m_selector(new QMaemo5ListPickSelector(this)),
    m_view(new ListView(this))
{
    this->setContextMenuPolicy(Qt::ActionsContextMenu);

    m_view->setMinimumHeight((m_view->count() > 0 ? m_view->sizeHintForRow(0) : 70) * 5);
    m_selector->setModel(m_view->model());
    m_selector->setView(m_view);
    this->setPickSelector(m_selector);
    this->setValueText(tr("None chosen"));
    this->connect(m_selector, SIGNAL(selected(QString)), this, SIGNAL(selected(QString)));
    this->connect(m_view, SIGNAL(countChanged(int)), this, SIGNAL(countChanged(int)));
}

int ListSelector::count() const {
    return m_view->count();
}

int ListSelector::currentIndex() const {
    return m_selector->currentIndex();
}

void ListSelector::setCurrentIndex(int i) {
    m_selector->setCurrentIndex(i);
}

QVariant ListSelector::currentValue() const {
    return m_view->model()->index(this->currentIndex(), 0).data(Qt::UserRole + 1);
}

void ListSelector::setCurrentValue(const QVariant &value) {
    for (int i = 0; i < this->count(); i++) {
        if (m_view->itemAt(i)->data() == value) {
            this->setCurrentIndex(i);
            return;
        }
    }

    this->setCurrentIndex(0);
}

QString ListSelector::currentValueText() const {
    return m_selector->currentValueText();
}

void ListSelector::addItem(const QString &name, const QVariant &value, Qt::Alignment textAlignment) {
    m_view->addItem(name, value, textAlignment);
}

void ListSelector::addItem(const QString &iconSource, const QString &name, const QVariant &value, Qt::Alignment textAlignment) {
    m_view->addItem(iconSource, name, value, textAlignment);
}

void ListSelector::insertItem(int row, const QString &name, const QVariant &value, Qt::Alignment textAlignment) {
    m_view->insertItem(row, name, value, textAlignment);
}

void ListSelector::insertItem(int row, const QString &iconSource, const QString &name, const QVariant &value, Qt::Alignment textAlignment) {
    m_view->insertItem(row, iconSource, name, value, textAlignment);
}

bool ListSelector::removeItem(int row) {
    return m_view->removeItem(row);
}

void ListSelector::clear() {
    m_view->clear();
}

void ListSelector::sort(Qt::SortOrder order) {
    m_view->sort(order);
}
