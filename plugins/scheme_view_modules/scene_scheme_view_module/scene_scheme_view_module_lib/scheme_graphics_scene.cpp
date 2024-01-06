#include "scheme_graphics_scene.h"


SchemeGraphicsScene::SchemeGraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{

}


void SchemeGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);

    QList<QGraphicsItem*> items_at_pos = items(event->scenePos());

    QGraphicsItem* top_item;
    if (items_at_pos.isEmpty())
        top_item = nullptr;
    else
        top_item = items_at_pos.first();

    auto scheme_event = std::make_shared<SchemeEvent>();
    scheme_event->scheme_event_type = SchemeEventType::MOUSE_PRESS;
    scheme_event->scene_pos = event->scenePos();
    emit schemeEventOccured(scheme_event, top_item);
}


void SchemeGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);

    QList<QGraphicsItem*> items_at_pos = items(event->scenePos());

    QGraphicsItem* top_item;
    if (items_at_pos.isEmpty())
        top_item = nullptr;
    else
        top_item = items_at_pos.first();

    auto scheme_event = std::make_shared<SchemeEvent>();
    scheme_event->scheme_event_type = SchemeEventType::MOUSE_RELEASE;
    scheme_event->scene_pos = event->scenePos();
    emit schemeEventOccured(scheme_event, top_item);
}


void SchemeGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // TODO: Сделать так, чтобы при любом движении (неважно, нажата мышка или нет) высылалось событие
    QGraphicsScene::mousePressEvent(event);

    QList<QGraphicsItem*> items_at_pos = items(event->scenePos());

    QGraphicsItem* top_item;
    if (items_at_pos.isEmpty())
        top_item = nullptr;
    else
        top_item = items_at_pos.first();

    auto scheme_event = std::make_shared<SchemeEvent>();
    scheme_event->scheme_event_type = SchemeEventType::MOUSE_MOVE;
    scheme_event->scene_pos = event->scenePos();
    emit schemeEventOccured(scheme_event, top_item);
}
