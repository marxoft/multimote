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

#ifndef HTTP_H
#define HTTP_H

#include <QObject>
#include <QScriptable>
#include <QVariantMap>

class QUrl;

class HttpPrivate;

class Http : public QObject, public QScriptable
{
    Q_OBJECT

    Q_ENUMS(Method)

public:
    enum Method {
        GET = 0,
        PUT,
        POST,
        DELETE,
        CUSTOM
    };

    explicit Http(QObject *parent = 0);
    ~Http();

    inline static Http* instance() { return self; }

public slots:
    void get(const QString &url, const QVariantMap &headers = QVariantMap(), const QString &callback = QString());
    void put(const QString &url, const QString &data, const QVariantMap &headers = QVariantMap(), const QString &callback = QString());
    void post(const QString &url, const QString &data, const QVariantMap &headers = QVariantMap(), const QString &callback = QString());
    void deleteResource(const QString &url, const QVariantMap &headers = QVariantMap(), const QString &callback = QString());
    void send(const QString &verb, const QString &url, const QString &data = QString(), const QVariantMap &headers = QVariantMap(), const QString &callback = QString());

private:
    Http(HttpPrivate &dd, QObject *parent = 0);

    QScopedPointer<HttpPrivate> d_ptr;

    static Http *self;

    Q_DISABLE_COPY(Http)
    Q_DECLARE_PRIVATE(Http)

    Q_PRIVATE_SLOT(d_func(), void _q_onReplyFinished())
};

#endif
