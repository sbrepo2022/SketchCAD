#include "edit_mode_dispatcher.h"
#include "plugin_system/sketch_cad_plugin_loader.h"
#include "plugin_system/plugins_types/edit_mode_plugin.h"


EditModeDispatcher::EditModeDispatcher() :
    QObject{nullptr},
    current_edit_mode(0)
{
    this->edit_modes.clear();
    std::vector<EditModePlugin*> plugins = SketchCADPluginLoader::getInstance()->getPluginsByType<EditModePlugin>();
    for (auto plugin : plugins)
    {
        std::shared_ptr<AbstractEditMode> edit_mode = std::shared_ptr<AbstractEditMode>(plugin->getEditMode());
        this->edit_modes.insert(std::make_pair(edit_mode->getId(), edit_mode));
        connect(edit_mode.get(), &AbstractEditMode::doAction, this, &EditModeDispatcher::doAction);
        connect(edit_mode.get(), &AbstractEditMode::objectSelected, this, &EditModeDispatcher::objectSelected);
    }
}


std::unordered_map<ID, std::shared_ptr<EditModeInfo>> EditModeDispatcher::getLoadedEditModesInfo()
{
    std::unordered_map<ID, std::shared_ptr<EditModeInfo>> result;
    for (auto& pair : this->edit_modes)
    {
        result.insert(std::make_pair(pair.first, pair.second->getEditModeInfo()));
    }
    return result;
}


std::shared_ptr<AbstractEditMode> EditModeDispatcher::getEditMode(ID id)
{
    auto it = this->edit_modes.find(id);
    if (it == this->edit_modes.end())
        return nullptr;

    return it->second;
}


ID EditModeDispatcher::getCurrentEditModeID()
{
    auto it = this->edit_modes.find(this->current_edit_mode);
    if (it == this->edit_modes.end())
        return 0;

    return this->current_edit_mode;
}


void EditModeDispatcher::setCurrentEditModeID(ID id)
{
    auto it = this->edit_modes.find(id);
    if (it != this->edit_modes.end())
        id = 0;

    this->current_edit_mode = id;
    emit this->currentEditModeIDChanged(id);
}


void EditModeDispatcher::onSchemeEventOccured(const SchemeEvent &scheme_event, const SchemeModel &scheme_model)
{
    std::shared_ptr<AbstractEditMode> edit_mode = this->getEditMode(this->getCurrentEditModeID());
    edit_mode->onSchemeEventOccured(scheme_event, scheme_model);
}
