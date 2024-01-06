#include "point_primitive.h"
#include "plugin_system/sketch_cad_plugin_loader.h"
#include "plugin_system/plugins_types/primitive_view_item_plugin.h"
#include "plugin_system/plugins_types/selectable_model_component_plugin.h"


PointPrimitive::PointPrimitive(ID id) :
    AbstractPrimitive(id)
{

}


std::shared_ptr<SketchCADPluginInfo> PointPrimitive::getPluginInfo() const
{
    return std::make_unique<PointPrimitivePluginInfo>();
}


std::vector<std::unique_ptr<AbstractPrimitiveViewItem>> PointPrimitive::createPrimitiveViewItems(const std::shared_ptr<AbstractPrimitive> &primitive)
{
    auto result = AbstractPrimitive::createPrimitiveViewItems(primitive);
    auto primitive_view_item_plugins = SketchCADPluginLoader::getInstance()->getPluginsByType<PrimitiveViewItemPlugin>();
    for (auto& primitive_view_item_plugin : primitive_view_item_plugins)
    {
        if (primitive_view_item_plugin->getPrimitiveViewItemInfo()->getPrimitiveFullName() == "scad_default::PointPrimitive")
        {
            AbstractPrimitiveViewItem* primitive_view_item = primitive_view_item_plugin->getPrimitiveViewItem(primitive);
            result.push_back(std::unique_ptr<AbstractPrimitiveViewItem>(primitive_view_item));
        }
    }
    return result;
}


std::vector<std::unique_ptr<SelectableModelComponent>> PointPrimitive::createSelectableModelComponents(const std::shared_ptr<AbstractPrimitive> &primitive)
{
    auto result = AbstractPrimitive::createSelectableModelComponents(primitive);
    auto plugin = SketchCADPluginLoader::getInstance()->getPluginByName("scad_default::PointPropertiesComponentPlugin");
    auto component_plugin = dynamic_cast<SelectableModelComponentPlugin*>(plugin);
    if (component_plugin != nullptr)
    {
        SelectableModelComponent* component = component_plugin->getSelectableModelComponent(primitive);
        result.push_back(std::unique_ptr<SelectableModelComponent>(component));
    }

    return result;
}


std::shared_ptr<AbstractPrimitive> PointPrimitiveFabric::createPrimitive()
{
    auto point_primitive = std::make_shared<PointPrimitive>();
    point_primitive->initialize(point_primitive);
    return point_primitive;
}


std::shared_ptr<AbstractPrimitive> PointPrimitiveFabric::createUninitializedPrimitive(ID id)
{
    return std::make_shared<PointPrimitive>(id);
}
