#ifndef PRIMITIVEVIEWITEMINFO_H
#define PRIMITIVEVIEWITEMINFO_H

#include "core_global.h"

#include <QString>


class CORE_EXPORT PrimitiveViewItemInfo
{
public:
    virtual ~PrimitiveViewItemInfo() = default;
    virtual QString getPrimitiveFullName() = 0;
    virtual QString getSchemeViewModelFullName() = 0;
};

#endif // PRIMITIVEVIEWITEMINFO_H
