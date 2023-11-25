#ifndef ABSTRACTPRIMITIVE_H
#define ABSTRACTPRIMITIVE_H

#include "core_global.h"
#include "helpers/id_counter.h"
#include "primitive/primitive_model/primitive_view_items_manager.h"
#include "primitive/selectable_model_component/selectable_model_components_keeper.h"
#include "plugin_system/sketch_cad_plugin_info_container.h"

#include <QObject>
#include <memory>

class SerializationContext;

class PrimitivePlainData;

class AbstractPrimitiveViewItem;

class SchemeTransaction;

class CORE_EXPORT AbstractPrimitive : public QObject, public IdCounterT<AbstractPrimitive>, public SketchCADPluginInfoContainer
{
    Q_OBJECT

private:
    bool initialized;

    std::unique_ptr<PrimitiveViewItemsManager> primitive_view_manager;
    std::unique_ptr<SelectableModelComponentsKeeper> selectable_model_components_keeper;
    bool marked_remove;
    bool marked_update;

protected:
    virtual std::vector<std::weak_ptr<AbstractPrimitive>> subscribeToPrimitives(); /* Returns primitives, which current primitive are subscribed to */
    virtual std::vector<std::unique_ptr<AbstractPrimitiveViewItem>> createPrimitiveViewItems(const std::shared_ptr<AbstractPrimitive> &primitive);
    virtual std::vector<std::unique_ptr<SelectableModelComponent>> createSelectableModelComponents(const std::shared_ptr<AbstractPrimitive> &primitive);

public:
    void initialize(const std::shared_ptr<AbstractPrimitive> &primitive);

    AbstractPrimitive(ID id = 0);
    virtual ~AbstractPrimitive() = default;

    bool isMarkedRemove() const { return this->marked_remove; }
    bool isMarkedUpdate() const { return this->marked_update; }
    void clearMarkRemove() { this->marked_remove = false; }
    void clearMarkUpdate() { this->marked_update = false; }

    PrimitiveViewItemsManager* getPrimitiveViewItemsManager() { return this->primitive_view_manager.get(); }
    SelectableModelComponentsKeeper* getSelectableModelComponentsKeeper() { return this->selectable_model_components_keeper.get(); }

    virtual PrimitivePlainData toPlainData() const;
    virtual void fromPlainData(const PrimitivePlainData &plain_data, const SerializationContext &serialization_context);

signals:
    void update(const AbstractPrimitive &primitive);
    void remove(const AbstractPrimitive &primitive);
    void doAction(const std::shared_ptr<AbstractSchemeActionCommand> &command);

public slots:
    virtual void onUpdate(const AbstractPrimitive &primitive);
    virtual void onRemove(const AbstractPrimitive &primitive);
};

#endif // ABSTRACTPRIMITIVE_H
