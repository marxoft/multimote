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

#ifndef REMOTESETTINGSDIALOG_H
#define REMOTESETTINGSDIALOG_H

#include <QDialog>

class QScrollArea;
class QDialogButtonBox;
class QGridLayout;

class RemoteSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RemoteSettingsDialog(const QString &name, QWidget *parent = 0);
    ~RemoteSettingsDialog();

private:
    void loadPortraitLayout();
    void loadLandscapeLayout();

private slots:
    void onOrientationChanged(Qt::Orientation orientation);

private:
    QScrollArea *m_scrollArea;
    QDialogButtonBox *m_buttonBox;
    QGridLayout *m_grid;

    Q_DISABLE_COPY(RemoteSettingsDialog)
};

#endif // REMOTESETTINGSDIALOG_H
