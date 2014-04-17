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

#ifndef SCREEN_H
#define SCREEN_H

#include <QObject>

class ScreenPrivate;

class Screen : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int width READ width NOTIFY widthChanged)
    Q_PROPERTY(int height READ height NOTIFY heightChanged)
    Q_PROPERTY(Qt::Orientations orientationLock READ orientationLock WRITE setOrientationLock NOTIFY orientationLockChanged)
    Q_PROPERTY(Qt::Orientation currentOrientation READ currentOrientation NOTIFY currentOrientationChanged)
    Q_PROPERTY(bool inPortrait READ inPortrait NOTIFY currentOrientationChanged)
    Q_PROPERTY(bool locked READ locked NOTIFY lockStateChanged)

public:
    explicit Screen(QObject *parent = 0);
    ~Screen();

    inline static Screen* instance() { return self; }

    int width() const;
    int height() const;

    Qt::Orientations orientationLock() const;
    void setOrientationLock(Qt::Orientations lock);

    Qt::Orientation currentOrientation() const;

    bool inPortrait() const;

    bool locked() const;

signals:
    void widthChanged(int width);
    void heightChanged(int height);
    void orientationLockChanged(Qt::Orientations lock);
    void currentOrientationChanged(Qt::Orientation current);
    void lockStateChanged(bool locked);

private:
    static Screen *self;

    QScopedPointer<ScreenPrivate> d_ptr;

    Q_DISABLE_COPY(Screen)
    Q_DECLARE_PRIVATE(Screen)

    Q_PRIVATE_SLOT(d_func(), void _q_onResized())
    Q_PRIVATE_SLOT(d_func(), void _q_onLockStateChanged(QString))
};

#endif // SCREEN_H
