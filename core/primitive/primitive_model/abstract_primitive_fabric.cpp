#include "abstract_primitive_fabric.h"


/*  -- Example of createPrimitive() realization --
 *
 *  std::shared_ptr<ConcretePrimitive> ConcretePrimitiveFabric::createPrimitive()
 *  {
 *      std::shared_ptr<ConcretePrimitive> concrete_primitive(new ConcretePrimitive());
 *      concrete_primitive->initialize(concrete_primitive);
 *      return concrete_primitive;
 *  }
 *
 *
 *  std::shared_ptr<AbstractPrimitive> createUninitializedPrimitive(ID id)
 *  {
 *      return std::make_shared<ConcretePrimitive>(id);
 *  }
*/


void AbstractPrimitiveFabric::initFromPlainData(
    const std::shared_ptr<AbstractPrimitive> &primitive,
    const PrimitivePlainData &plain_data,
    const SerializationContext &serialization_context
    )
{
    primitive->fromPlainData(plain_data, serialization_context);
    primitive->initialize(primitive);
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
