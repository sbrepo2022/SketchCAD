#ifndef SCHEMEHISTORY_H
#define SCHEMEHISTORY_H

#include "core_global.h"
#include "scheme/scheme_action_command/abstract_scheme_action_command.h"

#include <memory>
#include <stack>

class CORE_EXPORT SchemeHistory
{
private:
    std::stack<std::shared_ptr<AbstractSchemeActionCommand>> executed_commands;
    std::stack<std::shared_ptr<AbstractSchemeActionCommand>> cancelled_commands;

public:
    SchemeHistory();

    void doAction(const std::shared_ptr<AbstractSchemeActionCommand> &command, SchemeModel &scheme_model);
    void undoAction(SchemeModel &scheme_model);
    void redoAction(SchemeModel &scheme_model);
};

#endif // SCHEMEHISTORY_H
