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

#include "image.h"
#include <QPainter>
#include <QMouseEvent>
#include <QNetworkAccessManager>
#include <QNetworkReply>

QNetworkAccessManager* Image::networkManager = 0;

int Image::referenceCount = 0;

Image::Image(QWidget *parent) :
    QWidget(parent),
    ControlWidget(),
    m_reply(0),
    m_fillMode(Qt::KeepAspectRatio)
{
    this->setContextMenuPolicy(Qt::ActionsContextMenu);

    referenceCount++;
}

Image::~Image() {
    if (m_reply) {
        delete m_reply;
        m_reply = 0;
    }

    referenceCount--;

    if ((referenceCount <= 0) && (networkManager)) {
        delete networkManager;
        networkManager = 0;
    }
}

QString Image::source() const {
    return m_source;
}

void Image::setSource(const QString &source) {
    if (source != this->source()) {
        m_source = source;
        this->reload();
    }
}

Qt::AspectRatioMode Image::fillMode() const {
    return m_fillMode;
}

void Image::setFillMode(Qt::AspectRatioMode mode) {
    if (mode != this->fillMode()) {
        m_fillMode = mode;
        this->reload();
    }
}

void Image::clear() {
    m_image = QImage();
    this->update();
}

void Image::reload() {
    if (this->source().isEmpty()) {
        this->clear();
        return;
    }

    if (this->source().startsWith("http")) {
        this->downloadImage(QUrl(this->source()));
        return;
    }

    m_image = QImage(this->source()).scaled(this->size(), this->fillMode(), Qt::SmoothTransformation);
    this->update();
}

void Image::downloadImage(const QUrl &url) {
    if (!networkManager) {
        networkManager = new QNetworkAccessManager;
    }

    if (m_reply) {
        m_reply->deleteLater();
        m_reply = 0;
    }

    QNetworkRequest request(url);
    m_reply = networkManager->get(request);
    this->connect(m_reply, SIGNAL(finished()), this, SLOT(onReplyFinished()));
}

void Image::onReplyFinished() {
    if (!m_reply) {
        return;
    }

    switch (m_reply->error()) {
    case QNetworkReply::NoError:
        m_image.loadFromData(m_reply->readAll());
        m_image = m_image.scaled(this->size(), this->fillMode(), Qt::SmoothTransformation);
        this->update();
        return;
    default:
        return;
    }
}

void Image::paintEvent(QPaintEvent *event) {
    if (m_image.isNull()) {
        event->ignore();
        return;
    }

    QPainter painter(this);
    int x = 0;
    int y = 0;
    int widthDiff = this->width() - m_image.width();
    int heightDiff = this->height() - m_image.height();

    if (widthDiff) {
        x = this->rect().left() + widthDiff / 2;
    }

    if (heightDiff) {
        y = this->rect().top() + heightDiff / 2;
    }

    painter.drawImage(x, y, m_image);
    event->accept();
}

void Image::resizeEvent(QResizeEvent *event) {
    if (!m_image.isNull()) {
        this->reload();
    }

    QWidget::resizeEvent(event);
}

void Image::mousePressEvent(QMouseEvent *event) {
    if (this->rect().contains(event->pos())) {
        m_pressed = true;
        event->accept();
    }
    else {
        QWidget::mousePressEvent(event);
    }
}

void Image::mouseReleaseEvent(QMouseEvent *event) {
    if ((m_pressed) && (this->rect().contains(event->pos()))) {
        emit clicked();
        event->accept();
    }
    else {
        QWidget::mouseReleaseEvent(event);
    }

    m_pressed = false;
}
