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

#include "numberpad.h"
#include <QPushButton>
#include <QGridLayout>

Numberpad::Numberpad(QWidget *parent) :
    QWidget(parent),
    ControlWidget()
{
    this->setContextMenuPolicy(Qt::ActionsContextMenu);

    QWidget *widget = new QWidget(this);
    m_grid = new QGridLayout(widget);
    m_grid->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setContentsMargins(0, 0, 0, 0);
    vbox->addWidget(widget, 0, Qt::AlignCenter);
}

Numberpad::~Numberpad() {}

QPushButton* Numberpad::button(ButtonRole role) const {
    return m_buttons.value(role, 0);
}

void Numberpad::addButton(QPushButton *button, ButtonRole role) {
    if (QPushButton *old = this->button(role)) {
        m_grid->removeWidget(old);
    }

    button->setParent(this);

    switch (role) {
    case One:
        m_grid->addWidget(button, 0, 0);
        break;
    case Two:
        m_grid->addWidget(button, 0, 1);
        break;
    case Three:
        m_grid->addWidget(button, 0, 2);
        break;
    case Four:
        m_grid->addWidget(button, 1, 0);
        break;
    case Five:
        m_grid->addWidget(button, 1, 1);
        break;
    case Six:
        m_grid->addWidget(button, 1, 2);
        break;
    case Seven:
        m_grid->addWidget(button, 2, 0);
        break;
    case Eight:
        m_grid->addWidget(button, 2, 1);
        break;
    case Nine:
        m_grid->addWidget(button, 2, 2);
        break;
    case Zero:
        m_grid->addWidget(button, 3, 1);
        break;
    case Back:
        m_grid->addWidget(button, 3, 0);
        break;
    case Forward:
        m_grid->addWidget(button, 3, 2);
        break;
    default:
        m_grid->addWidget(button, 1, 1);
        break;
    }

    m_buttons[role] = button;
}
