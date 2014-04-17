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

#ifndef TIMER_H
#define TIMER_H

#include <QObject>

class Timer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int interval READ interval WRITE setInterval NOTIFY intervalChanged)
    Q_PROPERTY(bool repeat READ repeat WRITE setRepeat NOTIFY repeatChanged)
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(bool triggeredOnStart READ triggeredOnStart WRITE setTriggeredOnStart NOTIFY triggeredOnStartChanged)

public:
    explicit Timer(QObject *parent = 0);
    ~Timer();    

    int interval() const;
    void setInterval(int interval);

    bool repeat() const;
    void setRepeat(bool repeat);

    bool running() const;
    void setRunning(bool running);

    bool triggeredOnStart() const;
    void setTriggeredOnStart(bool triggered);

public slots:
    void restart();
    void start();
    void stop();

signals:
    void intervalChanged();
    void repeatChanged();
    void runningChanged();
    void triggeredOnStartChanged();
    void triggered();

private:
    void timerEvent(QTimerEvent *event);

    int m_timerId;

    int m_interval;

    bool m_repeat;

    bool m_running;

    bool m_triggeredOnStart;

    Q_DISABLE_COPY(Timer)
};

#endif // TIMER_H
