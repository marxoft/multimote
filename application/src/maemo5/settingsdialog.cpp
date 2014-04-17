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

#include "settingsdialog.h"
#include "../base/settings.h"
#include "../base/screen.h"
#include <QGridLayout>
#include <QDialogButtonBox>
#include <QScrollArea>
#include <QCheckBox>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    m_loadRemoteCheckbox(new QCheckBox(tr("Load last remote on startup"), this)),
    m_scrollArea(new QScrollArea(this)),
    m_buttonBox(new QDialogButtonBox(QDialogButtonBox::Save, Qt::Vertical, this)),
    m_grid(new QGridLayout(this))
{
    this->setWindowTitle(tr("MultiMote Settings"));
    this->setAttribute(Qt::WA_DeleteOnClose, true);

    QWidget *scrollWidget = new QWidget(m_scrollArea);
    QVBoxLayout *vbox = new QVBoxLayout(scrollWidget);
    vbox->setContentsMargins(0, 0, 0, 0);
    vbox->addWidget(m_loadRemoteCheckbox);

    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setWidget(scrollWidget);

    this->connect(Screen::instance(), SIGNAL(currentOrientationChanged(Qt::Orientation)), this, SLOT(onOrientationChanged(Qt::Orientation)));
    this->connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(saveSettings()));

    this->loadSettings();
    this->onOrientationChanged(Screen::instance()->currentOrientation());
}

SettingsDialog::~SettingsDialog() {}

void SettingsDialog::onOrientationChanged(Qt::Orientation orientation) {
    switch (orientation) {
    case Qt::Vertical:
        this->loadPortraitLayout();
        return;
    default:
        this->loadLandscapeLayout();
        return;
    }
}

void SettingsDialog::loadPortraitLayout() {
    m_buttonBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    if (m_grid->isEmpty()) {
        m_grid->addWidget(m_scrollArea, 0, 0, Qt::AlignBottom);
        m_grid->addWidget(m_buttonBox, 1, 0, Qt::AlignBottom);
    }
    else {
        m_grid->removeWidget(m_buttonBox);
        m_grid->addWidget(m_buttonBox, 1, 0, Qt::AlignBottom);
    }
}

void SettingsDialog::loadLandscapeLayout() {
    m_buttonBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    if (m_grid->isEmpty()) {
        m_grid->addWidget(m_scrollArea, 0, 0, Qt::AlignBottom);
        m_grid->addWidget(m_buttonBox, 0, 1, Qt::AlignBottom);
    }
    else {
        m_grid->removeWidget(m_buttonBox);
        m_grid->addWidget(m_buttonBox, 0, 1, Qt::AlignBottom);
    }
}

void SettingsDialog::loadSettings() {
    m_loadRemoteCheckbox->setChecked(Settings::instance()->loadRemoteOnStartup());
}

void SettingsDialog::saveSettings() {
    Settings::instance()->setLoadRemoteOnStartup(m_loadRemoteCheckbox->isChecked());

    this->accept();
}
