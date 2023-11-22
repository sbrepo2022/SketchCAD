#ifndef PRIMITIVEPLUGIN_H
#define PRIMITIVEPLUGIN_H

#include "core_global.h"
#include "plugin_system/abstract_sketch_cad_plugin.h"
#include "primitive/primitive_model/abstract_primitive_fabric.h"

class CORE_EXPORT PrimitivePlugin : public AbstractSketchCADPlugin
{
public:
    virtual ~PrimitivePlugin() = default;
    virtual AbstractPrimitiveFabric* getPrimitiveFabric() = 0;
};

Q_DECLARE_INTERFACE(PrimitivePlugin, "scad_basic::PrimitivePlugin/1.0")

#endif // PRIMITIVEPLUGIN_H
