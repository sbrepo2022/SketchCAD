#ifndef PRIMITIVEVIEWITEMPLUGIN_H
#define PRIMITIVEVIEWITEMPLUGIN_H

#include "plugin_system/abstract_sketch_cad_plugin.h"
#include "primitive/primitive_model/abstract_primitive_view_item.h"
#include "primitive/primitive_model/primitive_view_item_info_container.h"


class PrimitiveViewItemPlugin : public AbstractSketchCADPlugin, public PrimitiveViewItemInfoContainer
{
public:
    virtual ~PrimitiveViewItemPlugin() = default;
    virtual AbstractPrimitiveViewItem* getPrimitiveViewItem(const std::weak_ptr<AbstractPrimitive> &linked_primitive) = 0;
};

#endif // PRIMITIVEVIEWITEMPLUGIN_H
