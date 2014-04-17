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

#include "remoteloader.h"
#include "controls/controlloader.h"
#include "controls/remotepagestack.h"
#include "../base/scriptengine.h"
#include "../base/definitions.h"
#include "../base/settings.h"
#include "../base/screen.h"
#include <QPluginLoader>
#include <QDir>
#include <QDebug>

#if (defined Q_OS_SYMBIAN)
#define LIB_EXT "*.qtplugin"
#elif (defined Q_OS_UNIX)
#define LIB_EXT "*.so"
#else
#define LIB_EXT "*.dll"
#endif

RemoteLoader* RemoteLoader::self = 0;

RemoteLoader::RemoteLoader(QObject *parent) :
    QObject(parent)
{
    if (!self) {
        self = this;
    }
}

RemoteLoader::~RemoteLoader() {}

bool RemoteLoader::loadRemote(const QString &name) {
    if (!m_path.isEmpty()) {
        this->unloadRemote();
    }

    m_path = REMOTES_DIRECTORY + name;

    QFile file(m_path + "/remote.xml");

    qDebug() << "Loading remote at" << file.fileName();

    if ((file.open(QIODevice::ReadOnly)) && (m_xml.setContent(&file))) {
        QString orientation = m_xml.documentElement().firstChildElement("orientation").text();

        if (orientation.isEmpty()) {
            Screen::instance()->setOrientationLock(Qt::Horizontal);
        }
        else {
            Screen::instance()->setProperty("orientationLock", orientation);
        }

        m_remoteName = name;
        emit remoteChanged();

        return true;
    }

    return false;
}

bool RemoteLoader::unloadRemote() {
    qDebug() << "Unloading remote";
    m_xml.clear();

    if (m_loaders.isEmpty()) {
        return true;
    }

    foreach (QPluginLoader *loader, m_loaders) {
        loader->unload();
    }

    qDeleteAll(m_loaders);
    m_loaders.clear();

    return true;
}

RemotePageStack* RemoteLoader::loadUi() {
    qDebug() << "Loading remote ui";

    QDomElement remote = m_xml.documentElement();
    QDomNodeList pages = remote.elementsByTagName("page");

    if (pages.isEmpty()) {
        qDebug() << "No remote pages found";
        return 0;
    }

    return ControlLoader::loadPageStack(remote, true);
}

bool RemoteLoader::loadSettings() {
    qDebug() << "Loading remote settings";

    QFile file(m_path + "/settings.xml");

    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }

    QDomDocument xml;
    xml.setContent(&file);

    QDomElement remote = xml.documentElement();
    QDomNodeList settingsNodes = remote.childNodes();

    QString name = m_path.mid(m_path.lastIndexOf('/') + 1);
    Settings::instance()->beginGroup(name);

    for (int i = 0; i < settingsNodes.size(); i++) {
        QDomElement el = settingsNodes.at(i).toElement();
        QString key = el.attribute("key");
        QString handler = el.attribute("onChanged");
        QVariant value = Settings::instance()->value(key, el.attribute("default"));

        if (el.tagName() == "boolean") {
            ScriptEngine::instance()->globalObject().setProperty(key, value.toBool());
        }
        else if (el.tagName() == "integer") {
            ScriptEngine::instance()->globalObject().setProperty(key, value.toInt());
        }
        else {
            ScriptEngine::instance()->globalObject().setProperty(key, value.toString());
        }

        if (!handler.isEmpty()) {
            ScriptEngine::instance()->evaluate(handler);
        }
    }

    Settings::instance()->endGroup();

    return true;
}

bool RemoteLoader::loadPlugins() {
    qDebug() << "Loading remote plugins";

    QDir dir(m_path);
    QFile file;

    foreach (QString jsFile, dir.entryList(QStringList("*.js"), QDir::Files)) {
        file.setFileName(dir.absoluteFilePath(jsFile));

        if (file.open(QIODevice::ReadOnly)) {
            ScriptEngine::instance()->evaluate(file.readAll(), file.fileName());
            file.close();
        }
    }

    foreach(QString libFile, dir.entryList(QStringList(LIB_EXT), QDir::Files)) {
        QPluginLoader *loader = new QPluginLoader(dir.absoluteFilePath(libFile), this);
        QObject *plugin = loader->instance();

        if (plugin) {
            qDebug() << "Plugin loaded:" << plugin->objectName();
            m_loaders << loader;
            ScriptEngine::instance()->globalObject().setProperty(plugin->objectName(), ScriptEngine::instance()->newQObject(plugin));
        }
        else {
            qDebug() << "Error loading" << libFile << ":" << loader->errorString();
            loader->deleteLater();
        }
    }

    return true;
}
