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

#ifndef SELECTIONITEM_H
#define SELECTIONITEM_H

#include <QObject>
#include <QIcon>
#include <QVariant>

class QNetworkAccessManager;
class QNetworkReply; 

class SelectionItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString iconSource READ iconSource WRITE setIconSource NOTIFY dataChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY dataChanged)
    Q_PROPERTY(QVariant data READ data WRITE setData NOTIFY dataChanged)
    Q_PROPERTY(Qt::Alignment textAlignment READ textAlignment WRITE setTextAlignment NOTIFY dataChanged)

    Q_ENUMS(Roles)

public:
    enum Roles {
        DataRole = Qt::UserRole + 1,
        IconSourceRole,
        TextRole,
        TextAlignmentRole
    };
   
    explicit SelectionItem(QObject *parent = 0);
    explicit SelectionItem(const QString &text, QObject *parent = 0);
    explicit SelectionItem(const QString &text, const QVariant &data, Qt::Alignment textAlignment = Qt::AlignCenter, QObject *parent = 0);
    explicit SelectionItem(const QString &iconSource, const QString &text, const QVariant &data, Qt::Alignment textAlignment = Qt::AlignVCenter, QObject *parent = 0);
    ~SelectionItem();

    QIcon icon() const;
    void setIcon(const QIcon &icon);

    QString iconSource() const;
    void setIconSource(const QString &source);

    QString text() const;
    void setText(const QString &text);

    QVariant data() const;
    void setData(const QVariant &data);

    Qt::Alignment textAlignment() const;
    void setTextAlignment(Qt::Alignment alignment);

    QVariant data(int role) const;

private:
    void downloadIcon();

private slots:
    void onReplyFinished();

signals:
    void dataChanged();

private:
    static QHash<QString, QIcon> iconCache;

    static QNetworkAccessManager *networkManager;

    static int referenceCount;

    QNetworkReply *m_reply;

    QString m_iconSource;

    QIcon m_icon;

    QString m_text;

    QVariant m_data;

    Qt::Alignment m_textAlignment;

    Q_DISABLE_COPY(SelectionItem)
};

Q_DECLARE_METATYPE(SelectionItem*)

#endif // SELECTIONITEM_H
