#ifndef ABSTRACTCONSTRAINT_H
#define ABSTRACTCONSTRAINT_H

#include "core_global.h"
#include "primitive/primitive_model/abstract_primitive.h"

class CORE_EXPORT AbstractConstraint : public AbstractPrimitive
{
public:
    explicit AbstractConstraint();

    // TODO: Add data, which is constraint have to return to solver
};

#endif // ABSTRACTCONSTRAINT_H
