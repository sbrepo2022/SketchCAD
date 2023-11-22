#ifndef SERIALIZATIONCONTEXT_H
#define SERIALIZATIONCONTEXT_H

#include "core_global.h"
#include "primitive/primitive_model/abstract_primitive.h"
#include "primitive/primitive_model/abstract_constraint.h"

#include <memory>
#include <unordered_map>

class CORE_EXPORT SerializationContext
{
private:
    std::unordered_map<ID, std::shared_ptr<AbstractPrimitive>> primitives;
    std::unordered_map<ID, std::shared_ptr<AbstractConstraint>> constraints;

public:
    SerializationContext(
        const std::unordered_map<ID, std::shared_ptr<AbstractPrimitive>> &primitives,
        const std::unordered_map<ID, std::shared_ptr<AbstractConstraint>> &constraints
    );

    std::shared_ptr<AbstractPrimitive> getPrimitivesToAdd(ID id) { return this->primitives[id]; }
    std::shared_ptr<AbstractConstraint> getConstraintsToAdd(ID id) { return this->constraints[id]; }
};

#endif // SERIALIZATIONCONTEXT_H
