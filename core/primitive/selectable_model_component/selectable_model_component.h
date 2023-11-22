#ifndef SELECTABLEMODELCOMPONENT_H
#define SELECTABLEMODELCOMPONENT_H

#include "core_global.h"
#include "scheme/scheme_action_command/abstract_scheme_action_command.h"
#include "plugin_system/sketch_cad_plugin_info_container.h"

#include <QObject>
#include <QPointer>
#include <QWidget>
#include <memory>

class CORE_EXPORT SelectableModelComponent : public QObject, public SketchCADPluginInfoContainer
{
    Q_OBJECT

public:
    explicit SelectableModelComponent(QObject *parent = nullptr);
    virtual ~SelectableModelComponent();

    QWidget* getComponentWidget() const { return this->component_widget.get(); }

protected:
    QPointer<QWidget> component_widget;

signals:
    void doAction(const std::shared_ptr<AbstractSchemeActionCommand> &command);
};

#endif // SELECTABLEMODELCOMPONENT_H
