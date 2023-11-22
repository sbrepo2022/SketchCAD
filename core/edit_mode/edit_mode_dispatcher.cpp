#include "edit_mode_dispatcher.h"


EditModeDispatcher::EditModeDispatcher() :
    QObject{nullptr},
    current_edit_mode(0)
{
    // TODO: Load all edit modes from plugins and connect signals/slots with edit modes
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
