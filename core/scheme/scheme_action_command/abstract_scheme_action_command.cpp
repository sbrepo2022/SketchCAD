#include "abstract_scheme_action_command.h"

AbstractSchemeActionCommand::AbstractSchemeActionCommand() :
    sequence_with_previous(false)
{

}

AbstractSchemeActionCommand::AbstractSchemeActionCommand(bool sequence_with_previous) :
    sequence_with_previous(sequence_with_previous)
{

}

AbstractSchemeActionCommand::~AbstractSchemeActionCommand()
{

}
