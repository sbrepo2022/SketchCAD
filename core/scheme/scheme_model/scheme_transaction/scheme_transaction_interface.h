#ifndef SCHEMETRANSACTIONINTERFACE_H
#define SCHEMETRANSACTIONINTERFACE_H

#include "core_global.h"
#include "primitive/primitive_model/abstract_primitive.h"
#include "primitive/primitive_model/abstract_constraint.h"

class CORE_EXPORT SchemeTransactionInterface
{
public:
    virtual void addPrimitive(const std::shared_ptr<AbstractPrimitive> &primitive) = 0;
    virtual void addConstraint(const std::shared_ptr<AbstractConstraint> &constraint) = 0;
    virtual void removePrimitive(ID id) = 0;
    virtual void updatePrimitive(ID id) = 0;

    virtual bool applyTransaction() = 0;
};

#endif // SCHEMETRANSACTIONINTERFACE_H
