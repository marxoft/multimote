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

#include "multilistselector.h"
#include "listview.h"
#include "../../base/screen.h"
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QPainter>

MultiListSelector::MultiListSelector(QWidget *parent) :
    QMaemo5ValueButton(parent),
    ControlWidget(),
    m_dialog(new MultiListPickDialog(this)),
    m_selector(new MultiListPickSelector(m_dialog, this))
{
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
    this->setPickSelector(m_selector);
    this->setValueText(tr("None chosen"));
    this->connect(m_dialog->view(), SIGNAL(countChanged(int)), this, SIGNAL(countChanged(int)));
}

int MultiListSelector::count() const {
    return m_dialog->view()->count();
}

QVariantList MultiListSelector::currentIndexes() const {
    QVariantList list;

    foreach (QModelIndex index, m_dialog->view()->selectionModel()->selectedRows()) {
        list.append(index.row());
    }

    return list;
}

void MultiListSelector::setCurrentIndexes(const QVariantList &rows) {
    foreach (QVariant row, rows) {
        m_dialog->view()->selectionModel()->select(m_dialog->view()->model()->index(row.toInt(), 0), QItemSelectionModel::Select);
    }
}

QVariantList MultiListSelector::currentValues() const {
    QVariantList list;

    foreach (QModelIndex index, m_dialog->view()->selectionModel()->selectedRows()) {
        list.append(index.data(Qt::UserRole + 1));
    }

    return list;
}

void MultiListSelector::setCurrentValues(const QVariantList &values) {
    foreach (QVariant value, values) {
        for (int i = 0; i < m_dialog->view()->count(); i++) {
            const QModelIndex index = m_dialog->view()->model()->index(i, 0);

            if (index.data(Qt::UserRole + 1) == value) {
                m_dialog->view()->selectionModel()->select(index, QItemSelectionModel::Select);
                break;
            }
        }
    }
}

void MultiListSelector::addItem(const QString &name, const QVariant &value, Qt::Alignment textAlignment) {
    m_dialog->view()->addItem(name, value, textAlignment);
}

void MultiListSelector::addItem(const QString &iconSource, const QString &name, const QVariant &value, Qt::Alignment textAlignment) {
    m_dialog->view()->addItem(iconSource, name, value, textAlignment);
}

void MultiListSelector::insertItem(int row, const QString &name, const QVariant &value, Qt::Alignment textAlignment) {
    m_dialog->view()->insertItem(row, name, value, textAlignment);
}

void MultiListSelector::insertItem(int row, const QString &iconSource, const QString &name, const QVariant &value, Qt::Alignment textAlignment) {
    m_dialog->view()->insertItem(row, iconSource, name, value, textAlignment);
}

bool MultiListSelector::removeItem(int row) {
    return m_dialog->view()->removeItem(row);
}

void MultiListSelector::clear() {
    m_dialog->view()->clear();
}

void MultiListSelector::sort(Qt::SortOrder order) {
    m_dialog->view()->sort(order);
}

MultiListPickSelector::MultiListPickSelector(MultiListPickDialog *dialog, QObject *parent) :
    QMaemo5AbstractPickSelector(parent),
    m_dialog(dialog)
{
    this->connect(dialog, SIGNAL(accepted()), this, SLOT(onDialogAccepted()));
}

QWidget* MultiListPickSelector::widget(QWidget *parent) {
    if (QAbstractButton *button = qobject_cast<QAbstractButton*>(parent)) {
        m_dialog->setWindowTitle(button->text());
    }

    return m_dialog;
}

QString MultiListPickSelector::currentValueText() const {
    QStringList list;

    foreach (QModelIndex index, m_dialog->view()->selectionModel()->selectedRows()) {
        list.append(index.data().toString());
    }

    return list.join(", ");
}

void MultiListPickSelector::onDialogAccepted() {
    emit selected(this->currentValueText());
}

MultiListPickDialog::MultiListPickDialog(QWidget *parent) :
    QDialog(parent),
    m_view(new ListView(this)),
    m_buttonBox(new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Vertical, this)),
    m_grid(new QGridLayout(this))
{
    m_view->setSelectionMode(QListView::MultiSelection);
    m_view->setItemDelegate(new MultiListPickDelegate(m_view));
    m_view->setMinimumHeight((m_view->count() > 0 ? m_view->sizeHintForRow(0) : 70) * 5);

    this->connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    this->connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    this->connect(Screen::instance(), SIGNAL(currentOrientationChanged(Qt::Orientation)), this, SLOT(onOrientationChanged(Qt::Orientation)));
    this->onOrientationChanged(Screen::instance()->currentOrientation());
}

ListView* MultiListPickDialog::view() const {
    return m_view;
}

void MultiListPickDialog::setView(ListView *view) {
    m_view = view;
}

void MultiListPickDialog::onOrientationChanged(Qt::Orientation orientation) {
    switch (orientation) {
    case Qt::Vertical:
        this->loadPortraitLayout();
        return;
    default:
        this->loadLandscapeLayout();
        return;
    }
}

void MultiListPickDialog::loadPortraitLayout() {
    m_buttonBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    if (m_grid->isEmpty()) {
        m_grid->addWidget(m_view, 0, 0, Qt::AlignBottom);
        m_grid->addWidget(m_buttonBox, 1, 0, Qt::AlignBottom);
    }
    else {
        m_grid->removeWidget(m_buttonBox);
        m_grid->addWidget(m_buttonBox, 1, 0, Qt::AlignBottom);
    }
}

void MultiListPickDialog::loadLandscapeLayout() {
    m_buttonBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    if (m_grid->isEmpty()) {
        m_grid->addWidget(m_view, 0, 0, Qt::AlignBottom);
        m_grid->addWidget(m_buttonBox, 0, 1, Qt::AlignBottom);
    }
    else {
        m_grid->removeWidget(m_buttonBox);
        m_grid->addWidget(m_buttonBox, 0, 1, Qt::AlignBottom);
    }
}

void MultiListPickDialog::reject() {
    m_view->selectionModel()->select(m_itemSelection, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
    QDialog::reject();
}

void MultiListPickDialog::showEvent(QShowEvent *event) {
    m_itemSelection = m_view->selectionModel()->selection();
    QDialog::showEvent(event);
}

MultiListPickDelegate::MultiListPickDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

void MultiListPickDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyledItemDelegate::paint(painter, option, index);

    if ((option.state) & (QStyle::State_Selected)) {
        painter->drawImage(option.rect.right() - 48, option.rect.top() + ((option.rect.height() - 48) / 2),
                           QImage("/usr/share/icons/hicolor/48x48/hildon/widgets_tickmark_grid.png"));
    }
}
