#include "point_scene_view_item.h"

PointSceneViewItem::PointSceneViewItem() :
    point_graphics_item(new PointGraphicsItem)
{

}


QGraphicsItem* PointSceneViewItem::getGraphicsItem()
{
    return this->point_graphics_item;
}


void PointSceneViewItem::onLinkedPrimitiveUpdated()
{

}
