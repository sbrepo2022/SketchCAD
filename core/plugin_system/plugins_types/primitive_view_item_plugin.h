#ifndef PRIMITIVEVIEWITEMPLUGIN_H
#define PRIMITIVEVIEWITEMPLUGIN_H

#include "core_global.h"
#include "plugin_system/abstract_sketch_cad_plugin.h"
#include "primitive/primitive_model/abstract_primitive_view_item.h"

class CORE_EXPORT PrimitiveViewItemPlugin : public AbstractSketchCADPlugin
{
public:
    virtual ~PrimitiveViewItemPlugin() = default;
    virtual AbstractPrimitiveViewItem* getPrimitiveViewItem() = 0;
};

Q_DECLARE_INTERFACE(PrimitiveViewItemPlugin, "scad_basic::PrimitiveViewItemPlugin/1.0")

#endif // PRIMITIVEVIEWITEMPLUGIN_H
