#include "point_scene_view_item.h"
#include "point_properties_component.h"

#include "primitive/primitive_model/abstract_primitive.h"


PointSceneViewItem::PointSceneViewItem(const std::weak_ptr<AbstractPrimitive> &linked_primitive) :
    AbstractPrimitiveSceneViewItem(linked_primitive),
    point_graphics_item(new PointGraphicsItem)
{

}


QGraphicsItem* PointSceneViewItem::getGraphicsItem()
{
    return this->point_graphics_item;
}


void PointSceneViewItem::onLinkedPrimitiveUpdated()
{
    if (auto primitive = this->linked_primitive.lock())
    {
        std::vector<PointPropertiesComponent*> components = primitive->getSelectableModelComponentsKeeper()->getComponentsByType<PointPropertiesComponent>();
        if (components.size() > 0)
        {
            auto component = components[0];
            QPointF position = component->getPointPosition();
            this->point_graphics_item->setPos(position);
        }
    }
}


std::shared_ptr<SketchCADPluginInfo> PointSceneViewItem::getPluginInfo() const
{
    return std::make_shared<PointSceneViewItemPluginInfo>();
}


std::shared_ptr<PrimitiveViewItemInfo> PointSceneViewItem::getPrimitiveViewItemInfo() const
{
    return std::make_shared<PointSceneViewItemInfo>();
}
