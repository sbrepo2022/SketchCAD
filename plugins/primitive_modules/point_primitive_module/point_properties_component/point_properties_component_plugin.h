#ifndef POINT_PROPERTIES_COMPONENT_PLUGIN_H
#define POINT_PROPERTIES_COMPONENT_PLUGIN_H

#include "point_properties_component_global.h"
#include "plugin_system/plugins_types/selectable_model_component_plugin.h"
#include "point_properties_component.h"

#include <memory>

class POINT_PROPERTIES_COMPONENT_EXPORT PointPropertiesComponentPlugin : public QObject, public SelectableModelComponentPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "scad_basic::AbstractSketchCADPlugin/1.0")
    Q_INTERFACES(AbstractSketchCADPlugin)

public:
    virtual SelectableModelComponent* getSelectableModelComponent(const std::weak_ptr<AbstractPrimitive> &linked_primitive) const override { return new PointPropertiesComponent(linked_primitive); }
    virtual std::shared_ptr<SketchCADPluginInfo> getPluginInfo() const override { return std::make_shared<PointPropertiesComponentPluginInfo>(); }
};

#endif // POINT_PROPERTIES_COMPONENT_PLUGIN_H
