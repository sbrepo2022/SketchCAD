#ifndef SKETCHCADLOGSKEEPER_H
#define SKETCHCADLOGSKEEPER_H

#include "core_global.h"

#include <QObject>

#include <deque>

enum class LogLevel
{
    DEBUG,
    INFO,
    WARNING,
    CRITICAL,
    FATAL
};


struct LogMessage
{
    LogLevel log_level;
    QString msg;
};


class CORE_EXPORT SketchCADLogsKeeper : public QObject
{
    Q_OBJECT

// Singletone specific realization
private:
    // Private constructor and destructor
    SketchCADLogsKeeper() {};
    ~SketchCADLogsKeeper() {}

    // Forbiden copy and assigning
    SketchCADLogsKeeper(const SketchCADLogsKeeper&) = delete;
    SketchCADLogsKeeper& operator=(const SketchCADLogsKeeper&) = delete;

    static SketchCADLogsKeeper* instance;

public:
    // Static method for singletone instance getting
    static SketchCADLogsKeeper* getInstance() {
        if (instance == nullptr) {
            instance = new SketchCADLogsKeeper();
        }
        return instance;
    }

// Functional data and methods
private:
    size_t max_msg;
    std::deque<LogMessage> log_messages;

    void clipMessagesCountToMax();

public:
    void setMaxLogMessages(size_t max_msg);
    void addNewLogMessage(const LogMessage &log_message);
    std::deque<LogMessage> getLogMessages();

signals:
    void newLogMessage(const LogMessage &log_message);
};

#endif // SKETCHCADLOGSKEEPER_H
