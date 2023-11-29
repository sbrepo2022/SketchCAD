#include "tile_view_dispatcher.h"
#include "plugin_system/plugins_types/tile_view_plugin.h"
#include "plugin_system/sketch_cad_plugin_loader.h"

#include <vector>


TileViewDispatcher::TileViewDispatcher()
    : QObject{nullptr}
{
    this->tile_view_fabrics.clear();

    std::vector<TileViewPlugin*> plugins = SketchCADPluginLoader::getInstance()->getPluginsByType<TileViewPlugin>();
    for (auto plugin : plugins)
    {
        AbstractTileViewFabric* fabric = plugin->getTileViewFabric();
        this->tile_view_fabrics.emplace(fabric->getId(), std::unique_ptr<AbstractTileViewFabric>(fabric));
        connect(this, &TileViewDispatcher::currentSchemeChanged, fabric, &AbstractTileViewFabric::onCurrentSchemeChanged);
        connect(this, &TileViewDispatcher::currentEditModeChanged, fabric, &AbstractTileViewFabric::onCurrentEditModeChanged);
        connect(this, &TileViewDispatcher::objectSelected, fabric, &AbstractTileViewFabric::onObjectSelected);
    }
}


std::unordered_map<ID, std::shared_ptr<TileViewInfo>> TileViewDispatcher::getLoadedTileViewsInfo()
{
    std::unordered_map<ID, std::shared_ptr<TileViewInfo>> result;
    for (auto& pair : this->tile_view_fabrics)
    {
        result.insert(std::make_pair(pair.first, pair.second->getTileViewInfo()));
    }
    return result;
}


void TileViewDispatcher::onTileWidgetAwaitTileView(ID tile_widget_id, ID tile_view_fabric_id)
{
    auto it = this->tile_view_fabrics.find(tile_view_fabric_id);
    if (it != this->tile_view_fabrics.end())
    {
        AbstractTileView* tile_view = it->second->createTileView();
        emit this->tileViewCreated(tile_widget_id, tile_view);
    }
}
