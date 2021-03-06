#include "poligon.h"

Poligon::Poligon(QObject *parent)
    : QGraphicsScene(parent)
{
    weightPen = 1;
    penColor = Qt::red;
    mode = "Pen";
    brush = Qt::SolidPattern;
}

Poligon::~Poligon()
{

}

QColor Poligon::getPenColor()
{
    return penColor;
}

void Poligon::setPenColor(const QColor &newColor)
{
    penColor = newColor;
}

void Poligon::setMode(const QString &text)
{
    mode = text;
}

bool Poligon::openImage(const QString &fileName)
{
    QImage loadedImage(fileName);
    setBackgroundBrush(loadedImage);

    return true;
}



void Poligon::setWeight(QString numb)
{
    weightPen = numb.toInt();
}

void Poligon::setBrushPattern(QString index)
{
    if(index == "SolidPattern") brush = Qt::SolidPattern;
    else if(index == "Dense1Pattern") brush = Qt::Dense1Pattern;
    else if(index == "Dense2Pattern") brush = Qt::Dense2Pattern;
    else if(index == "Dense3Pattern") brush = Qt::Dense3Pattern;
    else if(index == "Dense4Pattern") brush = Qt::Dense4Pattern;
    else if(index == "Dense5Pattern") brush = Qt::Dense5Pattern;
    else if(index == "Dense6Pattern") brush = Qt::Dense6Pattern;
    else if(index == "Dense7Pattern") brush = Qt::Dense7Pattern;
    else if(index == "NoBrush") brush = Qt::NoBrush;
    else if(index == "HorPattern") brush = Qt::HorPattern;
    else if(index == "VerPattern") brush = Qt::VerPattern;
    else if(index == "CrossPattern") brush = Qt::CrossPattern;
    else if(index == "BDiagPattern") brush = Qt::BDiagPattern;
    else if(index == "FDiagPattern") brush = Qt::FDiagPattern;
    else  brush = Qt::DiagCrossPattern;
}

void Poligon::setWhiteBackground()
{
    setBackgroundBrush(QBrush(Qt::white));
    clear();
}

void Poligon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // При нажатии кнопки мыши отрисовываем эллипс
    if(mode == "Pen")
    {
        brush = penColor;
        addEllipse(event->scenePos().x() - 5,
                   event->scenePos().y() - 5,
                   weightPen,
                   weightPen,
                   QPen(Qt::NoPen),
                   brush);
        // Сохраняем координаты точки нажатия
        previousPoint = event->scenePos();
    }
    else if(mode == "Circle")
    {
        previousEllipse = new QGraphicsEllipseItem();
        addItem(previousEllipse);
        brush.setColor(penColor);
        // Сохраняем координаты точки нажатия
        previousPoint = event->scenePos();
    }
    else
    {
        previousRectangle = new QGraphicsRectItem();
        addItem(previousRectangle);
        brush.setColor(penColor);
        // Сохраняем координаты точки нажатия
        previousPoint = event->scenePos();
    }
}

void Poligon::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(mode == "Pen")
    {
        // Отрисовываем линии с использованием предыдущей координаты
        addLine(previousPoint.x(),
                previousPoint.y(),
                event->scenePos().x(),
                event->scenePos().y(),
                QPen(penColor,weightPen,Qt::SolidLine,Qt::RoundCap));
        // Обновляем данные о предыдущей координате
        previousPoint = event->scenePos();
    }
    else if(mode == "Circle")
    {
        removeItem(previousEllipse);

        QRectF rect(previousPoint, event->scenePos());
        QGraphicsEllipseItem* ellipseItem = new QGraphicsEllipseItem(rect);
        ellipseItem->setBrush(brush);
        ellipseItem->setPen(QPen(penColor,weightPen));
        ellipseItem->setRect(ellipseItem->boundingRect());
        addItem(ellipseItem);

        previousEllipse = ellipseItem;
    }
    else
    {
        removeItem(previousRectangle);

        QRectF rect(previousPoint, event->scenePos());
        QGraphicsEllipseItem* ellipseItem = new QGraphicsEllipseItem(rect);
        ellipseItem->setBrush(brush);
        ellipseItem->setPen(QPen(penColor,weightPen));

        addItem(ellipseItem);

        QGraphicsRectItem* rectItem = new QGraphicsRectItem(ellipseItem->boundingRect());
        rectItem->setBrush(brush);
        rectItem->setPen(QPen(penColor,weightPen));

        removeItem(ellipseItem);

        addItem(rectItem);

        previousRectangle = rectItem;
    }
}
