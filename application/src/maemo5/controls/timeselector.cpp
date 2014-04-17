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

#include "timeselector.h"
#include <QMaemo5TimePickSelector>

TimeSelector::TimeSelector(QWidget *parent) :
    QMaemo5ValueButton(parent),
    m_selector(new QMaemo5TimePickSelector(this))
{
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
    this->setPickSelector(m_selector);
    this->connect(m_selector, SIGNAL(selected(QString)), this, SIGNAL(selected(QString)));
}

int TimeSelector::minuteStep() const {
    return m_selector->minuteStep();
}

void TimeSelector::setMinuteStep(int step) {
    m_selector->setMinuteStep(step);
}

QTime TimeSelector::currentTime() const {
    return m_selector->currentTime();
}

void TimeSelector::setCurrentTime(const QTime &time) {
    m_selector->setCurrentTime(time);
}

int TimeSelector::currentHour() const {
    return m_selector->currentTime().hour();
}

int TimeSelector::currentMinute() const {
    return m_selector->currentTime().minute();
}

QString TimeSelector::currentValueText() const {
    return m_selector->currentValueText();
}
