#include "serialization_context.h"


SerializationContext::SerializationContext(
    const std::unordered_map<ID, std::shared_ptr<AbstractPrimitive>> &primitives,
    const std::unordered_map<ID, std::shared_ptr<AbstractConstraint>> &constraints
) :
    primitives(primitives),
    constraints(constraints)
{

}
