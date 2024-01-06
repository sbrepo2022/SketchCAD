#include "abstract_primitive_scene_view_item.h"


AbstractPrimitiveSceneViewItem::AbstractPrimitiveSceneViewItem(const std::weak_ptr<AbstractPrimitive> &linked_primitive) :
    AbstractPrimitiveViewItem(linked_primitive)
{

}
