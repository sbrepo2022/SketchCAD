#include "point_properties_component.h"
#include "point_position_change_action_command.h"


PointPropertiesComponent::PointPropertiesComponent(const std::weak_ptr<AbstractPrimitive> &linked_primitive)
    : PropertiesComponent(linked_primitive)
{
    QList<QMap<QString, QVariant>> widget_properties ={
        {
            std::pair<QString, QVariant>("name", "point_position"),
            std::pair<QString, QVariant>("title", "Point position")
        }
    };
    this->component_widget = PropertiesComponent::generateForm(widget_properties);

    connect(this, &PointPropertiesComponent::pointPositionChanged, this, &PointPropertiesComponent::onPointPositionChanged);
}


std::shared_ptr<SketchCADPluginInfo> PointPropertiesComponent::getPluginInfo() const
{
    return std::make_unique<PointPropertiesComponentPluginInfo>();
}


PointPropertiesComponent::~PointPropertiesComponent()
{

}


QPointF PointPropertiesComponent::getPointPosition() const
{
    return this->m_point_position;
}


void PointPropertiesComponent::directSetPointPosition(QPointF point_position)
{
    this->m_point_position = this->m_point_position_old = point_position;
}


void PointPropertiesComponent::onPointPositionChanged(QPointF point_position)
{
    if (auto linked_primitive_lock = this->linked_primitive.lock())
    {
        emit doAction(std::make_shared<PointPositionChangeActionCommand>(linked_primitive_lock->getId(), point_position, this->m_point_position_old));
        this->m_point_position_old = point_position;
    }
}
