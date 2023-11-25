#include "abstract_primitive_view_item.h"
#include "abstract_primitive.h"

AbstractPrimitiveViewItem::AbstractPrimitiveViewItem(const std::weak_ptr<AbstractPrimitive> &linked_primitive) :
    linked_primitive(linked_primitive)
{

}

AbstractPrimitiveViewItem::~AbstractPrimitiveViewItem()
{

}
