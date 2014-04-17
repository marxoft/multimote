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

#ifndef REMOTELOADER_H
#define REMOTELOADER_H

#include <QObject>
#include <QDomDocument>

class RemotePageStack;
class QPluginLoader;

class RemoteLoader : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString remoteName READ remoteName NOTIFY remoteChanged)

public:
    explicit RemoteLoader(QObject *parent = 0);
    ~RemoteLoader();

    inline static RemoteLoader* instance() { return self; }

    inline QString remoteName() const { return m_remoteName; }
        
    bool loadRemote(const QString &name);

    RemotePageStack* loadUi();

    bool loadSettings();
    bool loadPlugins();

private:
    bool unloadRemote();

signals:
    void remoteChanged();

private:
    static RemoteLoader *self;

    QString m_path;

    QDomDocument m_xml;

    QString m_remoteName;

    QList<QPluginLoader*> m_loaders;

    Q_DISABLE_COPY(RemoteLoader)
};

#endif // REMOTELOADER_H
