#ifndef ABSTRACTEDITMODE_H
#define ABSTRACTEDITMODE_H

#include "core_global.h"
#include "helpers/id_counter.h"
#include "edit_mode/edit_mode_info.h"
#include "scheme/scheme_model/scheme_model.h"
#include "scheme/scheme_event/scheme_event.h"
#include "plugin_system/sketch_cad_plugin_info_container.h"

#include <QObject>

#include <memory>

class CORE_EXPORT AbstractEditMode : public QObject, public IdCounterT<AbstractEditMode>, public SketchCADPluginInfoContainer
{
    Q_OBJECT

public:
    virtual ~AbstractEditMode() = default;

    virtual EditModeInfo* getEditModeInfo() = 0;


public slots:
    virtual void onSchemeEventOccured(const SchemeEvent &scheme_event, const SchemeModel &scheme_model) = 0;


signals:
    void doAction(const std::shared_ptr<AbstractSchemeActionCommand> &command);
    void objectSelected(SelectableModelComponentsKeeper *selectable_model_components_keeper);
};

#endif // ABSTRACTEDITMODE_H
