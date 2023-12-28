#ifndef PRIMITIVEVIEWITEMPLUGIN_H
#define PRIMITIVEVIEWITEMPLUGIN_H

#include "plugin_system/abstract_sketch_cad_plugin.h"
#include "primitive/primitive_model/abstract_primitive_view_item.h"

class PrimitiveViewItemPlugin : public AbstractSketchCADPlugin
{
public:
    virtual ~PrimitiveViewItemPlugin() = default;
    virtual AbstractPrimitiveViewItem* getPrimitiveViewItem() = 0;
};

#endif // PRIMITIVEVIEWITEMPLUGIN_H
