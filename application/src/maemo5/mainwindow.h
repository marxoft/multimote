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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class ValueSelectorAction;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    inline static MainWindow* instance() { return self; }

private slots:
    void loadRemote(const QVariant &value);
    void showRemoteSettingsDialog();
    void showSettingsDialog();
    void showRemoteAboutDialog();
    void showAboutDialog();
    void onOrientationLockChanged(Qt::Orientations lock);

private:
    static MainWindow *self;

    ValueSelectorAction *m_remoteSelectorAction;
    QAction *m_remoteSettingsAction;
    QAction *m_remoteAboutAction;
    QAction *m_settingsAction;
    QAction *m_aboutAction;

    Q_DISABLE_COPY(MainWindow)
};

#endif // MAINWINDOW_H
