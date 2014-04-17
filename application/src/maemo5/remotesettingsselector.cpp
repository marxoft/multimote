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

#include "remotesettingsselector.h"
#include "../base/settings.h"
#include "../base/scriptengine.h"
#include "../base/selectionmodel.h"
#include <QMaemo5ListPickSelector>

RemoteSettingsSelector::RemoteSettingsSelector(const QString &text, QWidget *parent) :
    ValueSelector(text, parent)
{
    this->setModel(new SelectionModel(this));
}

RemoteSettingsSelector::~RemoteSettingsSelector() {}

void RemoteSettingsSelector::setKey(const QString &key) {
    m_key = key;
}

void RemoteSettingsSelector::setDefaultValue(const QVariant &value) {
    m_default = value;
}

void RemoteSettingsSelector::setHandler(const QString &handler) {
    m_handler = handler;
}

void RemoteSettingsSelector::load() {
    if (!m_model) {
        return;
    }

    QVariant value = Settings::instance()->value(this->key(), this->defaultValue());

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
        m_selector->setCurrentIndex(0);
    }
}

QVariant RemoteSettingsSelector::currentValue() const {
    return !m_model ? QVariant() : m_model->data(m_model->index(m_selector->currentIndex(), 0), Qt::UserRole + 1);
}

void RemoteSettingsSelector::onSelected() {
    if (!this->key().isEmpty()) {
        Settings::instance()->setValue(this->key(), this->currentValue());
        ScriptEngine::instance()->globalObject().setProperty(this->key().section('/', -1), this->currentValue().toString());

        if (!this->handler().isEmpty()) {
            ScriptEngine::instance()->evaluate(this->handler());
        }
    }
}
