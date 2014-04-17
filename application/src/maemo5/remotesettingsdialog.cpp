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

#include "remotesettingsdialog.h"
#include "separatorlabel.h"
#include "remotesettingsselector.h"
#include "remotesettingscheckbox.h"
#include "remotesettingsspinbox.h"
#include "remotesettingslineedit.h"
#include "../base/definitions.h"
#include "../base/screen.h"
#include "../base/selectionmodel.h"
#include <QFile>
#include <QGridLayout>
#include <QScrollArea>
#include <QDialogButtonBox>
#include <QXmlStreamReader>
#include <QDebug>

RemoteSettingsDialog::RemoteSettingsDialog(const QString &name, QWidget *parent) :
    QDialog(parent),
    m_scrollArea(new QScrollArea(this)),
    m_buttonBox(new QDialogButtonBox(QDialogButtonBox::Ok, Qt::Vertical, this)),
    m_grid(new QGridLayout(this))
{
    this->setWindowTitle(tr("%1 settings").arg(name));
    this->setAttribute(Qt::WA_DeleteOnClose, true);

    QWidget *scrollWidget = new QWidget(m_scrollArea);
    QVBoxLayout *vbox = new QVBoxLayout(scrollWidget);
    vbox->setContentsMargins(0, 0, 0, 0);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setWidget(scrollWidget);

    QFile file(REMOTES_DIRECTORY + name + "/settings.xml");

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Cannot open file" << file.fileName();
        return;
    }

    QXmlStreamReader reader;
    reader.setDevice(&file);
    reader.readNextStartElement();

    while (!reader.atEnd()) {
        if (!reader.attributes().isEmpty()) {
            if (reader.name() == "group") {
                vbox->addWidget(new SeparatorLabel(reader.attributes().value("name").toString(), this));
            }
            else if (reader.name() == "list") {
                RemoteSettingsSelector *selector = new RemoteSettingsSelector(reader.attributes().value("name").toString(), this);
                selector->setKey(QString("%1/%2").arg(name).arg(reader.attributes().value("key").toString()));
                selector->setDefaultValue(reader.attributes().value("default").toString());
                selector->setHandler(reader.attributes().value("onChanged").toString());
                reader.readNextStartElement();

                if (selector->model()) {
                    while (reader.name() == "element") {
                        if (!reader.attributes().isEmpty()) {
                            selector->model()->addItem(reader.attributes().value("name").toString(), reader.attributes().value("value").toString());
                        }

                        reader.readNextStartElement();
                    }
                }

                selector->load();
                vbox->addWidget(selector);
            }
            else if (reader.name() == "boolean") {
                RemoteSettingsCheckbox *checkbox = new RemoteSettingsCheckbox(this);
                checkbox->setText(reader.attributes().value("name").toString());
                checkbox->setKey(QString("%1/%2").arg(name).arg(reader.attributes().value("key").toString()));
                checkbox->setDefaultValue(reader.attributes().value("default").toString());
                checkbox->setHandler(reader.attributes().value("onChanged").toString());
                checkbox->load();
                vbox->addWidget(checkbox);
            }
            else if (reader.name() == "integer") {
                RemoteSettingsSpinbox *spinbox = new RemoteSettingsSpinbox(this);
                spinbox->setKey(QString("%1/%2").arg(name).arg(reader.attributes().value("key").toString()));
                spinbox->setDefaultValue(reader.attributes().value("default").toString());
                spinbox->setHandler(reader.attributes().value("onChanged").toString());
                spinbox->setMinimum(reader.attributes().value("minimum").toString().toInt());
                spinbox->setMaximum(reader.attributes().value("maximum").toString().toInt());
                spinbox->setSingleStep(reader.attributes().value("step").toString().toInt());
                spinbox->load();
                vbox->addWidget(new QLabel(reader.attributes().value("name").toString(), this));
                vbox->addWidget(spinbox);
            }
            else if (reader.name() == "text") {
                RemoteSettingsLineEdit *lineEdit = new RemoteSettingsLineEdit(this);
                lineEdit->setKey(QString("%1/%2").arg(name).arg(reader.attributes().value("key").toString()));
                lineEdit->setDefaultValue(reader.attributes().value("default").toString());
                lineEdit->setHandler(reader.attributes().value("onChanged").toString());
                lineEdit->load();
                vbox->addWidget(new QLabel(reader.attributes().value("name").toString(), this));
                vbox->addWidget(lineEdit);
            }
        }

        reader.readNextStartElement();
    }

    file.close();

    this->connect(Screen::instance(), SIGNAL(currentOrientationChanged(Qt::Orientation)), this, SLOT(onOrientationChanged(Qt::Orientation)));
    this->connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));

    this->onOrientationChanged(Screen::instance()->currentOrientation());
}

RemoteSettingsDialog::~RemoteSettingsDialog() {}

void RemoteSettingsDialog::onOrientationChanged(Qt::Orientation orientation) {
    switch (orientation) {
    case Qt::Vertical:
        this->loadPortraitLayout();
        return;
    default:
        this->loadLandscapeLayout();
        return;
    }
}

void RemoteSettingsDialog::loadPortraitLayout() {
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

void RemoteSettingsDialog::loadLandscapeLayout() {
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
