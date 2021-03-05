#ifndef POLIGON_H
#define POLIGON_H

#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QColor>
#include <QGraphicsItem>
#include <QImage>
#include <QGraphicsPixmapItem>
#include <QPainter>

using namespace std;

class Poligon : public QGraphicsScene
{
    Q_OBJECT
public:
    Poligon(QObject *parent = nullptr);
    ~Poligon();

    QColor getPenColor();
    void setPenColor(const QColor &newColor);
    void setMode(const QString &text);
    bool openImage(const QString &fileName);
    void saveImage(const QString &fileName);

private slots:

    void setWeight(QString);
    void setBrushPattern(QString);
    void setWhiteBackground();

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    QPointF previousPoint;
    int weightPen;
    QColor penColor;
    QString mode;
    QBrush brush;
    QGraphicsEllipseItem* previousEllipse;
    QGraphicsRectItem* previousRectangle;
};

#endif // POLIGON_H
