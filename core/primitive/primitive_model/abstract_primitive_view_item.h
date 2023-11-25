#ifndef ABSTRACTPRIMITIVEVIEWITEM_H
#define ABSTRACTPRIMITIVEVIEWITEM_H

#include "core_global.h"
#include "plugin_system/sketch_cad_plugin_info_container.h"

#include <memory>

class AbstractPrimitive;

class CORE_EXPORT AbstractPrimitiveViewItem : public SketchCADPluginInfoContainer
{
protected:
    std::weak_ptr<AbstractPrimitive> linked_primitive;

public:
    AbstractPrimitiveViewItem(const std::weak_ptr<AbstractPrimitive> &linked_primitive);
    virtual ~AbstractPrimitiveViewItem();
    std::weak_ptr<AbstractPrimitive> getLinkedPrimitive() const { return linked_primitive; }

    virtual void onLinkedPrimitiveUpdated() = 0;
};

#endif // ABSTRACTPRIMITIVEVIEWITEM_H
