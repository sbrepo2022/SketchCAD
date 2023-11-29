#include "sketch_cad_logs_keeper.h"

SketchCADLogsKeeper* SketchCADLogsKeeper::instance = nullptr;


void SketchCADLogsKeeper::clipMessagesCountToMax()
{
    while (this->log_messages.size() > this->max_msg)
    {
        this->log_messages.pop_front();
    }
}


void SketchCADLogsKeeper::setMaxLogMessages(size_t max_msg)
{
    this->max_msg = max_msg;
    this->clipMessagesCountToMax();
}


void SketchCADLogsKeeper::addNewLogMessage(const LogMessage &log_message)
{
    this->log_messages.push_back(log_message);
    this->clipMessagesCountToMax();
    emit this->newLogMessage(log_message);
}

std::deque<LogMessage> SketchCADLogsKeeper::getLogMessages()
{
    return this->log_messages;
}
