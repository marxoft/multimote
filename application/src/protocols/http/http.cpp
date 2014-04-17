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

#include "http.h"
#include "http_p.h"
#include "../../base/notifications.h"
#include "../../base/scriptengine.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QBuffer>

const int MAX_REDIRECTS = 8;

Http* Http::self = 0;

Http::Http(QObject *parent) :
    QObject(parent),
    d_ptr(new HttpPrivate(this))
{
    if (!self) {
        self = this;
    }
}

Http::Http(HttpPrivate &dd, QObject *parent) :
    QObject(parent),
    d_ptr(&dd)
{
    if (!self) {
        self = this;
    }
}

Http::~Http() {}

void Http::get(const QString &url, const QVariantMap &headers, const QString &callback) {
    Q_D(Http);

    Request request;
    request.method = Http::GET;
    request.url = url;
    request.headers = headers;
    request.sender = this->thisObject();
    request.callback = callback;
    d->requests.enqueue(request);

    if (d->requests.size() == 1) {
        d->performNextRequest();
    }
}

void Http::put(const QString &url, const QString &data, const QVariantMap &headers, const QString &callback) {
    Q_D(Http);

    Request request;
    request.method = Http::PUT;
    request.url = url;
    request.data = data;
    request.headers = headers;
    request.sender = this->thisObject();
    request.callback = callback;
    d->requests.enqueue(request);

    if (d->requests.size() == 1) {
        d->performNextRequest();
    }
}

void Http::post(const QString &url, const QString &data, const QVariantMap &headers, const QString &callback) {
    Q_D(Http);

    Request request;
    request.method = Http::POST;
    request.url = url;
    request.data = data;
    request.headers = headers;
    request.sender = this->thisObject();
    request.callback = callback;
    d->requests.enqueue(request);

    if (d->requests.size() == 1) {
        d->performNextRequest();
    }
}

void Http::deleteResource(const QString &url, const QVariantMap &headers, const QString &callback) {
    Q_D(Http);

    Request request;
    request.method = Http::DELETE;
    request.url = url;
    request.headers = headers;
    request.sender = this->thisObject();
    request.callback = callback;
    d->requests.enqueue(request);

    if (d->requests.size() == 1) {
        d->performNextRequest();
    }
}

void Http::send(const QString &verb, const QString &url, const QString &data, const QVariantMap &headers, const QString &callback) {
    Q_D(Http);

    Request request;
    request.method = Http::CUSTOM;
    request.verb = verb;
    request.url = url;
    request.data = data;
    request.headers = headers;
    request.sender = this->thisObject();
    request.callback = callback;
    d->requests.enqueue(request);

    if (d->requests.size() == 1) {
        d->performNextRequest();
    }
}

HttpPrivate::HttpPrivate(Http *parent) :
    q_ptr(parent),
    nam(new QNetworkAccessManager(parent)),
    reply(0),
    buffer(0),
    redirects(0)
{
}

HttpPrivate::~HttpPrivate() {
    if (reply) {
        delete reply;
        reply = 0;
    }

    if (buffer) {
        delete buffer;
        buffer = 0;
    }
}

void HttpPrivate::performNextRequest(bool isRedirect) {
    if (requests.isEmpty()) {
        return;
    }

    if (!isRedirect) {
        redirects = 0;
    }

    Request queuedRequest = requests.first();

    QNetworkRequest request(queuedRequest.url);

    QMapIterator<QString, QVariant> iterator(queuedRequest.headers);

    while (iterator.hasNext()) {
        iterator.next();
        request.setRawHeader(iterator.key().toUtf8(), iterator.value().toByteArray());
    }

    if (reply) {
        reply->deleteLater();
        reply = 0;
    }

    switch (queuedRequest.method) {
    case Http::PUT:
        reply = nam->put(request, queuedRequest.data.toUtf8());
        break;
    case Http::POST:
        reply = nam->post(request, queuedRequest.data.toUtf8());
        break;
    case Http::DELETE:
        reply = nam->deleteResource(request);
        break;
    case Http::CUSTOM:
        if (!queuedRequest.data.isEmpty()) {
            if (!buffer) {
                buffer = new QBuffer;
            }
            else if (buffer->isOpen()) {
                buffer->close();
            }

            buffer->setData(queuedRequest.data.toUtf8());
            buffer->open(QIODevice::ReadOnly);
        }

        reply = nam->sendCustomRequest(request, queuedRequest.verb.toUtf8(), buffer);
        break;
    default:
        reply = nam->get(request);
        break;
    }

    Http::connect(reply, SIGNAL(finished()), q_func(), SLOT(_q_onReplyFinished()));
}

void HttpPrivate::_q_onReplyFinished() {
    if ((!reply) || (requests.isEmpty())) {
        Notifications::error(Http::tr("Network error"));
        return;
    }

    QUrl redirect = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();

    if (!redirect.isEmpty()) {
        if (redirects < MAX_REDIRECTS) {
            requests[0].url = redirect;
            this->performNextRequest(true);
            return;
        }
        else {
            Notifications::error(Http::tr("Maximum redirects reached"));
        }
    }
    else {
        switch (reply->error()) {
        case QNetworkReply::NoError:
            break;
        default:
            Notifications::error(reply->errorString());
            break;
        }
    }

    Request queuedRequest = requests.dequeue();

    if (!queuedRequest.callback.isEmpty()) {
        QScriptValue val;

        if (queuedRequest.callback.startsWith("function")) {
            val = ScriptEngine::instance()->evaluate(QString("(%1)").arg(queuedRequest.callback));

            if (val.isFunction()) {
                val = val.call(queuedRequest.sender, QScriptValueList() << QString(reply->readAll()));
            }
        }
        else if (queuedRequest.sender.isValid()) {
            QScriptValue global = ScriptEngine::instance()->globalObject();
            val = global.property(queuedRequest.callback).call(queuedRequest.sender, QScriptValueList() << QString(reply->readAll()));
        }
        else {
            val = ScriptEngine::instance()->evaluate(QString("%1(\"%2\")").arg(queuedRequest.callback).arg(QString(reply->readAll())));
        }

        if (val.isError()) {
            QString errorString = val.toString();
            Notifications::error(Http::tr("Error calling %1: %2").arg(queuedRequest.callback)
                                 .arg(errorString.isEmpty() ? Http::tr("Unknown error") : errorString));
        }
    }

    if (!requests.isEmpty()) {
        this->performNextRequest();
    }
}

#include "moc_http.cpp"
