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

#ifndef LISTSELECTOR_H
#define LISTSELECTOR_H

#include "controlwidget.h"
#include <QMaemo5ValueButton>
#include <QVariant>

class QMaemo5ListPickSelector;
class ListView;

class ListSelector : public QMaemo5ValueButton, public ControlWidget
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
    Q_PROPERTY(int currentIndex READ currentIndex WRITE setCurrentIndex)
    Q_PROPERTY(QVariant currentValue READ currentValue WRITE setCurrentValue)
    Q_PROPERTY(QString currentValueText READ currentValueText NOTIFY selected)
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    explicit ListSelector(QWidget *parent = 0);

    int count() const;

    int currentIndex() const;
    void setCurrentIndex(int i);

    QVariant currentValue() const;
    void setCurrentValue(const QVariant &value);

    QString currentValueText() const;

public slots:
    void addItem(const QString &name, const QVariant &value, Qt::Alignment textAlignment = Qt::AlignCenter);
    void addItem(const QString &iconSource, const QString &name, const QVariant &value, Qt::Alignment textAlignment = Qt::AlignVCenter);

    void insertItem(int row, const QString &name, const QVariant &value, Qt::Alignment textAlignment = Qt::AlignCenter);
    void insertItem(int row, const QString &iconSource, const QString &name, const QVariant &value, Qt::Alignment textAlignment = Qt::AlignVCenter);

    bool removeItem(int row);

    void clear();

    void sort(Qt::SortOrder order = Qt::AscendingOrder);
    
signals:
    void selected(const QString &text);
    void countChanged(int count);

private:
    QMaemo5ListPickSelector *m_selector;
    ListView *m_view;

    Q_DISABLE_COPY(ListSelector)
};

#endif // LISTSELECTOR_H
