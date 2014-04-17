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

#ifndef DATESELECTOR_H
#define DATESELECTOR_H

#include "controlwidget.h"
#include <QMaemo5ValueButton>
#include <QDate>

class QMaemo5DatePickSelector;

class DateSelector : public QMaemo5ValueButton, public ControlWidget
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
    Q_PROPERTY(int minimumYear READ minimumYear WRITE setMinimumYear)
    Q_PROPERTY(int maximumYear READ maximumYear WRITE setMaximumYear)
    Q_PROPERTY(QDate currentDate READ currentDate WRITE setCurrentDate)
    Q_PROPERTY(int currentDay READ currentDay)
    Q_PROPERTY(int currentMonth READ currentMonth)
    Q_PROPERTY(int currentYear READ currentYear)
    Q_PROPERTY(QString currentValueText READ currentValueText NOTIFY selected)

public:
    explicit DateSelector(QWidget *parent = 0);

    int minimumYear() const;
    void setMinimumYear(int min);

    int maximumYear() const;
    void setMaximumYear(int max);

    QDate currentDate() const;
    void setCurrentDate(const QDate &date);

    int currentDay() const;
    int currentMonth() const;
    int currentYear() const;

    QString currentValueText() const;

signals:
    void selected(const QString &text);
    
private:
    QMaemo5DatePickSelector *m_selector;

    Q_DISABLE_COPY(DateSelector)
};

#endif // DATESELECTOR_H
