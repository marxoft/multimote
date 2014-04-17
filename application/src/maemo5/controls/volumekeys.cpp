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

#include "volumekeys.h"
#include "../mainwindow.h"
#include <QKeyEvent>
#include <QX11Info>
#include <X11/Xlib.h>
#include <X11/Xatom.h>

int VolumeKeys::referenceCount = 0;

VolumeKeys::VolumeKeys(QObject *parent) :
    QObject(parent)
{
    referenceCount++;

    if (referenceCount == 1) {
        this->grabVolumeKeys(true);
    }
}

VolumeKeys::~VolumeKeys() {
    referenceCount--;

    if (referenceCount <= 0) {
        this->grabVolumeKeys(false);
    }
}

bool VolumeKeys::eventFilter(QObject *obj, QEvent *event) {
    switch (event->type()) {
    case 7:
        if (QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event)) {
            switch (keyEvent->key()) {
            case Qt::Key_F7:
                emit upPressed();
                return true;
            case Qt::Key_F8:
                emit downPressed();
                return true;
            default:
                break;
            }
        }

        break;
    default:
        break;
    }

    return QObject::eventFilter(obj, event);
}

void VolumeKeys::grabVolumeKeys(bool grab) {
    MainWindow *window = MainWindow::instance();

    if ((!window) || (!window->winId())) {
        qWarning("Can't grab keys unless we have a window id");
        return;
    }

    unsigned long val = (grab) ? 1 : 0;
    Atom atom = XInternAtom(QX11Info::display(), "_HILDON_ZOOM_KEY_ATOM", False);

    if (!atom) {
        qWarning("Unable to obtain _HILDON_ZOOM_KEY_ATOM. This example will only work "
                 "on a Maemo 5 device!");
        return;
    }

    XChangeProperty (QX11Info::display(),
                     window->winId(),
                     atom,
                     XA_INTEGER,
                     32,
                     PropModeReplace,
                     reinterpret_cast<unsigned char *>(&val),
                     1);
}
