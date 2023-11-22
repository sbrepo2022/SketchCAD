#ifndef ABSTRACTPRIMITIVEFABRIC_H
#define ABSTRACTPRIMITIVEFABRIC_H

#include "core_global.h"
#include "primitive/primitive_model/abstract_primitive.h"
#include "primitive/primitive_model/primitive_plain_data.h"
#include <memory>


class CORE_EXPORT AbstractPrimitiveFabric
{
public:
    virtual ~AbstractPrimitiveFabric() = default;
    virtual std::shared_ptr<AbstractPrimitive> createPrimitive() = 0;
    virtual std::shared_ptr<AbstractPrimitive> createUninitializedPrimitive(ID id) = 0;

    void initFromPlainData(
        const std::shared_ptr<AbstractPrimitive> &primitive,
        const PrimitivePlainData &plain_data,
        const SerializationContext &serialization_context
    );

    std::shared_ptr<AbstractPrimitive> createFromPlainData(
        const PrimitivePlainData &plain_data,
        const SerializationContext &serialization_context
    );
};

#endif // ABSTRACTPRIMITIVEFABRIC_H
