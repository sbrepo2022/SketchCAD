#ifndef PRIMITIVEVIEWITEMINFOCONTAINER_H
#define PRIMITIVEVIEWITEMINFOCONTAINER_H

#include "core_global.h"
#include "primitive_view_item_info.h"


class CORE_EXPORT PrimitiveViewItemInfoContainer
{
public:
    virtual ~PrimitiveViewItemInfoContainer() = default;
    virtual std::shared_ptr<PrimitiveViewItemInfo> getPrimitiveViewItemInfo() const = 0;
};

#endif // PRIMITIVEVIEWITEMINFOCONTAINER_H
