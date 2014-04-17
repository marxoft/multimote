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

#include "remotepage.h"
#include "../../base/screen.h"
#include <QShowEvent>
#include <QScrollArea>
#include <QGridLayout>
#include <QVariant>

RemotePage::RemotePage(QWidget *parent) :
    QWidget(parent),
    m_scrollArea(new QScrollArea(this)),
    m_scrollWidget(new QWidget(m_scrollArea)),
    m_grid(new QGridLayout(m_scrollWidget))
{
    this->setContextMenuPolicy(Qt::ActionsContextMenu);

    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setWidget(m_scrollWidget);
    m_grid->setContentsMargins(0, 0, 0, 0);
    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->addWidget(m_scrollArea);

    this->connect(Screen::instance(), SIGNAL(currentOrientationChanged(Qt::Orientation)), this, SLOT(onOrientationChanged(Qt::Orientation)));
}

RemotePage::~RemotePage() {}

void RemotePage::showEvent(QShowEvent *event) {
    if (m_grid->isEmpty()) {
        this->onOrientationChanged(Screen::instance()->currentOrientation());
    }

    QWidget::showEvent(event);
}

void RemotePage::addWidget(QWidget *widget) {
    widget->setParent(this);

    if (!widget->windowFlags().testFlag(Qt::Dialog)) {
        m_widgets << widget;
    }
}

void RemotePage::clearLayout() {
    if (!m_grid->isEmpty()) {
        foreach (QWidget *widget, m_widgets) {
            m_grid->removeWidget(widget);
        }
    }
}

void RemotePage::loadPortraitLayout() {
    this->clearLayout();

    foreach (QWidget *widget, m_widgets) {
        int width = widget->property("widthPortrait").toInt();

        if (width) {
            widget->setFixedWidth(width);
        }

        int height = widget->property("heightPortrait").toInt();

        if (height) {
            widget->setFixedHeight(height);
        }

        int align = widget->property("alignmentPortrait").toInt();

        if (!align) {
            m_grid->addWidget(widget,
                              widget->property("rowPortrait").toInt(),
                              widget->property("columnPortrait").toInt(),
                              widget->property("rowSpanPortrait").toInt(),
                              widget->property("colSpanPortrait").toInt());
        }
        else {
            m_grid->addWidget(widget,
                              widget->property("rowPortrait").toInt(),
                              widget->property("columnPortrait").toInt(),
                              widget->property("rowSpanPortrait").toInt(),
                              widget->property("colSpanPortrait").toInt(),
                              static_cast<Qt::Alignment>(align));
        }
    }
}

void RemotePage::loadLandscapeLayout() {
    this->clearLayout();

    foreach (QWidget *widget, m_widgets) {
        int width = widget->property("widthLandscape").toInt();

        if (width) {
            widget->setFixedWidth(width);
        }

        int height = widget->property("heightLandscape").toInt();

        if (height) {
            widget->setFixedHeight(height);
        }

        int align = widget->property("alignmentLandscape").toInt();

        if (!align) {
            m_grid->addWidget(widget,
                              widget->property("rowLandscape").toInt(),
                              widget->property("columnLandscape").toInt(),
                              widget->property("rowSpanLandscape").toInt(),
                              widget->property("colSpanLandscape").toInt());
        }
        else {
            m_grid->addWidget(widget,
                              widget->property("rowLandscape").toInt(),
                              widget->property("columnLandscape").toInt(),
                              widget->property("rowSpanLandscape").toInt(),
                              widget->property("colSpanLandscape").toInt(),
                              static_cast<Qt::Alignment>(align));
        }
    }
}

void RemotePage::onOrientationChanged(Qt::Orientation orientation) {
    switch (orientation) {
    case Qt::Vertical:
        this->loadPortraitLayout();
        return;
    default:
        this->loadLandscapeLayout();
        return;
    }
}
