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

#ifndef REMOTEPAGESTACK_H
#define REMOTEPAGESTACK_H

#include <QStackedWidget>

class RemotePageStack : public QStackedWidget
{
    Q_OBJECT

    Q_PROPERTY(QString title READ windowTitle WRITE setWindowTitle)
    Q_PROPERTY(QWidget* currentPage READ currentWidget WRITE setCurrentWidget NOTIFY currentChanged)

public:
    explicit RemotePageStack(QWidget *parent = 0);

public slots:
    void previousPage();
    void nextPage();
    
private:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    bool m_pressed;

    QPoint m_oldPos;

    Q_DISABLE_COPY(RemotePageStack)
};

#endif // REMOTEPAGESTACK_H
