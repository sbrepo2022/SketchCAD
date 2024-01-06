#ifndef ABSTRACTPRIMITIVESCENEVIEWITEM_H
#define ABSTRACTPRIMITIVESCENEVIEWITEM_H

#include <QGraphicsItem>

#include "primitive/primitive_model/abstract_primitive_view_item.h"


class AbstractPrimitiveSceneViewItem : public AbstractPrimitiveViewItem
{
public:
    AbstractPrimitiveSceneViewItem(const std::weak_ptr<AbstractPrimitive> &linked_primitive);
    virtual QGraphicsItem* getGraphicsItem() = 0;
};

#endif // ABSTRACTPRIMITIVESCENEVIEWITEM_H
