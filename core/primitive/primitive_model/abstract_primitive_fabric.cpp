#include "abstract_primitive_fabric.h"


/*  -- Example of createPrimitive() realization --
 *
 *  std::shared_ptr<ConcretePrimitive> ConcretePrimitiveFabric::createPrimitive()
 *  {
 *      ConcretePrimitive *concrete_primitive = new ConcretePrimitive();
 *      concrete_primitive->initialize();
 *      return std::shared_ptr<ConcretePrimitive>(concrete_primitive);
 *  }
 *
 *
 *  std::shared_ptr<AbstractPrimitive> createUninitializedPrimitive(ID id)
 *  {
 *      ConcretePrimitive *concrete_primitive = new ConcretePrimitive(id);
 *      return std::shared_ptr<ConcretePrimitive>(concrete_primitive);
 *  }
*/


void AbstractPrimitiveFabric::initFromPlainData(
    const std::shared_ptr<AbstractPrimitive> &primitive,
    const PrimitivePlainData &plain_data,
    const SerializationContext &serialization_context
    )
{
    primitive->fromPlainData(plain_data, serialization_context);
    primitive->initialize();
}


std::shared_ptr<AbstractPrimitive> AbstractPrimitiveFabric::createFromPlainData(
    const PrimitivePlainData &plain_data,
    const SerializationContext &serialization_context
)
{
    std::shared_ptr<AbstractPrimitive> primitive = this->createUninitializedPrimitive(plain_data.primitive_id);
    this->initFromPlainData(primitive, plain_data, serialization_context);
    return primitive;
}
