#ifndef PRIMITIVENAMECHANGEACTIONCOMMAND_H
#define PRIMITIVENAMECHANGEACTIONCOMMAND_H

#include "core_global.h"
#include "scheme/scheme_model/scheme_model.h"
#include "scheme/scheme_action_command/abstract_scheme_action_command.h"

#include <QString>


class CORE_EXPORT PrimitiveComponentChangeActionCommand : public AbstractSchemeActionCommand
{
private:
    ID linked_primitive_id;
    QString old_name;
    QString new_name;

public:
    PrimitiveComponentChangeActionCommand(ID linked_primitive_id, QString old_name, QString new_name);
    virtual ~PrimitiveComponentChangeActionCommand() = default;

    virtual void doAction(const SchemeModel &scheme_model);
    virtual void undoAction(const SchemeModel &scheme_model);
    virtual void redoAction(const SchemeModel &scheme_model);
};

#endif // PRIMITIVENAMECHANGEACTIONCOMMAND_H
