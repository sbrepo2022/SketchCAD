#include "scheme_history.h"
#include "scheme/scheme_model/scheme_model.h"

SchemeHistory::SchemeHistory()
{

}

void SchemeHistory::doAction(const std::shared_ptr<AbstractSchemeActionCommand> &command, SchemeModel &scheme_model)
{
    this->executed_commands.push(command);
    command->doAction(scheme_model);
    std::stack<std::shared_ptr<AbstractSchemeActionCommand>>().swap(this->cancelled_commands);
}

void SchemeHistory::undoAction(SchemeModel &scheme_model)
{
    bool sequence_with_previous = false;
    do {
        std::shared_ptr<AbstractSchemeActionCommand> command = this->executed_commands.top();
        this->executed_commands.pop();
        this->cancelled_commands.push(command);
        command->undoAction(scheme_model);
        sequence_with_previous = command->isSequenceWithPrevious();
    } while(sequence_with_previous);
}

void SchemeHistory::redoAction(SchemeModel &scheme_model)
{
    bool sequence_with_previous = false;
    do {
        std::shared_ptr<AbstractSchemeActionCommand> command = this->cancelled_commands.top();
        this->cancelled_commands.pop();
        this->executed_commands.push(command);
        command->redoAction(scheme_model);
        sequence_with_previous = this->cancelled_commands.top()->isSequenceWithPrevious();
    } while(sequence_with_previous);
}
