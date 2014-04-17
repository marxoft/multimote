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

#ifndef REMOTESETTINGSSLIDER_H
#define REMOTESETTINGSSLIDER_H

#include <QSlider>
#include <QVariant>

class RemoteSettingsSlider : public QSlider
{
    Q_OBJECT

public:
    explicit RemoteSettingsSlider(QWidget *parent = 0);
    ~RemoteSettingsSlider();

    inline QString key() const { return m_key; }
    inline QVariant defaultValue() const { return m_default; }
    inline QString handler() const { return m_handler; }
    
public slots:
    void setKey(const QString &key);
    void setDefaultValue(const QVariant &value);
    void setHandler(const QString &handler);
    void load();

private slots:
    void onReleased();

private:
    QString m_key;
    QVariant m_default;
    QString m_handler;

    Q_DISABLE_COPY(RemoteSettingsSlider)
};

#endif // REMOTESETTINGSSLIDER_H
