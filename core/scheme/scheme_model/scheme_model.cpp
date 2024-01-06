#include "scheme_model.h"



/* Private methods */


void SchemeModel::addPrimitive(const std::shared_ptr<AbstractPrimitive> &primitive)
{
    this->primitives.insert_or_assign(primitive->getId(), primitive);
    this->scheme_view_models_manager->attachPrimitive(primitive);
    connect(primitive.get(), &AbstractPrimitive::doAction, this, &SchemeModel::onDoAction);
}


void SchemeModel::addConstraint(const std::shared_ptr<AbstractConstraint> &constraint)
{
    this->constraints.insert_or_assign(constraint->getId(), constraint);
}


void SchemeModel::removePrimitive(ID id)
{
    // Start remove propogation
    auto it = this->primitives.find(id);
    if (it != this->primitives.end())
    {
        auto& primitive = it->second;
        primitive->onRemove(*primitive);
    }
}


void SchemeModel::updatePrimitive(ID id)
{
    // Start update propogation
    auto it = this->primitives.find(id);
    if (it != this->primitives.end())
    {
        auto& primitive = it->second;
        primitive->onUpdate(*primitive);
    }
}


bool SchemeModel::applyTransaction()
{
    /* Step 1: remove constraints and primitives */

    // Remove marked primitives
    for (auto& primitive_pair : this->primitives)
    {
        ID id = primitive_pair.first;
        auto& primitive = primitive_pair.second;

        disconnect(primitive.get(), &AbstractPrimitive::doAction, this, &SchemeModel::onDoAction);

        if (primitive->isMarkedRemove())
        {
            this->scheme_view_models_manager->detachPrimitive(primitive);
            this->primitives.erase(id);
        }
    }

    // Remove marked constraints
    for (auto& constraint_pair : this->constraints)
    {
        ID id = constraint_pair.first;
        auto& constraint = constraint_pair.second;
        if (constraint->isMarkedRemove())
        {
            this->constraints.erase(id);
        }
    }


    /* Step 2: update primitives visual representations */

    // Update marked primitives view items
    for (auto& primitive_pair : this->primitives)
    {
        auto& primitive = primitive_pair.second;
        if (primitive->isMarkedUpdate())
        {
            primitive->getPrimitiveViewItemsManager()->updatePrimitiveViewItems();
            primitive->clearMarkUpdate();
        }
    }


    // Check, are constraints should update
    bool constraints_should_update = false;
    for (auto& constraint_pair : this->constraints)
    {
        auto& constraint = constraint_pair.second;
        if (constraint->isMarkedUpdate())
        {
            constraints_should_update = true;
        }
    }


    /* Step 3: check constraints, send recalculation signal if needed */

    // Clear mark update in primitives
    for (auto& primitive_pair : this->primitives)
    {
        auto& primitive = primitive_pair.second;
        if (primitive->isMarkedUpdate())
        {
            primitive->clearMarkUpdate();
        }
    }

    // Run recalculation if needed
    if (constraints_should_update)
    {
        emit recalculateConstraints(*this);
    }

    return true;
}



/* Public methods */


SchemeModel::SchemeModel()
    : QObject{nullptr}
{
    this->scheme_name = QString("New scheme #%1").arg(this->getId());

    this->scheme_view_models_manager = std::make_unique<SchemeViewModelsManager>();
    connect(this->scheme_view_models_manager.get(), &SchemeViewModelsManager::schemeEventOccured, this, [this](const std::shared_ptr<SchemeEvent> &scheme_event) {
        emit this->schemeEventOccured(scheme_event, *this);
    });
}


std::vector<ID> SchemeModel::getPrimitivesIDs() const
{
    std::vector<ID> keys;
    keys.reserve(primitives.size());

    for (const auto& pair : primitives) {
        keys.push_back(pair.first);
    }

    return keys;
}

std::vector<ID> SchemeModel::getConstraintsIDs() const
{
    std::vector<ID> keys;
    keys.reserve(constraints.size());

    for (const auto& pair : constraints) {
        keys.push_back(pair.first);
    }

    return keys;
}


std::shared_ptr<AbstractPrimitive> SchemeModel::getPrimitive(ID id) const
{
    return primitives.at(id);
}


std::shared_ptr<AbstractConstraint> SchemeModel::getConstraint(ID id) const
{
    return constraints.at(id);
}


SchemeViewModelsManager* SchemeModel::getSchemeViewModelsManager()
{
    return this->scheme_view_models_manager.get();
}


SchemeTransaction SchemeModel::createTransaction() const
{
    return SchemeTransaction(this);
}



/* Public slots */


void SchemeModel::onDoAction(const std::shared_ptr<AbstractSchemeActionCommand> &command) const
{
    scheme_history.doAction(command, const_cast<SchemeModel&>(*this));
}


void SchemeModel::onUndoLastAction() const
{
    scheme_history.undoAction(const_cast<SchemeModel&>(*this));
}


void SchemeModel::onRedoLastAction() const
{
    scheme_history.redoAction(const_cast<SchemeModel&>(*this));
}
