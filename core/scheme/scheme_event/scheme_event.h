#ifndef SCHEMEEVENT_H
#define SCHEMEEVENT_H

#include "core_global.h"

#include "primitive/primitive_model/abstract_primitive_view_item.h"

#include <QPointF>


enum class SchemeEventType
{
    UNDEFINED,
    MOUSE_PRESS,
    MOUSE_RELEASE,
    MOUSE_MOVE
};

class CORE_EXPORT SchemeEvent
{
public:
    SchemeEventType scheme_event_type;
    QPointF scene_pos;
    AbstractPrimitiveViewItem* primitive_view_item;

    SchemeEvent() :
        scheme_event_type(SchemeEventType::UNDEFINED),
        scene_pos(QPointF(0, 0)),
        primitive_view_item(nullptr)
    {}
};

#endif // SCHEMEEVENT_H
