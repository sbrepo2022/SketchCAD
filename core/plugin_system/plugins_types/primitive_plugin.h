#ifndef PRIMITIVEPLUGIN_H
#define PRIMITIVEPLUGIN_H

#include "plugin_system/abstract_sketch_cad_plugin.h"
#include "primitive/primitive_model/abstract_primitive_fabric.h"

class PrimitivePlugin : public AbstractSketchCADPlugin
{
public:
    virtual ~PrimitivePlugin() = default;
    virtual AbstractPrimitiveFabric* getPrimitiveFabric() const = 0;
};

#endif // PRIMITIVEPLUGIN_H
