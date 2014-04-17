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

#include "mainwindow.h"
#include "noremotewidget.h"
#include "remoteloader.h"
#include "remotesettingsdialog.h"
#include "remoteaboutdialog.h"
#include "settingsdialog.h"
#include "aboutdialog.h"
#include "valueselectoraction.h"
#include "controls/remotepagestack.h"
#include "../base/remotelistmodel.h"
#include "../base/scriptengine.h"
#include "../base/settings.h"
#include "../base/screen.h"
#include <QMenuBar>
#include <QLabel>

MainWindow* MainWindow::self = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_remoteSelectorAction(new ValueSelectorAction(this)),
    m_remoteSettingsAction(this->menuBar()->addAction(tr("Remote settings"), this, SLOT(showRemoteSettingsDialog()))),
    m_remoteAboutAction(this->menuBar()->addAction(tr("About remote"), this, SLOT(showRemoteAboutDialog()))),
    m_settingsAction(this->menuBar()->addAction(tr("MultiMote settings"), this, SLOT(showSettingsDialog()))),
    m_aboutAction(this->menuBar()->addAction(tr("About MultiMote"), this, SLOT(showAboutDialog())))
{
    if (!self) {
        self = this;
    }

    this->setWindowTitle("MultiMote");
    this->menuBar()->insertAction(m_remoteSettingsAction, m_remoteSelectorAction);

    Settings *settings = new Settings(this);
    new ScriptEngine(this);
    new RemoteLoader(this);

    m_remoteSelectorAction->setText(tr("Remote"));
    m_remoteSelectorAction->setModel(new RemoteListModel(m_remoteSelectorAction));
    m_remoteSettingsAction->setEnabled(false);
    m_remoteAboutAction->setEnabled(false);

    this->connect(Screen::instance(), SIGNAL(orientationLockChanged(Qt::Orientations)), this, SLOT(onOrientationLockChanged(Qt::Orientations)));
    this->connect(m_remoteSelectorAction, SIGNAL(valueChanged(QVariant)), this, SLOT(loadRemote(QVariant)));

    if (settings->loadRemoteOnStartup()) {
        QString remote = settings->currentRemote();

        if (!remote.isEmpty()) {
            m_remoteSelectorAction->setValue(remote);
            this->loadRemote(remote);
            return;
        }
    }

    this->setCentralWidget(new NoRemoteWidget(this));
}

MainWindow::~MainWindow() {}

void MainWindow::loadRemote(const QVariant &value) {
    if (RemoteLoader::instance()->loadRemote(value.toString())) {
        Settings::instance()->setCurrentRemote(RemoteLoader::instance()->remoteName());
        QWidget *oldWidget = this->centralWidget();
        this->setCentralWidget(RemoteLoader::instance()->loadUi());
        this->setWindowTitle(RemoteLoader::instance()->remoteName());
        m_remoteSettingsAction->setText(tr("%1 settings").arg(RemoteLoader::instance()->remoteName()));
        m_remoteSettingsAction->setEnabled(RemoteLoader::instance()->loadSettings());
        m_remoteAboutAction->setText(tr("About %1").arg(RemoteLoader::instance()->remoteName()));
        m_remoteAboutAction->setEnabled(true);
        RemoteLoader::instance()->loadPlugins();

        if (oldWidget) {
            oldWidget->deleteLater();
        }
    }
}

void MainWindow::showRemoteSettingsDialog() {
    RemoteSettingsDialog *dialog = new RemoteSettingsDialog(RemoteLoader::instance()->remoteName(), this);
    dialog->open();
}

void MainWindow::showSettingsDialog() {
    SettingsDialog *dialog = new SettingsDialog(this);
    dialog->open();
}

void MainWindow::showRemoteAboutDialog() {
    RemoteAboutDialog *dialog = new RemoteAboutDialog(RemoteLoader::instance()->remoteName(), this);
    dialog->open();
}

void MainWindow::showAboutDialog() {
    AboutDialog *dialog = new AboutDialog(this);
    dialog->open();
}

void MainWindow::onOrientationLockChanged(Qt::Orientations lock) {
    if ((lock.testFlag(Qt::Horizontal)) && (lock.testFlag(Qt::Vertical))) {
        this->setAttribute(Qt::WA_Maemo5AutoOrientation, true);
    }
    else if (lock.testFlag(Qt::Vertical)) {
        this->setAttribute(Qt::WA_Maemo5PortraitOrientation, true);
    }
    else {
        this->setAttribute(Qt::WA_Maemo5LandscapeOrientation, true);
    }
}
