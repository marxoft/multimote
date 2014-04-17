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

#include "aboutdialog.h"
#include "../base/definitions.h"
#include "../base/screen.h"
#include <QDesktopServices>
#include <QUrl>
#include <QLabel>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QGridLayout>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    m_container(new QWidget(this)),
    m_buttonBox(new QDialogButtonBox(Qt::Vertical, this)),
    m_grid(new QGridLayout(this))
{
    this->setWindowTitle(tr("About MultiMote"));
    this->setAttribute(Qt::WA_DeleteOnClose, true);

    QLabel *imageLabel = new QLabel(this);
    imageLabel->setFixedWidth(64);
    imageLabel->setPixmap(QPixmap("/usr/share/icons/hicolor/64x64/apps/multimote.png"));

    QLabel *titleLabel = new QLabel("MultiMote " + VERSION_NUMBER, this);
    titleLabel->setAlignment(Qt::AlignVCenter);
    titleLabel->setWordWrap(true);

    QFont bold;
    bold.setBold(true);
    bold.setPixelSize(52);
    titleLabel->setFont(bold);

    QLabel *descriptionLabel = new QLabel(QString("%1<br><br>&copy; Stuart Howarth 2014").arg(tr("A plugin-based remote control application.")), this);
    descriptionLabel->setWordWrap(true);

    QPushButton *donateButton = new QPushButton(tr("Donate"), this);
    QPushButton *bugButton = new QPushButton(tr("Report bug"), this);

    m_buttonBox->addButton(donateButton, QDialogButtonBox::ActionRole);
    m_buttonBox->addButton(bugButton, QDialogButtonBox::ActionRole);

    QGridLayout *grid = new QGridLayout(m_container);
    grid->addWidget(imageLabel, 0, 0);
    grid->addWidget(titleLabel, 0, 1);
    grid->addWidget(descriptionLabel, 1, 0, 1, 2);

    this->connect(Screen::instance(), SIGNAL(currentOrientationChanged(Qt::Orientation)), this, SLOT(onOrientationChanged(Qt::Orientation)));
    this->connect(donateButton, SIGNAL(clicked()), this, SLOT(donate()));
    this->connect(bugButton, SIGNAL(clicked()), this, SLOT(reportBug()));

    this->onOrientationChanged(Screen::instance()->currentOrientation());
}

AboutDialog::~AboutDialog() {}

void AboutDialog::onOrientationChanged(Qt::Orientation orientation) {
    switch (orientation) {
    case Qt::Vertical:
        this->loadPortraitLayout();
        return;
    default:
        this->loadLandscapeLayout();
        return;
    }
}

void AboutDialog::loadPortraitLayout() {
    m_buttonBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    if (m_grid->isEmpty()) {
        m_grid->addWidget(m_container, 0, 0, Qt::AlignBottom);
        m_grid->addWidget(m_buttonBox, 1, 0, Qt::AlignBottom);
    }
    else {
        m_grid->removeWidget(m_buttonBox);
        m_grid->addWidget(m_buttonBox, 1, 0, Qt::AlignBottom);
    }
}

void AboutDialog::loadLandscapeLayout() {
    m_buttonBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    if (m_grid->isEmpty()) {
        m_grid->addWidget(m_container, 0, 0, Qt::AlignBottom);
        m_grid->addWidget(m_buttonBox, 0, 1, Qt::AlignBottom);
    }
    else {
        m_grid->removeWidget(m_buttonBox);
        m_grid->addWidget(m_buttonBox, 0, 1, Qt::AlignBottom);
    }
}

void AboutDialog::donate() {
    QDesktopServices::openUrl(QUrl("https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=showarth@marxoft.co.uk&lc=GB&item_name=MultiMote&currency_code=USD&bn=PP%2dDonationsBF%3abtn_donate_SM%2egif%3aNonHosted"));
    this->accept();
}

void AboutDialog::reportBug() {
    QDesktopServices::openUrl(QUrl(QString("mailto:showarth@marxoft.co.uk?subject=MultiMote %1 for Maemo5").arg(VERSION_NUMBER)));
    this->accept();
}
