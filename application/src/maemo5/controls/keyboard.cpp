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

#include "keyboard.h"
#include <QKeyEvent>

Keyboard::Keyboard(QObject *parent) :
    QObject(parent)
{
}

bool Keyboard::eventFilter(QObject *obj, QEvent *event) {
    switch (event->type()) {
    case QEvent::KeyRelease:
        if (QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event)) {
            switch (keyEvent->key()) {
            case Qt::Key_F7:
            case Qt::Key_F8:
                break;
            default:
                emit keyPressed(keyEvent);
                return true;
            }
        }

        break;
    default:
        break;
    }

    return QObject::eventFilter(obj, event);
}
