#include "point_position_change_action_command.h"
#include "point_properties_component.h"


PointPositionChangeActionCommand::PointPositionChangeActionCommand(ID linked_primitive_id, QPointF old_point_position, QPointF new_point_position) :
    AbstractSchemeActionCommand(),
    linked_primitive_id(linked_primitive_id),
    old_point_position(old_point_position),
    new_point_position(new_point_position)
{

}


void PointPositionChangeActionCommand::doAction(const SchemeModel &scheme_model)
{
    SchemeTransaction scheme_transaction = scheme_model.createTransaction();
    scheme_transaction.updatePrimitive(this->linked_primitive_id);
    scheme_transaction.applyTransaction();
    Q_UNUSED(scheme_model)
}


void PointPositionChangeActionCommand::undoAction(const SchemeModel &scheme_model)
{
    if (auto primitive = scheme_model.getPrimitive(this->linked_primitive_id))
    {
        std::vector<PointPropertiesComponent*> components = primitive->getSelectableModelComponentsKeeper()->getComponentsByType<PointPropertiesComponent>();
        if (components.size() > 0)
        {
            auto component = components[0];
            component->directSetPointPosition(old_point_position);
        }
    }

    SchemeTransaction scheme_transaction = scheme_model.createTransaction();
    scheme_transaction.updatePrimitive(this->linked_primitive_id);
    scheme_transaction.applyTransaction();
    Q_UNUSED(scheme_model)
}


void PointPositionChangeActionCommand::redoAction(const SchemeModel &scheme_model)
{
    if (auto primitive = scheme_model.getPrimitive(this->linked_primitive_id))
    {
        std::vector<PointPropertiesComponent*> components = primitive->getSelectableModelComponentsKeeper()->getComponentsByType<PointPropertiesComponent>();
        if (components.size() > 0)
        {
            auto component = components[0];
            component->directSetPointPosition(new_point_position);
        }
    }

    SchemeTransaction scheme_transaction = scheme_model.createTransaction();
    scheme_transaction.updatePrimitive(this->linked_primitive_id);
    scheme_transaction.applyTransaction();

    Q_UNUSED(scheme_model)
}
