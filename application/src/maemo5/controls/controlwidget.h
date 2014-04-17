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

#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <Qt>

class ControlWidget
{

public:
    ControlWidget() :
        m_widthPortrait(0),
        m_widthLandscape(0),
        m_heightPortrait(0),
        m_heightLandscape(0),
        m_rowPortrait(0),
        m_rowLandscape(0),
        m_columnPortrait(0),
        m_columnLandscape(0),
        m_rowSpanPortrait(1),
        m_rowSpanLandscape(1),
        m_colSpanPortrait(1),
        m_colSpanLandscape(1),
        m_alignmentPortrait(0),
        m_alignmentLandscape(0)
    {}

    virtual ~ControlWidget() {}

    inline int widthPortrait() const { return m_widthPortrait; }
    inline void setWidthPortrait(int width) { m_widthPortrait = width; }

    inline int widthLandscape() const { return m_widthLandscape; }
    inline void setWidthLandscape(int width) { m_widthLandscape = width; }

    inline int heightPortrait() const { return m_heightPortrait; }
    inline void setHeightPortrait(int height) { m_heightPortrait = height; }

    inline int heightLandscape() const { return m_heightLandscape; }
    inline void setHeightLandscape(int height) { m_heightLandscape = height; }

    inline int rowPortrait() const { return m_rowPortrait; }
    inline void setRowPortrait(int row) { m_rowPortrait = row; }

    inline int rowLandscape() const { return m_rowLandscape; }
    inline void setRowLandscape(int row) { m_rowLandscape = row; }

    inline int columnPortrait() const { return m_columnPortrait; }
    inline void setColumnPortrait(int column) { m_columnPortrait = column; }

    inline int columnLandscape() const { return m_columnLandscape; }
    inline void setColumnLandscape(int column) { m_columnLandscape = column; }

    inline int rowSpanPortrait() const { return m_rowSpanPortrait; }
    inline void setRowSpanPortrait(int span) { m_rowSpanPortrait = span; }

    inline int rowSpanLandscape() const { return m_rowSpanLandscape; }
    inline void setRowSpanLandscape(int span) { m_rowSpanLandscape = span; }

    inline int colSpanPortrait() const { return m_colSpanPortrait; }
    inline void setColSpanPortrait(int span) { m_colSpanPortrait = span; }

    inline int colSpanLandscape() const { return m_colSpanLandscape; }
    inline void setColSpanLandscape(int span) { m_colSpanLandscape = span; }

    inline Qt::Alignment alignmentPortrait() const { return m_alignmentPortrait; }
    inline void setAlignmentPortrait(Qt::Alignment alignment) { m_alignmentPortrait = alignment; }

    inline Qt::Alignment alignmentLandscape() const { return m_alignmentLandscape; }
    inline void setAlignmentLandscape(Qt::Alignment alignment) { m_alignmentLandscape = alignment; }

protected:
    int m_widthPortrait;
    int m_widthLandscape;

    int m_heightPortrait;
    int m_heightLandscape;

    int m_rowPortrait;
    int m_rowLandscape;

    int m_columnPortrait;
    int m_columnLandscape;

    int m_rowSpanPortrait;
    int m_rowSpanLandscape;

    int m_colSpanPortrait;
    int m_colSpanLandscape;

    Qt::Alignment m_alignmentPortrait;
    Qt::Alignment m_alignmentLandscape;
};

#endif // CONTROLWIDGET_H
