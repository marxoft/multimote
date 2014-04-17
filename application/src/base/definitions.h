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

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <QString>
#include <qplatformdefs.h>
#if QT_VERSION >= 0x050000
#include <QStandardPaths>
#else
#include <QDesktopServices>
#endif

static const QString VERSION_NUMBER("0.0.3");

#if (defined Q_WS_MAEMO_5) || (defined MEEGO_EDITION_HARMATTAN)
static const QString REMOTES_DIRECTORY("/home/user/MultiMote/remotes/");
#elif QT_VERSION >= 0x050000
static const QString REMOTES_DIRECTORY(QStandardPaths::writeableLocation(QStandardPaths::HomeLocation) + "/MultiMote/remotes/");
#else
static const QString REMOTES_DIRECTORY(QDesktopServices::storageLocation(QDesktopServices::HomeLocation) + "/MultiMote/remotes/");
#endif

#endif // DEFINITIONS_H
