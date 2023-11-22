#ifndef ABSTRACTSKETCHCADPLUGIN_H
#define ABSTRACTSKETCHCADPLUGIN_H

#include "core_global.h"
#include "plugin_system/sketch_cad_plugin_info_container.h"

#include <QtPlugin>
#include <QString>

class CORE_EXPORT AbstractSketchCADPlugin : public SketchCADPluginInfoContainer
{
public:
    virtual ~AbstractSketchCADPlugin() = default;
};

Q_DECLARE_INTERFACE(AbstractSketchCADPlugin, "scad_basic::AbstractSketchCADPlugin/1.0")

#endif // ABSTRACTSKETCHCADPLUGIN_H
