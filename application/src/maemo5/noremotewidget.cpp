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

#include "noremotewidget.h"
#include "../base/definitions.h"
#include <QPainter>
#include <QPaintEvent>

NoRemoteWidget::NoRemoteWidget(QWidget *parent) :
    QWidget(parent)
{
}

NoRemoteWidget::~NoRemoteWidget() {}

void NoRemoteWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    QString title("MultiMote " + VERSION_NUMBER);
    QString description(tr("No remote loaded. Please choose a remote from the menu."));

    QFont bold;
    bold.setBold(true);
    bold.setPixelSize(52);

    QSize titleSize = QFontMetrics(bold).size(Qt::TextSingleLine, title);
    QSize descriptionSize = this->fontMetrics().size(Qt::TextSingleLine, description);
    QSize totalSize(qMax(titleSize.width(), descriptionSize.width()), 74 + descriptionSize.height());
    QRect content(this->rect().right() / 2 - totalSize.width() / 2, this->rect().bottom() / 2 - totalSize.height() / 2, totalSize.width(), totalSize.height());

    painter.drawPixmap(content.left(), content.top(), QPixmap("/usr/share/icons/hicolor/64x64/apps/multimote.png"));
    painter.save();
    painter.setFont(bold);
    painter.drawText(content.left() + 74, content.top(), titleSize.width(), titleSize.height(), Qt::AlignVCenter, title);
    painter.restore();
    painter.drawText(content.left(), content.top() + 74, descriptionSize.width(), descriptionSize.height(), Qt::AlignBottom, description);

    event->accept();
}
