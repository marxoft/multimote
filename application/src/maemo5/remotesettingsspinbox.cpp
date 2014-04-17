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

#include "remotesettingsspinbox.h"
#include "../base/settings.h"
#include "../base/scriptengine.h"

RemoteSettingsSpinbox::RemoteSettingsSpinbox(QWidget *parent) :
    QSpinBox(parent)
{
    this->connect(this, SIGNAL(editingFinished()), this, SLOT(onValueEdited()));
}

RemoteSettingsSpinbox::~RemoteSettingsSpinbox() {}

void RemoteSettingsSpinbox::setKey(const QString &key) {
    m_key = key;
}

void RemoteSettingsSpinbox::setDefaultValue(const QVariant &value) {
    m_default = value;
}

void RemoteSettingsSpinbox::setHandler(const QString &handler) {
    m_handler = handler;
}

void RemoteSettingsSpinbox::load() {
    int value = Settings::instance()->value(this->key(), this->defaultValue()).toInt();
    this->setValue(value);
}

void RemoteSettingsSpinbox::onValueEdited() {
    if (!this->key().isEmpty()) {
        Settings::instance()->setValue(this->key(), this->value());
        ScriptEngine::instance()->globalObject().setProperty(this->key().section('/', -1), this->value());

        if (!this->handler().isEmpty()) {
            ScriptEngine::instance()->evaluate(this->handler());
        }
    }
}
