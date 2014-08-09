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

#include "selectionitem.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>

QHash<QString, QIcon> SelectionItem::iconCache = QHash<QString, QIcon>();

QNetworkAccessManager* SelectionItem::networkManager = 0;

int SelectionItem::referenceCount = 0;

SelectionItem::SelectionItem(QObject *parent) :
    QObject(parent),
    m_reply(0)
{
    referenceCount++;
}

SelectionItem::SelectionItem(const QString &text, QObject *parent) :
    QObject(parent),
    m_reply(0),
    m_text(text)
{
    referenceCount++;
}

SelectionItem::SelectionItem(const QString &text, const QVariant &data, Qt::Alignment textAlignment, QObject *parent) :
    QObject(parent),
    m_reply(0),
    m_text(text),
    m_data(data),
    m_textAlignment(textAlignment)
{
    referenceCount++;
}

SelectionItem::SelectionItem(const QString &iconSource, const QString &text, const QVariant &data, Qt::Alignment textAlignment, QObject *parent) :
    QObject(parent),
    m_reply(0),
    m_text(text),
    m_data(data),
    m_textAlignment(textAlignment)
{
    this->setIconSource(iconSource);
    referenceCount++;
}

SelectionItem::~SelectionItem() {
    if (m_reply) {
        delete m_reply;
        m_reply = 0;
    }

    referenceCount--;

    if (referenceCount <= 0) {
        iconCache.clear();

        if (networkManager) {
            delete networkManager;
            networkManager = 0;
        }
    }
}

QIcon SelectionItem::icon() const {
    return m_icon;
}

void SelectionItem::setIcon(const QIcon &icon) {
    m_icon = icon;
    emit dataChanged();    
}

QString SelectionItem::iconSource() const {
    return m_iconSource;
}

void SelectionItem::setIconSource(const QString &source) {
    if (source != this->iconSource()) {
        m_iconSource = source;

        if (source.isEmpty()) {
            this->setIcon(QIcon());
            return;
        }

        if (iconCache.contains(source)) {
            this->setIcon(iconCache.value(source, QIcon()));
        }
        else if (!source.contains("/")) {
            QIcon icon = QIcon::fromTheme(source);
            iconCache[source] = icon;
            this->setIcon(icon);
        }
        else if (source.startsWith("http")) {
            this->downloadIcon();
        }
        else {
            QIcon icon(source);
            iconCache[source] = icon;
            this->setIcon(icon);
        }
    }
}

QString SelectionItem::text() const {
    return m_text;
}

void SelectionItem::setText(const QString &text) {
    if (text != this->text()) {
        m_text = text;
        emit dataChanged();
    }
}

QVariant SelectionItem::data() const {
    return m_data;
}

void SelectionItem::setData(const QVariant &data) {
    if (data != this->data()) {
        m_data = data;
        emit dataChanged();
    }
}

Qt::Alignment SelectionItem::textAlignment() const {
    return m_textAlignment;
}

void SelectionItem::setTextAlignment(Qt::Alignment alignment) {
    if (alignment != this->textAlignment()) {
        m_textAlignment = alignment;
        emit dataChanged();
    }
}

QVariant SelectionItem::data(int role) const {
    switch (role) {
    case Qt::DisplayRole:
    case TextRole:
        return this->text();
    case Qt::DecorationRole:
        return this->icon();
    case Qt::TextAlignmentRole:
    case TextAlignmentRole:
        return int (this->textAlignment());
    case DataRole:
        return this->data();
    case IconSourceRole:
        return this->iconSource();
    default:
        return QVariant();
    }
} 

void SelectionItem::downloadIcon() {
    if (!networkManager) {
        networkManager = new QNetworkAccessManager;
    }

    if (m_reply) {
        m_reply->deleteLater();
        m_reply = 0;
    }

    QNetworkRequest request(QUrl(this->iconSource()));
    m_reply = networkManager->get(request);
    this->connect(m_reply, SIGNAL(finished()), this, SLOT(onReplyFinished()));
}

void SelectionItem::onReplyFinished() {
    if (!m_reply) {
        return;
    }

    switch (m_reply->error()) {
    case QNetworkReply::NoError:
        break;
    default:
        return;
    }

    QPixmap pixmap;
    
    if (pixmap.loadFromData(m_reply->readAll())) {
        QIcon icon(pixmap);
        iconCache[m_reply->request().url().toString()] = icon;
        this->setIcon(icon);
    }
}
