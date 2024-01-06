#include "logs_tile_view.h"
#include "ui_logs_tile_view.h"

#include <deque>


LogsTileView::LogsTileView(QWidget *parent) :
    AbstractTileView(parent),
    ui(new Ui::LogsTileView)
{
    ui->setupUi(this);

    this->updateLogOutputView();

    SketchCADLogsKeeper* logs_keeper = SketchCADLogsKeeper::getInstance();
    connect(logs_keeper, &SketchCADLogsKeeper::newLogMessage, this, &LogsTileView::onNewLogMessage);
}


QString LogsTileView::getStyledLogMessage(const LogMessage &log_message)
{
    QString text;
    switch (log_message.log_level)
    {
        case LogLevel::DEBUG:
            text = QString("<div style='color: black;'>%1</div>").arg(log_message.msg);
            break;

        case LogLevel::INFO:
            text = QString("<div style='color: blue;'>%1</div>").arg(log_message.msg);
            break;

        case LogLevel::WARNING:
            text = QString("<div style='color: orange;'>%1</div>").arg(log_message.msg);
            break;

        case LogLevel::CRITICAL:
            text = QString("<div style='color: red; font-weight: bold;'>%1</div>").arg(log_message.msg);
            break;

        case LogLevel::FATAL:
            text = QString("<div style='color: black; font-weight: bold;'>%1</div>").arg(log_message.msg);
            break;
    }

    return text;
}


void LogsTileView::updateLogOutputView()
{
    SketchCADLogsKeeper* logs_keeper = SketchCADLogsKeeper::getInstance();
    std::deque<LogMessage> log_messages = logs_keeper->getLogMessages();
    QString text;
    for (auto& log_message : log_messages)
    {
        text += this->getStyledLogMessage(log_message);
    }

    QTextCursor text_cursor = this->ui->logs_text_edit->textCursor();
    text_cursor.movePosition(QTextCursor::End);
    this->ui->logs_text_edit->setTextCursor(text_cursor);

    this->ui->logs_text_edit->setHtml(text);

    text_cursor.movePosition(QTextCursor::End);
    this->ui->logs_text_edit->setTextCursor(text_cursor);
}


void LogsTileView::onNewLogMessage(const LogMessage &log_message)
{
    this->updateLogOutputView();
    Q_UNUSED(log_message);
}


AbstractTileView* LogsTileViewFabric::createTileView()
{
    AbstractTileView* tile_view = new LogsTileView();
    this->makeConnections(tile_view);
    return tile_view;
}
