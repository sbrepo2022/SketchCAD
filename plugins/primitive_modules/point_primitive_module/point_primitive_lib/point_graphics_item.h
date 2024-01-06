#ifndef POINTGRAPHICSITEM_H
#define POINTGRAPHICSITEM_H

#include "point_primitive_lib_global.h"

#include <QGraphicsItem>
#include <QPainter>

class POINT_PRIMITIVE_LIB_EXPORT PointGraphicsItem : public QGraphicsItem
{
    const double size = 5.0;

public:
    PointGraphicsItem();

    QRectF boundingRect() const override
    {
        return QRectF(size / 2, size / 2, size, size);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
    {
        painter->setBrush(Qt::blue);
        painter->drawEllipse(QPointF(0, 0), this->size, this->size);

        Q_UNUSED(option);
        Q_UNUSED(widget);
    }
};

#endif // POINTGRAPHICSITEM_H
