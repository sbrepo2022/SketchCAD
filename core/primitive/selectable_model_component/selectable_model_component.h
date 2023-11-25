#ifndef SELECTABLEMODELCOMPONENT_H
#define SELECTABLEMODELCOMPONENT_H

#include "core_global.h"
#include "scheme/scheme_action_command/abstract_scheme_action_command.h"
#include "plugin_system/sketch_cad_plugin_info_container.h"

#include <QObject>
#include <QPointer>
#include <QWidget>
#include <memory>

class AbstractPrimitive;

class CORE_EXPORT SelectableModelComponent : public QObject, public SketchCADPluginInfoContainer
{
    Q_OBJECT

protected:
    QPointer<QWidget> component_widget;
    std::weak_ptr<AbstractPrimitive> linked_primitive;


public:
    explicit SelectableModelComponent(const std::weak_ptr<AbstractPrimitive> &linked_primitive);
    virtual ~SelectableModelComponent();

    QWidget* getComponentWidget() const { return this->component_widget.get(); }
    std::weak_ptr<AbstractPrimitive> getLinkedPrimitive() const { return linked_primitive; }


signals:
    void doAction(const std::shared_ptr<AbstractSchemeActionCommand> &command);
};

#endif // SELECTABLEMODELCOMPONENT_H
