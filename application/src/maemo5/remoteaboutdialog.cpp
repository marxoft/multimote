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

#include "remoteaboutdialog.h"
#include "../base/definitions.h"
#include <QFile>
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QXmlStreamReader>
#include <QDebug>

RemoteAboutDialog::RemoteAboutDialog(const QString &name, QWidget *parent) :
    QDialog(parent)
{
    this->setWindowTitle(tr("About %1").arg(name));
    this->setAttribute(Qt::WA_DeleteOnClose, true);

    QScrollArea *scrollArea = new QScrollArea(this);
    QWidget *scrollWidget = new QWidget(scrollArea);
    QLabel *label = new QLabel(tr("There is no information on this remote."), scrollWidget);
    label->setWordWrap(true);
    QVBoxLayout *scrollVBox = new QVBoxLayout(scrollWidget);
    scrollVBox->setContentsMargins(0, 0, 0, 0);
    scrollVBox->addWidget(label);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(scrollWidget);

    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->addWidget(scrollArea);

    QFile file(REMOTES_DIRECTORY + name + "/remote.xml");

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Cannot open file" << file.fileName();
        return;
    }

    QXmlStreamReader reader;
    reader.setDevice(&file);
    reader.readNextStartElement();

    bool infoLoaded = false;
    bool versionLoaded = false;

    QString text;

    while (((!infoLoaded) || (!versionLoaded)) && (!reader.atEnd())) {
        if (reader.name() == "description") {
            text.append(reader.readElementText());
            infoLoaded = true;
        }
        else if (reader.name() == "version") {
            text.prepend(QString("%1: %2<br><br>").arg(tr("Version")).arg(reader.readElementText()));
            versionLoaded = true;
        }

        reader.readNextStartElement();
    }

    file.close();

    if (!text.isEmpty()) {
        label->setText(text);
    }
}

RemoteAboutDialog::~RemoteAboutDialog() {}
