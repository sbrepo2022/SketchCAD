#ifndef POINTSCENEVIEWITEM_H
#define POINTSCENEVIEWITEM_H

#include "point_primitive_lib_global.h"
#include "abstract_primitive_scene_view_item.h"
#include "point_graphics_item.h"


class POINT_PRIMITIVE_LIB_EXPORT PointSceneViewItemPluginInfo : public SketchCADPluginInfo
{
    // Functional information
    virtual int getVersion() const override { return 1; }
    virtual QString getNamespace() const override { return "scad_default"; }
    virtual QString getName() const override { return "PointPropertiesComponentPlugin"; }

    // Descriptional information
    virtual QString getAuthor() const override { return "Sergey Borisov"; }
    virtual QString getAuthorEmail() const override { return "borisov123.sergey@yandex.ru"; }
    virtual QString getTitle() const override { return "Point properties"; }
    virtual QString getDescription() const override { return "Point primitive properties."; } /* getDescription() may return HTML text */
};


class POINT_PRIMITIVE_LIB_EXPORT PointSceneViewItemInfo : public PrimitiveViewItemInfo
{
    virtual QString getPrimitiveFullName() { return "scad_default::PointPrimitive"; }
    virtual QString getSchemeViewModelFullName() { return "scad_default::SceneSchemeViewModelPlugin"; }
};


class POINT_PRIMITIVE_LIB_EXPORT PointSceneViewItem : public AbstractPrimitiveSceneViewItem
{
    PointGraphicsItem* point_graphics_item;

public:
    PointSceneViewItem(const std::weak_ptr<AbstractPrimitive> &linked_primitive);
    virtual QGraphicsItem* getGraphicsItem() override;
    virtual void onLinkedPrimitiveUpdated() override;

    virtual std::shared_ptr<SketchCADPluginInfo> getPluginInfo() const override;
    virtual std::shared_ptr<PrimitiveViewItemInfo> getPrimitiveViewItemInfo() const override;
};

#endif // POINTSCENEVIEWITEM_H
