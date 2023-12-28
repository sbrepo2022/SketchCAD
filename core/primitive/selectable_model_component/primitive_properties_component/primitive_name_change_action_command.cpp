#include "primitive_name_change_action_command.h"
#include "primitive/primitive_model/abstract_primitive.h"
#include "primitive/selectable_model_component/primitive_properties_component/primitive_properties_component.h"

PrimitiveComponentChangeActionCommand::PrimitiveComponentChangeActionCommand(ID linked_primitive_id, QString old_name, QString new_name) :
    AbstractSchemeActionCommand(),
    linked_primitive_id(linked_primitive_id),
    old_name(old_name),
    new_name(new_name)
{

}


void PrimitiveComponentChangeActionCommand::doAction(const SchemeModel &scheme_model)
{
    if (auto primitive = scheme_model.getPrimitive(this->linked_primitive_id))
    {
        primitive->getPrimitiveViewItemsManager()->updatePrimitiveViewItems();
    }
    Q_UNUSED(scheme_model)
}


void PrimitiveComponentChangeActionCommand::undoAction(const SchemeModel &scheme_model)
{
    if (auto primitive = scheme_model.getPrimitive(this->linked_primitive_id))
    {
        std::vector<PrimitivePropertiesComponent*> components = primitive->getSelectableModelComponentsKeeper()->getComponentsByType<PrimitivePropertiesComponent>();
        for (auto component : components)
        {
            component->directSetPrimitiveName(old_name);
        }
        primitive->getPrimitiveViewItemsManager()->updatePrimitiveViewItems();
    }
    Q_UNUSED(scheme_model)
}


void PrimitiveComponentChangeActionCommand::redoAction(const SchemeModel &scheme_model)
{
    if (auto primitive = scheme_model.getPrimitive(this->linked_primitive_id))
    {
        std::vector<PrimitivePropertiesComponent*> components = primitive->getSelectableModelComponentsKeeper()->getComponentsByType<PrimitivePropertiesComponent>();
        for (auto component : components)
        {
            component->directSetPrimitiveName(new_name);
        }
        primitive->getPrimitiveViewItemsManager()->updatePrimitiveViewItems();
    }
    Q_UNUSED(scheme_model)
}
