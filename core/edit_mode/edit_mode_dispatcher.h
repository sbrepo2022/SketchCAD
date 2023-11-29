#ifndef EDITMODEDISPATCHER_H
#define EDITMODEDISPATCHER_H

#include "core_global.h"
#include "edit_mode/abstract_edit_mode.h"

#include <QObject>

#include <memory>
#include <unordered_map>


class CORE_EXPORT EditModeDispatcher : public QObject
{
    Q_OBJECT

private:
    std::unordered_map<ID, std::shared_ptr<AbstractEditMode>> edit_modes;
    ID current_edit_mode;


public:
    EditModeDispatcher();
    std::unordered_map<ID, std::shared_ptr<EditModeInfo>> getLoadedEditModesInfo();
    std::unordered_map<ID, std::shared_ptr<SketchCADPluginInfo>> getLoadedEditModesPluginsInfo();

    std::shared_ptr<AbstractEditMode> getEditMode(ID id);

    ID getCurrentEditModeID();
    void setCurrentEditModeID(ID id);


public slots:
    void onSchemeEventOccured(const SchemeEvent &scheme_event, const SchemeModel &scheme_model);


signals:
    void currentEditModeChanged(const std::shared_ptr<AbstractEditMode> &edit_mode);
    void doAction(const std::shared_ptr<AbstractSchemeActionCommand> &command);
    void objectSelected(SelectableModelComponentsKeeper *selectable_model_components_keeper);
};

#endif // EDITMODEDISPATCHER_H
