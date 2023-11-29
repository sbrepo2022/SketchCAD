#ifndef TILEVIEWPLUGININFOCONTAINER_H
#define TILEVIEWPLUGININFOCONTAINER_H

#include "core_global.h"
#include "tile_view/tile_view_info.h"


class CORE_EXPORT TileViewPluginInfoContainer
{
public:
    TileViewPluginInfoContainer() = default;

    virtual std::shared_ptr<TileViewInfo> getTileViewInfo() const = 0;
};

#endif // TILEVIEWPLUGININFOCONTAINER_H
