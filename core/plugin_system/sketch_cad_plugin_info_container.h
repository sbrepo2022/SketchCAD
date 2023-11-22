#ifndef SKETCHCADPLUGININFOCONTAINER_H
#define SKETCHCADPLUGININFOCONTAINER_H

#include "core_global.h"
#include "plugin_system/sketch_cad_plugin_info.h"

#include <memory>

class CORE_EXPORT SketchCADPluginInfoContainer
{
public:
    virtual ~SketchCADPluginInfoContainer() = default;
    virtual std::unique_ptr<SketchCADPluginInfo> getPluginInfo() const = 0;
};

#endif // SKETCHCADPLUGININFOCONTAINER_H
