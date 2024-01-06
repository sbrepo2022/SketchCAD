#include "abstract_tile_view_fabric.h"


AbstractTileViewFabric::AbstractTileViewFabric() :
    QObject(nullptr),
    IdCounterT<AbstractTileViewFabric>(),
    SketchCADPluginInfoContainer(),
    TileViewPluginInfoContainer()
{

}


void AbstractTileViewFabric::makeConnections(AbstractTileView* tile_view)
{
    connect(this, &AbstractTileViewFabric::currentSchemeChanged, tile_view, &AbstractTileView::onCurrentSchemeChanged);
    connect(this, &AbstractTileViewFabric::currentEditModeChanged, tile_view, &AbstractTileView::onCurrentEditModeChanged);
    connect(this, &AbstractTileViewFabric::objectSelected, tile_view, &AbstractTileView::onObjectSelected);
}
