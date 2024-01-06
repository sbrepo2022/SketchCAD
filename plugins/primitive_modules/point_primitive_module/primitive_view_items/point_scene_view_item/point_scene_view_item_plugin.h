#ifndef ADDPOINTEDITMODE_H
#define ADDPOINTEDITMODE_H

#include "point_scene_view_item_global.h"
#include "plugin_system/plugins_types/primitive_view_item_plugin.h"
#include "point_scene_view_item.h"

#include <memory>


class POINT_SCENE_VIEW_ITEM_EXPORT PointSceneViewItemPlugin : public QObject, public PrimitiveViewItemPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "scad_basic::AbstractSketchCADPlugin/1.0")
    Q_INTERFACES(AbstractSketchCADPlugin)

public:
    virtual AbstractPrimitiveViewItem* getPrimitiveViewItem(const std::weak_ptr<AbstractPrimitive> &linked_primitive) override { return new PointSceneViewItem(linked_primitive); }
    virtual std::shared_ptr<SketchCADPluginInfo> getPluginInfo() const override { return std::make_shared<PointSceneViewItemPluginInfo>(); }
    virtual std::shared_ptr<PrimitiveViewItemInfo> getPrimitiveViewItemInfo() const override { return std::make_shared<PointSceneViewItemInfo>(); }
};

#endif // ADDPOINTEDITMODE_H
