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

#ifndef HTTP_P_H
#define HTTP_P_H

#include "http.h"
#include <QQueue>
#include <QUrl>
#include <QScriptValue>

class QNetworkAccessManager;
class QNetworkReply;
class QBuffer;

struct Request {
    Http::Method method;
    QString verb;
    QUrl url;
    QString data;
    QVariantMap headers;
    QScriptValue sender;
    QString callback;
};

class HttpPrivate
{

public:
    HttpPrivate(Http *parent);
    virtual ~HttpPrivate();

    void performNextRequest(bool isRedirect = false);

    void _q_onReplyFinished();

    Http *q_ptr;

    QNetworkAccessManager *nam;

    QNetworkReply *reply;

    QBuffer *buffer;

    int redirects;

    QQueue<Request> requests;

    Q_DECLARE_PUBLIC(Http)
};

#endif // HTTP_P_H
