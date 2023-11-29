#ifndef TILEVIEWDISPATCHER_H
#define TILEVIEWDISPATCHER_H

#include "core_global.h"
#include "helpers/id_counter.h"
#include "edit_mode/abstract_edit_mode.h"
#include "tile_view/abstract_tile_view_fabric.h"

#include <QObject>

#include <unordered_map>
#include <memory>


class CORE_EXPORT TileViewDispatcher : public QObject
{
    Q_OBJECT

private:
    std::unordered_map<ID, std::unique_ptr<AbstractTileViewFabric>> tile_view_fabrics;


public:
    TileViewDispatcher();
    std::unordered_map<ID, std::shared_ptr<TileViewInfo>> getLoadedTileViewsInfo();


public slots:
    void onTileWidgetAwaitTileView(ID tile_widget_id, ID tile_view_fabric_id);


signals:
    void currentSchemeChanged(const std::shared_ptr<SchemeModel> &scheme);
    void currentEditModeChanged(const std::shared_ptr<AbstractEditMode> &edit_mode);
    void objectSelected(SelectableModelComponentsKeeper *selectable_model_components_keeper);
    void tileViewCreated(ID tile_widget_id, AbstractTileView* tile_view);
};

#endif // TILEVIEWDISPATCHER_H
