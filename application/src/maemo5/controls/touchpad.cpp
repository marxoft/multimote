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

#include "touchpad.h"
#include <QMouseEvent>
#include <QPainter>
#ifdef Q_WS_MAEMO_5
#include <QMaemo5Style>
#endif

Touchpad::Touchpad(QWidget *parent) :
    QWidget(parent),
    ControlWidget(),
    m_pressed(false)
{
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
}

bool Touchpad::isPressed() const {
    return m_pressed;
}

void Touchpad::setPressed(bool pressed) {
    if (pressed != this->isPressed()) {
        m_pressed = pressed;
        emit pressedChanged();
    }
}

QPoint Touchpad::mousePos() const {
    return m_pos;
}

void Touchpad::setMousePos(const QPoint &pos) {
    if (pos != this->mousePos()) {
        m_pos = pos;

        emit mousePosChanged(pos);
    }
}

int Touchpad::mouseX() const {
    return m_pos.x();
}

int Touchpad::mouseY() const {
    return m_pos.y();
}

void Touchpad::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    QRect backgroundRect = this->rect();
    backgroundRect.setBottomRight(QPoint(backgroundRect.right() - 1, backgroundRect.bottom() - 1));
#ifdef Q_WS_MAEMO_5
    painter.setPen(QMaemo5Style::standardColor("SecondaryTextColor"));
#else
    painter.setPen("#4d4d4d");
#endif
    painter.drawRect(backgroundRect);

    event->accept();
}

void Touchpad::mousePressEvent(QMouseEvent *event) {
    if (this->rect().contains(event->pos())) {
        this->setPressed(true);
    }
}

void Touchpad::mouseReleaseEvent(QMouseEvent *event) {
    this->setPressed(false);

    if (this->rect().contains(event->pos())) {
        emit clicked();
    }
}

void Touchpad::mouseDoubleClickEvent(QMouseEvent *event) {
    Q_UNUSED(event)

    emit doubleClicked();
}

void Touchpad::mouseMoveEvent(QMouseEvent *event) {
    this->setMousePos(event->pos());
}
