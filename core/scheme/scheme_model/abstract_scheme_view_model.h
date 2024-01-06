#ifndef ABSTRACTSCHEMEVIEWMODEL_H
#define ABSTRACTSCHEMEVIEWMODEL_H

#include "core_global.h"
#include "scheme/scheme_event/scheme_event.h"
#include "scheme/scheme_action_command/abstract_scheme_action_command.h"
#include "primitive/primitive_model/abstract_primitive.h"
#include "plugin_system/sketch_cad_plugin_info_container.h"

#include <QObject>

#include <memory>

class CORE_EXPORT AbstractSchemeViewModel : public QObject, public SketchCADPluginInfoContainer
{
    Q_OBJECT

public:
    explicit AbstractSchemeViewModel();

public slots:
    virtual void attachPrimitive(const std::shared_ptr<AbstractPrimitive> &primitive) = 0;
    virtual void detachPrimitive(const std::shared_ptr<AbstractPrimitive> &primitive) = 0;

signals:
    void schemeEventOccured(const std::shared_ptr<SchemeEvent> &scheme_event);
    void doAction(const std::shared_ptr<AbstractSchemeActionCommand> &command);
};

#endif // ABSTRACTSCHEMEVIEWMODEL_H
