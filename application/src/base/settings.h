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

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

class Settings : public QSettings
{
    Q_OBJECT

    Q_PROPERTY(QString currentRemote READ currentRemote WRITE setCurrentRemote NOTIFY currentRemoteChanged)
    Q_PROPERTY(bool loadRemoteOnStartup READ loadRemoteOnStartup WRITE setLoadRemoteOnStartup NOTIFY loadRemoteOnStartupChanged)

public:
    explicit Settings(QObject *parent = 0);
    ~Settings();

    inline static Settings* instance() { return self; }
    
    QString currentRemote() const;
    void setCurrentRemote(const QString &remote);

    bool loadRemoteOnStartup() const;
    void setLoadRemoteOnStartup(bool load);

public slots:
    QVariant setting(const QString &key) const;
    void setSetting(const QString &key, const QVariant &value);

signals:
    void currentRemoteChanged();
    void loadRemoteOnStartupChanged();

private:
    static Settings *self;

    Q_DISABLE_COPY(Settings)
};

#endif // SETTINGS_H
