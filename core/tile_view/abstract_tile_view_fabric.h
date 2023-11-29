#ifndef ABSTRACTTILEVIEWFABRIC_H
#define ABSTRACTTILEVIEWFABRIC_H

#include "core_global.h"
#include "tile_view/abstract_tile_view.h"
#include "edit_mode/abstract_edit_mode.h"
#include "tile_view/tile_view_plugin_info_container.h"

#include <QObject>

class CORE_EXPORT AbstractTileViewFabric : public QObject, public IdCounterT<AbstractTileViewFabric>, public SketchCADPluginInfoContainer, public TileViewPluginInfoContainer
{
    Q_OBJECT

public:
    AbstractTileViewFabric();
    virtual ~AbstractTileViewFabric() = default;
    virtual AbstractTileView* createTileView() = 0;

public slots:
    virtual void onCurrentSchemeChanged(const std::shared_ptr<SchemeModel> &scheme) {}
    virtual void onCurrentEditModeChanged(const std::shared_ptr<AbstractEditMode> &edit_mode) {}
    virtual void onObjectSelected(SelectableModelComponentsKeeper *selectable_model_components_keeper) {}
};

#endif // ABSTRACTTILEVIEWFABRIC_H
