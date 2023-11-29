#include "abstract_tile_view_fabric.h"


AbstractTileViewFabric::AbstractTileViewFabric() :
    QObject(nullptr),
    IdCounterT<AbstractTileViewFabric>(),
    SketchCADPluginInfoContainer(),
    TileViewPluginInfoContainer()
{

}
