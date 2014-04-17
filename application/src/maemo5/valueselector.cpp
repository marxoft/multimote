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

#include "valueselector.h"
#include "../base/selectionmodel.h"
#include <QMaemo5ListPickSelector>

ValueSelector::ValueSelector(const QString &text, QWidget *parent) :
    QMaemo5ValueButton(text, parent),
    m_model(0),
    m_selector(new QMaemo5ListPickSelector(this))
{
    this->setPickSelector(m_selector);
    this->setValueText(tr("None chosen"));
    this->connect(m_selector, SIGNAL(selected(QString)), this, SLOT(onSelected()));
}

ValueSelector::~ValueSelector() {}

SelectionModel* ValueSelector::model() const {
    return m_model;
}

void ValueSelector::setModel(SelectionModel *model) {
    m_model = model;
    m_selector->setModel(model);
    m_selector->setModelColumn(0);
}

void ValueSelector::setValue(const QVariant &value) {
    if (!m_model) {
        return;
    }

    bool found = false;
    int i = 0;

    while ((!found) && (i < m_model->rowCount())) {
        found = m_model->data(m_model->index(i, 0), Qt::UserRole + 1) == value;

        if (found) {
            m_selector->setCurrentIndex(i);
        }

        i++;
    }

    if (!found) {
        this->setValueText(tr("None chosen"));
    }
}

QVariant ValueSelector::currentValue() const {
    return !m_model ? QVariant() : m_model->data(m_model->index(m_selector->currentIndex(), 0), Qt::UserRole + 1);
}

void ValueSelector::onSelected() {
    emit valueChanged(this->currentValue());
}
