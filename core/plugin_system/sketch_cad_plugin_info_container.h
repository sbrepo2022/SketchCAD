#ifndef SKETCHCADPLUGININFOCONTAINER_H
#define SKETCHCADPLUGININFOCONTAINER_H

#include "plugin_system/sketch_cad_plugin_info.h"

#include <memory>

class SketchCADPluginInfoContainer
{
public:
    virtual ~SketchCADPluginInfoContainer() = default;
    virtual std::shared_ptr<SketchCADPluginInfo> getPluginInfo() const = 0;
};

#endif // SKETCHCADPLUGININFOCONTAINER_H
