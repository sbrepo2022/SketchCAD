#ifndef TILEVIEWPLUGIN_H
#define TILEVIEWPLUGIN_H

#include "plugin_system/abstract_sketch_cad_plugin.h"
#include "tile_view/abstract_tile_view_fabric.h"

class TileViewPlugin : public AbstractSketchCADPlugin, public TileViewPluginInfoContainer
{
public:
    virtual ~TileViewPlugin() = default;
    virtual AbstractTileViewFabric* getTileViewFabric() const = 0;
};

#endif // TILEVIEWPLUGIN_H
