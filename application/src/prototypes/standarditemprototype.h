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

#ifndef STANDARDITEMPROTOTYPE_H
#define STANDARDITEMPROTOTYPE_H

#include <QObject>
#include <QScriptable>
#include <QStandardItem>

class StandardItemPrototype : public QObject, public QScriptable
{
    Q_OBJECT

    Q_PROPERTY(QString text READ text WRITE setText)
    Q_PROPERTY(QString iconSource READ iconSource WRITE setIconSource)
    Q_PROPERTY(QVariant data READ data WRITE setData)

public:
    explicit StandardItemPrototype(QObject *parent = 0);

    QString text() const;
    void setText(const QString &text);

    QString iconSource() const;
    void setIconSource(const QString &path);

    QVariant data() const;
    void setData(const QVariant &data);

private:
    Q_DISABLE_COPY(StandardItemPrototype)
};

Q_DECLARE_METATYPE(QStandardItem*)

#endif // STANDARDITEMPROTOTYPE_H
