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

#ifndef REMOTEPAGE_H
#define REMOTEPAGE_H

#include <QWidget>
#include <QList>

class QScrollArea;
class QGridLayout;

class RemotePage : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QString title READ windowTitle WRITE setWindowTitle)

public:
    explicit RemotePage(QWidget *parent = 0);
    ~RemotePage();
    
public slots:
    void addWidget(QWidget *widget);

private:
    void showEvent(QShowEvent *event);

    void clearLayout();
    void loadPortraitLayout();
    void loadLandscapeLayout();

private slots:
    void onOrientationChanged(Qt::Orientation orientation);
    
private:
    QScrollArea *m_scrollArea;
    QWidget *m_scrollWidget;
    QGridLayout *m_grid;

    QList<QWidget*> m_widgets;

    Q_DISABLE_COPY(RemotePage)
};

#endif // REMOTEPAGE_H
