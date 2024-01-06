#ifndef SCHEMEGRAPHICSSCENE_H
#define SCHEMEGRAPHICSSCENE_H

#include "scene_scheme_view_module_lib_global.h"
#include "scheme/scheme_event/scheme_event.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

#include <memory>

class SCENE_SCHEME_VIEW_MODULE_LIB_EXPORT SchemeGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit SchemeGraphicsScene(QObject *parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void schemeEventOccured(const std::shared_ptr<SchemeEvent> &scheme_event, QGraphicsItem *graphics_item);
};

#endif // SCHEMEGRAPHICSSCENE_H
