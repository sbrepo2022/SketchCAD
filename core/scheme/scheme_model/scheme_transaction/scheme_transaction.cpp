#include "scheme_transaction.h"

SchemeTransaction::SchemeTransaction(SchemeTransactionInterface *apply_to) :
    apply_to(apply_to)
{

}


void SchemeTransaction::addPrimitive(const std::shared_ptr<AbstractPrimitive> &primitive)
{
    this->primitives_to_add.push_back(primitive);
    this->updatePrimitives(primitive->getId());
}


void SchemeTransaction::addConstraint(const std::shared_ptr<AbstractConstraint> &constraint)
{
    this->addPrimitive(constraint);
    this->constraints_to_add.push_back(constraint);
    this->updatePrimitives(constraint->getId());
}


void SchemeTransaction::removePrimitive(ID id)
{
    this->primitives_to_remove.push_back(id);
}


void SchemeTransaction::updatePrimitives(ID id)
{
    this->primitives_to_update.push_back(id);
}


bool SchemeTransaction::applyTransaction()
{
    if (apply_to == nullptr)
        return false;

    for (auto& primitive_to_add : this->primitives_to_add)
    {
        this->apply_to->addPrimitive(primitive_to_add);
    }

    for (auto& constraint_to_add : this->constraints_to_add)
    {
        this->apply_to->addConstraint(constraint_to_add);
    }

    for (ID id : this->primitives_to_remove)
    {
        this->apply_to->removePrimitive(id);
    }

    for (ID id : this->primitives_to_update)
    {
        this->apply_to->updatePrimitives(id);
    }

    return this->apply_to->applyTransaction();
}
