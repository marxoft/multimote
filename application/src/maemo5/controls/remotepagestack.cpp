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

#include "remotepagestack.h"
#include <QMouseEvent>

RemotePageStack::RemotePageStack(QWidget *parent) :
    QStackedWidget(parent),
    m_pressed(false)
{
    this->setFrameStyle(QFrame::NoFrame);
}

void RemotePageStack::mousePressEvent(QMouseEvent *event) {
    if (this->rect().contains(event->pos())) {
        m_pressed = true;
        m_oldPos = event->pos();
    }

    QStackedWidget::mousePressEvent(event);
}

void RemotePageStack::mouseReleaseEvent(QMouseEvent *event) {
    if (!m_pressed) {
        return;
    }

    m_pressed = false;

    if (this->rect().contains(event->pos())) {
        int xDiff = event->x() - m_oldPos.x();
        int yDiff = event->y() - m_oldPos.y();

        if ((qAbs(yDiff)) < (qAbs(xDiff) * 0.2)) {
            if (xDiff > 100) {
                event->accept();
                this->previousPage();
                return;
            }
            else if (xDiff < -100) {
                event->accept();
                this->nextPage();
                return;
            }
        }
    }

    QStackedWidget::mouseReleaseEvent(event);
}

void RemotePageStack::previousPage() {
    if (this->currentIndex() > 0) {
        this->setCurrentIndex(this->currentIndex() - 1);
    }
    else {
        this->setCurrentIndex(this->count() - 1);
    }
}

void RemotePageStack::nextPage() {
    if (this->currentIndex() < (this->count() - 1)) {
        this->setCurrentIndex(this->currentIndex() + 1);
    }
    else {
        this->setCurrentIndex(0);
    }
}
