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

#include "settings.h"

Settings* Settings::self = 0;

Settings::Settings(QObject *parent) :
    QSettings("MultiMote", "MultiMote", parent)
{
    if (!self) {
        self = this;
    }
}

Settings::~Settings() {}

QString Settings::currentRemote() const {
    return this->value("currentRemote").toString();
}

void Settings::setCurrentRemote(const QString &remote) {
    if (remote != this->currentRemote()) {
        this->setValue("currentRemote", remote);
        emit currentRemoteChanged();
    }
}

bool Settings::loadRemoteOnStartup() const {
    return this->value("loadRemoteOnStartup", true).toBool();
}

void Settings::setLoadRemoteOnStartup(bool load) {
    if (load != this->loadRemoteOnStartup()) {
        this->setValue("loadRemoteOnStartup", load);
        emit loadRemoteOnStartupChanged();
    }
}

QVariant Settings::setting(const QString &key) const {
    return this->value(key);
}

void Settings::setSetting(const QString &key, const QVariant &value) {
    this->setValue(key, value);
}
