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

#include "dateselector.h"
#include <QMaemo5DatePickSelector>

DateSelector::DateSelector(QWidget *parent) :
    QMaemo5ValueButton(parent),
    m_selector(new QMaemo5DatePickSelector(this))
{
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
    this->setPickSelector(m_selector);
    this->connect(m_selector, SIGNAL(selected(QString)), this, SIGNAL(selected(QString)));
}

int DateSelector::minimumYear() const {
    return m_selector->minimumYear();
}

void DateSelector::setMinimumYear(int min) {
    m_selector->setMinimumYear(min);
}

int DateSelector::maximumYear() const {
    return m_selector->maximumYear();
}

void DateSelector::setMaximumYear(int max) {
    m_selector->setMaximumYear(max);
}

QDate DateSelector::currentDate() const {
    return m_selector->currentDate();
}

void DateSelector::setCurrentDate(const QDate &date) {
    m_selector->setCurrentDate(date);
}

int DateSelector::currentDay() const {
    return m_selector->currentDate().day();
}

int DateSelector::currentMonth() const {
    return m_selector->currentDate().month();
}

int DateSelector::currentYear() const {
    return m_selector->currentDate().year();
}

QString DateSelector::currentValueText() const {
    return m_selector->currentValueText();
}
