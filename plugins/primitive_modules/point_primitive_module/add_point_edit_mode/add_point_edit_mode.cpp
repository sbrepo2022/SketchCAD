#include "add_point_edit_mode.h"

void AddPointEditMode::onSchemeEventOccured(const std::shared_ptr<SchemeEvent> &scheme_event, const SchemeModel &scheme_model)
{
    qDebug() << QString("Scheme event got in AddPointEditMode: (%1, %2)")
                .arg(scheme_event->scene_pos.x()).arg(scheme_event->scene_pos.y());
}
