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

#ifndef IMAGE_H
#define IMAGE_H

#include "controlwidget.h"
#include <QWidget>

class QNetworkAccessManager;
class QNetworkReply;
class QUrl;

class Image : public QWidget, public ControlWidget
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
    Q_PROPERTY(QString source READ source WRITE setSource)
    Q_PROPERTY(Qt::AspectRatioMode fillMode READ fillMode WRITE setFillMode)

public:
    explicit Image(QWidget *parent = 0);
    ~Image();

    QString source() const;

    Qt::AspectRatioMode fillMode() const;
    void setFillMode(Qt::AspectRatioMode mode);

public slots:
    void setSource(const QString &source);
    void clear();
    void reload();
    
private:
    void downloadImage(const QUrl &url);

    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void onReplyFinished();

signals:
    void clicked();

private:
    static QNetworkAccessManager *networkManager;

    static int referenceCount;

    QNetworkReply *m_reply;

    QString m_source;

    Qt::AspectRatioMode m_fillMode;

    QImage m_image;

    bool m_pressed;

    Q_DISABLE_COPY(Image)
};

#endif // IMAGE_H
