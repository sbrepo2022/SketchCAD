#include "primitive_properties_component.h"

PrimitivePropertiesComponent::PrimitivePropertiesComponent(QObject *parent)
    : PropertiesComponent(parent)
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


std::unique_ptr<SketchCADPluginInfo> PrimitivePropertiesComponent::getPluginInfo() const
{
    return std::make_unique<PrimitivePropertiesComponentPluginInfo>();
}

PrimitivePropertiesComponent::~PrimitivePropertiesComponent()
{

}

void PrimitivePropertiesComponent::onPrimitiveNameChanged(QString primitive_name)
{
    // TODO: отправлять doAction() с изменением имени объекта

}
