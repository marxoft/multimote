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

#ifndef LISTVIEW_H
#define LISTVIEW_H

#include "controlwidget.h"
#include <QListView>

class SelectionModel;
class QStandardItem;

class ListView : public QListView, public ControlWidget
{
    Q_OBJECT

    Q_PROPERTY(int width READ width WRITE setFixedWidth)
    Q_PROPERTY(int height READ height WRITE setFixedHeight)
    Q_PROPERTY(int widthPortrait READ widthPortrait WRITE setWidthPortrait SCRIPTABLE false)
    Q_PROPERTY(int widthLandscape READ widthLandscape WRITE setWidthLandscape SCRIPTABLE false)
    Q_PROPERTY(int heightPortrait READ heightPortrait WRITE setHeightPortrait SCRIPTABLE false)
    Q_PROPERTY(int heightLandscape READ heightLandscape WRITE setHeightLandscape SCRIPTABLE false)
    Q_PROPERTY(int rowPortrait READ rowPortrait WRITE setRowPortrait SCRIPTABLE false)
    Q_PROPERTY(int rowLandscape READ rowLandscape WRITE setRowLandscape SCRIPTABLE false)
    Q_PROPERTY(int columnPortrait READ columnPortrait WRITE setColumnPortrait SCRIPTABLE false)
    Q_PROPERTY(int columnLandscape READ columnLandscape WRITE setColumnLandscape SCRIPTABLE false)
    Q_PROPERTY(int rowSpanPortrait READ rowSpanPortrait WRITE setRowSpanPortrait SCRIPTABLE false)
    Q_PROPERTY(int rowSpanLandscape READ rowSpanLandscape WRITE setRowSpanLandscape SCRIPTABLE false)
    Q_PROPERTY(int colSpanPortrait READ colSpanPortrait WRITE setColSpanPortrait SCRIPTABLE false)
    Q_PROPERTY(int colSpanLandscape READ colSpanLandscape WRITE setColSpanLandscape SCRIPTABLE false)
    Q_PROPERTY(Qt::Alignment alignmentPortrait READ alignmentPortrait WRITE setAlignmentPortrait SCRIPTABLE false)
    Q_PROPERTY(Qt::Alignment alignmentLandscape READ alignmentLandscape WRITE setAlignmentLandscape SCRIPTABLE false)
    Q_PROPERTY(QStandardItem* currentItem READ currentItem NOTIFY currentItemChanged)
    Q_PROPERTY(int currentIndex READ currentRow WRITE setCurrentRow NOTIFY currentItemChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(bool multiSelection READ multiSelection WRITE setMultiSelection)

public:
    explicit ListView(QWidget *parent = 0);

    bool multiSelection() const;
    void setMultiSelection(bool multi);

    int count() const;

    QStandardItem* currentItem() const;

    int currentRow() const;
    void setCurrentRow(int row);

public slots:
    void addItem(const QString &name, const QVariant &value, Qt::Alignment textAlignment = Qt::AlignVCenter);
    void addItem(const QString &iconSource, const QString &name, const QVariant &value, Qt::Alignment textAlignment = Qt::AlignVCenter);

    void insertItem(int row, const QString &name, const QVariant &value, Qt::Alignment textAlignment = Qt::AlignVCenter);
    void insertItem(int row, const QString &iconSource, const QString &name, const QVariant &value, Qt::Alignment textAlignment = Qt::AlignVCenter);

    bool removeItem(int row);

    void clear();

    void sort(Qt::SortOrder order = Qt::AscendingOrder);

    QStandardItem* itemAt(int row) const;



private slots:
    void onCurrentItemChanged();

signals:
    void currentItemChanged(QStandardItem *item);
    void countChanged(int count);
    
private:
    SelectionModel *m_model;

    Q_DISABLE_COPY(ListView)
};

#endif // LISTVIEW_H
