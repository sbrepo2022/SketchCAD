#include "primitive_properties_component.h"
#include "primitive/selectable_model_component/primitive_properties_component/primitive_name_change_action_command.h"

PrimitivePropertiesComponent::PrimitivePropertiesComponent(const std::weak_ptr<AbstractPrimitive> &linked_primitive)
    : PropertiesComponent(linked_primitive)
{
    QList<QMap<QString, QVariant>> widget_properties ={
        {
            std::pair<QString, QVariant>("name", "primitive_name"),
            std::pair<QString, QVariant>("title", "Primitive name"),
            std::pair<QString, QVariant>("field_type", "line"),
        }
    };
    this->component_widget = PropertiesComponent::generateForm(widget_properties);

    connect(this, &PrimitivePropertiesComponent::primitiveNameChanged, this, &PrimitivePropertiesComponent::onPrimitiveNameChanged);
}


std::shared_ptr<SketchCADPluginInfo> PrimitivePropertiesComponent::getPluginInfo() const
{
    return std::make_unique<PrimitivePropertiesComponentPluginInfo>();
}


PrimitivePropertiesComponent::~PrimitivePropertiesComponent()
{

}


QString PrimitivePropertiesComponent::getPrimitiveName()
{
    return this->m_primitive_name;
}


void PrimitivePropertiesComponent::directSetPrimitiveName(QString primitive_name)
{
    this->m_primitive_name = this->m_primitive_name_old = primitive_name;
}


void PrimitivePropertiesComponent::onPrimitiveNameChanged(QString primitive_name)
{
    if (auto linked_primitive_lock = this->linked_primitive.lock())
    {
        emit doAction(std::make_shared<PrimitiveComponentChangeActionCommand>(linked_primitive_lock->getId(), primitive_name, this->m_primitive_name_old));
        this->m_primitive_name_old = primitive_name;
    }
}
