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

#ifndef SELECTIONMODEL_H
#define SELECTIONMODEL_H

#include <QAbstractListModel>

class SelectionItem;

class SelectionModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)

public:
    explicit SelectionModel(QObject *parent = 0);
    ~SelectionModel();

#if QT_VERSION >= 0x050000
    QHash<int, QByteArray> roleNames() const;
#endif

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    
    Q_INVOKABLE SelectionItem* itemAt(int row) const;

public slots:
    void addItem(const QString &text, const QVariant &data, Qt::Alignment textAlignment = Qt::AlignCenter);
    void addItem(const QString &iconSource, const QString &text, const QVariant &data, Qt::Alignment textAlignment = Qt::AlignVCenter);

    void insertItem(int row, const QString &text, const QVariant &data, Qt::Alignment textAlignment = Qt::AlignCenter);
    void insertItem(int row, const QString &iconSource, const QString &text, const QVariant &data, Qt::Alignment textAlignment = Qt::AlignVCenter);

    bool removeItem(int row);

    void clear();

private slots:
    void onItemDataChanged();

signals:
    void countChanged(int count);

private:
    QList<SelectionItem*> m_list;

    QHash<int, QByteArray> m_roleNames;

    Q_DISABLE_COPY(SelectionModel)
};

#endif // SELECTIONMODEL_H
