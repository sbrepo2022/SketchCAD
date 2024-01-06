#ifndef POINT_POSITION_CHANGE_ACTION_COMMAND_H
#define POINT_POSITION_CHANGE_ACTION_COMMAND_H

#include "point_primitive_lib_global.h"
#include "scheme/scheme_model/scheme_model.h"
#include "scheme/scheme_action_command/abstract_scheme_action_command.h"

#include <QString>


class POINT_PRIMITIVE_LIB_EXPORT PointPositionChangeActionCommand : public AbstractSchemeActionCommand
{
private:
    ID linked_primitive_id;
    QPointF old_point_position;
    QPointF new_point_position;

public:
    PointPositionChangeActionCommand(ID linked_primitive_id, QPointF old_point_position, QPointF new_point_position);
    virtual ~PointPositionChangeActionCommand() = default;

    virtual void doAction(const SchemeModel &scheme_model);
    virtual void undoAction(const SchemeModel &scheme_model);
    virtual void redoAction(const SchemeModel &scheme_model);
};


#endif // POINT_POSITION_CHANGE_ACTION_COMMAND_H
