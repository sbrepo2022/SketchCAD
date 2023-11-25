#include "selectable_model_component.h"

SelectableModelComponent::SelectableModelComponent(const std::weak_ptr<AbstractPrimitive> &linked_primitive) :
    QObject(nullptr),
    component_widget(nullptr),
    linked_primitive(linked_primitive)
{

}

SelectableModelComponent::~SelectableModelComponent()
{

}
