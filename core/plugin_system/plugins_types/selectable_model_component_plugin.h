#ifndef SELECTABLEMODELCOMPONENTPLUGIN_H
#define SELECTABLEMODELCOMPONENTPLUGIN_H

#include "core_global.h"
#include "plugin_system/abstract_sketch_cad_plugin.h"
#include "primitive/selectable_model_component/selectable_model_component.h"

class CORE_EXPORT SelectableModelComponentPlugin : public AbstractSketchCADPlugin
{
public:
    virtual ~SelectableModelComponentPlugin() = default;
    virtual SelectableModelComponent* getSelectableModelComponent() = 0;
};

Q_DECLARE_INTERFACE(SelectableModelComponentPlugin, "scad_basic::SelectableModelComponentPlugin/1.0")

#endif // SELECTABLEMODELCOMPONENTPLUGIN_H
