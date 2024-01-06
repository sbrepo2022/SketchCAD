#include "scene_scheme_view_model_lib.h"

SceneSchemeViewModel::SceneSchemeViewModel()
{
    this->scene = new SchemeGraphicsScene();
    this->scene->setSceneRect(-4000, -3000, 8000, 6000); // TODO: Сделать нормальное масштабирование сцены

    connect(this->scene, &SchemeGraphicsScene::schemeEventOccured, this, &SceneSchemeViewModel::onSchemeEventOccured);

    QPen pen(Qt::black); // цвет границы
    QBrush brush(Qt::red); // цвет заливки
    this->scene->addRect(QRectF(200, 200, 100, 100), pen, brush);
}

SceneSchemeViewModel::~SceneSchemeViewModel()
{
    if (this->scene != nullptr)
    {
        delete this->scene;
    }
}


QGraphicsScene* SceneSchemeViewModel::getScene() const
{
    return this->scene.get();
}


void SceneSchemeViewModel::attachPrimitive(const std::shared_ptr<AbstractPrimitive> &primitive)
{
    if (this->scene != nullptr)
    {
        auto view_items = primitive->getPrimitiveViewItemsManager()->getPrimitiveViewItemsByType<AbstractPrimitiveSceneViewItem>();

        for (auto& view_item : view_items)
        {
            this->scene_primitive_view_items.push_back(view_item);
            this->scene->addItem(view_item->getGraphicsItem());
        }
    }
}


void SceneSchemeViewModel::detachPrimitive(const std::shared_ptr<AbstractPrimitive> &primitive)
{
    if (this->scene != nullptr)
    {
        auto view_items = primitive->getPrimitiveViewItemsManager()->getPrimitiveViewItemsByType<AbstractPrimitiveSceneViewItem>();

        for (auto& view_item : view_items)
        {
            this->scene_primitive_view_items.remove(view_item);
            this->scene->removeItem(view_item->getGraphicsItem());
        }
    }
}


void SceneSchemeViewModel::onSchemeEventOccured(const std::shared_ptr<SchemeEvent> &scheme_event, QGraphicsItem *graphics_item)
{
    if (graphics_item != nullptr)
    {
        auto it = this->scene_primitive_view_items.begin();
        while (it != this->scene_primitive_view_items.end()) {
            if ((*it)->getGraphicsItem() == graphics_item) {
                scheme_event->primitive_view_item = *it;
                break;
            }
            ++it;
        }

        if (it == this->scene_primitive_view_items.end())
        {
            qCritical() << "Scheme event occured, QGraphicsItem provided, but AbstractPrimitiveSceneViewItem not found in SceneSchemeViewModel";
        }
    }

    emit schemeEventOccured(scheme_event);
}
