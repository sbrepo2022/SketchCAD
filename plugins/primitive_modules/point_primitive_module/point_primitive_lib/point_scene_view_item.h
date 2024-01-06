#ifndef POINTSCENEVIEWITEM_H
#define POINTSCENEVIEWITEM_H

#include "point_primitive_lib_global.h"
#include "abstract_primitive_scene_view_item.h"
#include "point_graphics_item.h"

class POINT_PRIMITIVE_LIB_EXPORT PointSceneViewItem : public AbstractPrimitiveSceneViewItem
{
    Q_OBJECT

    PointGraphicsItem* point_graphics_item;

public:
    PointSceneViewItem();
    virtual QGraphicsItem* getGraphicsItem() override;
    virtual void onLinkedPrimitiveUpdated() override;
};

#endif // POINTSCENEVIEWITEM_H
