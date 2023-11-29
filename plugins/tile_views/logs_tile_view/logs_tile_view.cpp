#include "logs_tile_view.h"
#include "ui_logs_tile_view.h"

#include <deque>


LogsTileView::LogsTileView(QWidget *parent) :
    AbstractTileView(parent),
    ui(new Ui::LogsTileView)
{
    ui->setupUi(this);

    SketchCADLogsKeeper* logs_keeper = SketchCADLogsKeeper::getInstance();
    std::deque<LogMessage> log_messages = logs_keeper->getLogMessages();
    for (auto& log_message : log_messages)
    {
        this->onNewLogMessage(log_message);
    }

    connect(logs_keeper, &SketchCADLogsKeeper::newLogMessage, this, &LogsTileView::onNewLogMessage);
}


void LogsTileView::onNewLogMessage(const LogMessage &log_message)
{
    this->ui->logs_text_edit->textCursor().movePosition(QTextCursor::End);

    QString text;
    switch (log_message.log_level)
    {
        case LogLevel::DEBUG:
            text = QString("<div style='color: black;'>%1</div><br>").arg(log_message.msg);
            break;

        case LogLevel::INFO:
            text = QString("<div style='color: blue;'>%1</div><br>").arg(log_message.msg);
            break;

        case LogLevel::WARNING:
            text = QString("<div style='color: orange;'>%1</div><br>").arg(log_message.msg);
            break;

        case LogLevel::CRITICAL:
            text = QString("<div style='color: red; font-weight: bold;'>%1</div><br>").arg(log_message.msg);
            break;

        case LogLevel::FATAL:
            text = QString("<div style='color: black; font-weight: bold;'>%1</div><br>").arg(log_message.msg);
            break;
    }

    this->ui->logs_text_edit->insertHtml(text);
}
