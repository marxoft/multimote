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

#include "remotesettingscheckbox.h"
#include "../base/settings.h"
#include "../base/scriptengine.h"

RemoteSettingsCheckbox::RemoteSettingsCheckbox(QWidget *parent) :
    QCheckBox(parent)
{
    this->connect(this, SIGNAL(clicked(bool)), this, SLOT(onClicked(bool)));
}

RemoteSettingsCheckbox::~RemoteSettingsCheckbox() {}

void RemoteSettingsCheckbox::setKey(const QString &key) {
    m_key = key;
}

void RemoteSettingsCheckbox::setDefaultValue(const QVariant &value) {
    m_default = value;
}

void RemoteSettingsCheckbox::setHandler(const QString &handler) {
    m_handler = handler;
}

void RemoteSettingsCheckbox::load() {
    bool enabled = Settings::instance()->value(this->key(), this->defaultValue()).toBool();
    this->setChecked(enabled);
}

void RemoteSettingsCheckbox::onClicked(bool checked) {
    if (!this->key().isEmpty()) {
        Settings::instance()->setValue(this->key(), checked);
        ScriptEngine::instance()->globalObject().setProperty(this->key().section('/', -1), checked);

        if (!this->handler().isEmpty()) {
            ScriptEngine::instance()->evaluate(this->handler());
        }
    }
}
