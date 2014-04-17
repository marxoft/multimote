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

#include "notifications.h"
#include <QMessageBox>
#ifdef Q_WS_MAEMO_5
#include <QMaemo5InformationBox>
#endif

Notifications::Notifications(QObject *parent) :
    QObject(parent)
{
}

Notifications::~Notifications() {}

#ifdef Q_WS_MAEMO_5
void Notifications::information(const QString &message, QWidget *parent) {

    QMaemo5InformationBox::information(parent, message);
}

void Notifications::error(const QString &message, QWidget *parent) {
    QMaemo5InformationBox::information(parent, message, QMaemo5InformationBox::NoTimeout);
}

bool Notifications::confirm(const QString &message, QWidget *parent) {
    return QMessageBox::question(parent, Notifications::tr("Confirm"), message, QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes;
}
#else
void Notifications::information(const QString &message, QObject *parent) {
    Q_UNUSED(message);
    Q_UNUSED(parent);
}

void Notifications::error(const QString &message, QObject *parent) {
    Q_UNUSED(message);
    Q_UNUSED(parent);
}

bool Notifications::confirm(const QString &message, QObject *parent) {
    Q_UNUSED(message);
    Q_UNUSED(parent);

    return false;
}
#endif
