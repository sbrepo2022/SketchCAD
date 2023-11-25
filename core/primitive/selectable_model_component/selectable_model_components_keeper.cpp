#include "selectable_model_components_keeper.h"

SelectableModelComponentsKeeper::SelectableModelComponentsKeeper(QObject *parent)
    : QObject(parent)
{

}

SelectableModelComponentsKeeper::~SelectableModelComponentsKeeper()
{
    for (auto it = this->selectable_model_components.begin(); it != this->selectable_model_components.end(); ++it)
    {
        disconnect(it->second.get(), &SelectableModelComponent::doAction, this, &SelectableModelComponentsKeeper::doAction);
    }
}



void SelectableModelComponentsKeeper::addComponent(std::unique_ptr<SelectableModelComponent> &&component)
{
    connect(component.get(), &SelectableModelComponent::doAction, this, &SelectableModelComponentsKeeper::doAction);
    this->selectable_model_components.emplace(component->getPluginInfo()->getFullName(), std::move(component));
}


SelectableModelComponent *SelectableModelComponentsKeeper::getComponentByName(const QString &full_name) const
{
    return this->selectable_model_components.at(full_name).get();
}
