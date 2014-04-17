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

#include "dialog.h"
#include "../../base/screen.h"
#include <QShowEvent>
#include <QScrollArea>
#include <QGridLayout>
#include <QVariant>
#include <QDialogButtonBox>
#include <QPushButton>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ControlWidget(),
    m_scrollArea(new QScrollArea(this)),
    m_scrollWidget(new QWidget(m_scrollArea)),
    m_grid(new QGridLayout(m_scrollWidget)),
    m_buttonBox(0),
    m_outerGrid(new QGridLayout(this))
{
    this->setContextMenuPolicy(Qt::ActionsContextMenu);

    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setWidget(m_scrollWidget);
    m_grid->setContentsMargins(0, 0, 0, 0);

    this->connect(Screen::instance(), SIGNAL(currentOrientationChanged(Qt::Orientation)), this, SLOT(onOrientationChanged(Qt::Orientation)));
}

Dialog::~Dialog() {}

void Dialog::showEvent(QShowEvent *event) {
    if (m_outerGrid->isEmpty()) {
        this->onOrientationChanged(Screen::instance()->currentOrientation());
    }

    QWidget::showEvent(event);
}

void Dialog::addWidget(QWidget *widget) {
    widget->setParent(this);

    if (!widget->windowFlags().testFlag(Qt::Dialog)) {
        m_widgets << widget;
    }
}

void Dialog::addButton(QPushButton *button) {
    button->setParent(this);

    if (!m_buttonBox) {
#ifdef Q_WS_MAEMO_5
        m_buttonBox = new QDialogButtonBox(Qt::Vertical, this);
#else
        m_buttonBox = new QDialogButtonBox(Qt::Horizontal, this);
#endif
    }

    m_buttonBox->addButton(button, QDialogButtonBox::ActionRole);
}

void Dialog::clearLayout() {
    if (!m_grid->isEmpty()) {
        foreach (QWidget *widget, m_widgets) {
            m_grid->removeWidget(widget);
        }
    }
}

void Dialog::loadPortraitLayout() {
    this->clearLayout();

    if (this->heightPortrait()) {
        this->setFixedHeight(this->heightPortrait());
    }

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

    if (m_outerGrid->isEmpty()) {
        m_outerGrid->addWidget(m_scrollArea, 0, 0);

        if (m_buttonBox) {
            m_buttonBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
            m_outerGrid->addWidget(m_buttonBox, 1, 0);
        }
    }
    else if (m_buttonBox) {
        m_buttonBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        m_outerGrid->removeWidget(m_buttonBox);
        m_outerGrid->addWidget(m_buttonBox, 1, 0);
    }
}

void Dialog::loadLandscapeLayout() {
    this->clearLayout();

    if (this->heightLandscape()) {
        this->setFixedHeight(this->heightLandscape());
    }

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

    if (m_outerGrid->isEmpty()) {
        m_outerGrid->addWidget(m_scrollArea, 0, 0);

        if (m_buttonBox) {
            m_buttonBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
            m_outerGrid->addWidget(m_buttonBox, 0, 1);
        }
    }
    else if (m_buttonBox) {
        m_buttonBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        m_outerGrid->removeWidget(m_buttonBox);
        m_outerGrid->addWidget(m_buttonBox, 0, 1);
    }
}

void Dialog::onOrientationChanged(Qt::Orientation orientation) {
    switch (orientation) {
    case Qt::Vertical:
        this->loadPortraitLayout();
        return;
    default:
        this->loadLandscapeLayout();
        return;
    }
}
