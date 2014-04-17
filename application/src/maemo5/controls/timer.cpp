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

#include "timer.h"
#include <QTimerEvent>

Timer::Timer(QObject *parent) :
    QObject(parent),
    m_timerId(0),
    m_interval(1000),
    m_repeat(false),
    m_running(false),
    m_triggeredOnStart(false)
{
}

Timer::~Timer() {
    this->stop();
}

int Timer::interval() const {
    return m_interval;
}

void Timer::setInterval(int interval) {
    if (interval != this->interval()) {
        m_interval = interval;
        emit intervalChanged();

        if (this->running()) {
            this->restart();
        }
    }
}

bool Timer::repeat() const {
    return m_repeat;
}

void Timer::setRepeat(bool repeat) {
    if (repeat != this->repeat()) {
        m_repeat = repeat;
        emit repeatChanged();
    }
}

bool Timer::running() const {
    return m_running;
}

void Timer::setRunning(bool running) {
    if (running) {
        if (!this->running()) {
            this->start();
        }
    }
    else if (this->running()) {
        this->stop();
    }
}

bool Timer::triggeredOnStart() const {
    return m_triggeredOnStart;
}

void Timer::setTriggeredOnStart(bool triggered) {
    if (triggered != this->triggeredOnStart()) {
        m_triggeredOnStart = triggered;
        emit triggeredOnStartChanged();
    }
}

void Timer::restart() {
    if (this->running()) {
        this->stop();
    }

    this->start();
}

void Timer::start() {
    if (this->running()) {
        return;
    }

    m_timerId = this->startTimer(this->interval());

    if (m_timerId > 0) {
        m_running = true;
        emit runningChanged();

        if (this->triggeredOnStart()) {
            emit triggered();
        }
    }
}

void Timer::stop() {
    if (this->running()) {
        this->killTimer(m_timerId);
        m_running = false;
        emit runningChanged();
    }
}

void Timer::timerEvent(QTimerEvent *event) {
    event->accept();

    if (!this->repeat()) {
        this->stop();
    }

    emit triggered();
}
