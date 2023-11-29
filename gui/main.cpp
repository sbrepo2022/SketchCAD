#include "mainwindow.h"

#include "plugin_system/sketch_cad_plugin_loader.h"
#include "settings_config/sketch_cad_settings_config.h"
#include "logs_keeper/sketch_cad_logs_keeper.h"

#include <QJsonValue>
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QFile>
#include <QDateTime>

#include <optional>


QFile log_file;


void setupTheme(QApplication &app);
void setupTranslator(QApplication &app);

void setupPreLogging();
void setupLogger();
void writeMsgToLogFile(QString text);
void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

void loadPlugins();


int main(int argc, char *argv[])
{
    setupPreLogging();

    QApplication app(argc, argv);

    // Set default executable dir
    QString executable_dir = QCoreApplication::applicationDirPath();
    QDir::setCurrent(executable_dir);

    setupTheme(app);
    setupTranslator(app);

    SketchCADSettingsConfig::getInstance()->setupAppSettingsDefault();
    SketchCADSettingsConfig::getInstance()->readSettingsOverrided();

    setupLogger();
    loadPlugins();

    SketchCADSettingsConfig::getInstance()->setupPluginsSettingsDefault();
    SketchCADSettingsConfig::getInstance()->writeSettingsDefault();

    MainWindow window;
    window.showMaximized();
    return app.exec();
}


void setupTheme(QApplication &app)
{
    QFile file(":/theme.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        app.setStyleSheet(stream.readAll());
    }
}


void setupTranslator(QApplication &app)
{
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "translate_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }
}


void setupPreLogging()
{
    SketchCADLogsKeeper::getInstance()->setMaxLogMessages(1000);
    qInstallMessageHandler(customMessageHandler);
}


void setupLogger()
{
    if (auto logs_dir_optional = SketchCADSettingsConfig::getInstance()->getNestedValue(QString("app"), QString("logs_dir")))
    {
        if (log_file.isOpen())
        {
            log_file.close();
        }

        QDir log_file_dir(logs_dir_optional->toString());
        if (!log_file_dir.exists()) {
            log_file_dir.mkpath(".");
        }

        QString time_stamp = QDateTime::currentDateTime().toString("yyyy_MM_dd__hh_mm_ss");
        QString log_file_name = QString("%1_%2").arg(time_stamp).arg("logs.txt");

        log_file.setFileName(log_file_dir.absoluteFilePath(log_file_name));
        log_file.open(QIODevice::WriteOnly | QIODevice::Append);

        // Write messages, which appears while log file was not init
        for (auto& log_message : SketchCADLogsKeeper::getInstance()->getLogMessages())
        {
            writeMsgToLogFile(log_message.msg);
        }
    }
    else
    {
        qCritical() << "Cannot setup logging to file, no logs_dir option in settings.\n";
    }

    if (auto max_logs_msg_optional = SketchCADSettingsConfig::getInstance()->getNestedValue(QString("app"), QString("max_logs_msg")))
    {
        SketchCADLogsKeeper::getInstance()->setMaxLogMessages(max_logs_msg_optional->toInt());
    }
}


void writeMsgToLogFile(QString text)
{
    if (log_file.isOpen()) {
        QTextStream stream(&log_file);
        stream << text << "\n";
    }
}


void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    QString time_stamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString text;

    switch (type) {
    case QtDebugMsg:
        text = QString("[%1] Debug: %2").arg(time_stamp, msg);
        SketchCADLogsKeeper::getInstance()->addNewLogMessage({LogLevel::DEBUG, text});
        fprintf(stdout, "%s\n", text.toLocal8Bit().constData());
        return;
    case QtInfoMsg:
        text = QString("[%1] Info: %2").arg(time_stamp, msg);
        SketchCADLogsKeeper::getInstance()->addNewLogMessage({LogLevel::INFO, text});
        fprintf(stdout, "%s\n", text.toLocal8Bit().constData());
        break;
    case QtWarningMsg:
        text = QString("[%1] Warning: %2").arg(time_stamp, msg);
        SketchCADLogsKeeper::getInstance()->addNewLogMessage({LogLevel::WARNING, text});
        fprintf(stdout, "%s\n", text.toLocal8Bit().constData());
        break;
    case QtCriticalMsg:
        text = QString("[%1] Critical: %2").arg(time_stamp, msg);
        SketchCADLogsKeeper::getInstance()->addNewLogMessage({LogLevel::CRITICAL, text});
        fprintf(stderr, "%s\n", text.toLocal8Bit().constData());
        break;
    case QtFatalMsg:
        text = QString("[%1] Fatal: %2").arg(time_stamp, msg);
        SketchCADLogsKeeper::getInstance()->addNewLogMessage({LogLevel::FATAL, text});
        fprintf(stderr, "%s\n", text.toLocal8Bit().constData());
        break;
    }

    writeMsgToLogFile(text);

    Q_UNUSED(context)
}


void loadPlugins()
{
    if (auto  plugins_dirs_optional = SketchCADSettingsConfig::getInstance()->getNestedValue(QString("app"), QString("plugins_dirs")))
    {
        QJsonArray plugins_dirs =  plugins_dirs_optional->toArray();
        for (const QJsonValue& plugins_dir_value : plugins_dirs)
        {
            size_t before_loading_size = SketchCADPluginLoader::getInstance()->size();
            SketchCADPluginLoader::getInstance()->loadPluginsFromDir(plugins_dir_value.toString());
            size_t after_loading_size = SketchCADPluginLoader::getInstance()->size();
            qInfo() << QString("%1 plugin(s) loaded from '%2' directory").arg(after_loading_size - before_loading_size).arg(plugins_dir_value.toString());
        }
    }
    else
    {
        qCritical() << QString("No plugins_dirs option specified in settings, plugins could not loaded");
        return;
    }
}
