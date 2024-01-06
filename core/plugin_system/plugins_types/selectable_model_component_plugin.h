#ifndef SELECTABLEMODELCOMPONENTPLUGIN_H
#define SELECTABLEMODELCOMPONENTPLUGIN_H

#include "plugin_system/abstract_sketch_cad_plugin.h"
#include "primitive/selectable_model_component/selectable_model_component.h"

class SelectableModelComponentPlugin : public AbstractSketchCADPlugin
{
public:
    virtual ~SelectableModelComponentPlugin() = default;
    virtual SelectableModelComponent* getSelectableModelComponent(const std::weak_ptr<AbstractPrimitive> &linked_primitive) const = 0;
};

#endif // SELECTABLEMODELCOMPONENTPLUGIN_H
