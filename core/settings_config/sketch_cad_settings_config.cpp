#include "sketch_cad_settings_config.h"

#include "plugin_system/sketch_cad_plugin_loader.h"

#include <QCoreApplication>

#include <vector>


SketchCADSettingsConfig* SketchCADSettingsConfig::instance = nullptr;


SketchCADSettingsConfig::SketchCADSettingsConfig()
{

}


QDir SketchCADSettingsConfig::getConfigDirectory()
{
    QString app_dir_path = QCoreApplication::applicationDirPath();
    QDir dir(app_dir_path);
    QString config_path = dir.filePath("config");
    return QDir(config_path);
}


void SketchCADSettingsConfig::readSettingsOverrided()
{
    // Create dir for settings file
    QDir settings_dir = SketchCADSettingsConfig::getConfigDirectory();
    if (!settings_dir.exists()) {
        settings_dir.mkpath(".");
    }

    // Read overrided settings file
    QFile file_in(settings_dir.filePath("app_settings_override.json"));

    if (!file_in.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Cannot open 'app_settings_override.json' file for reading. Creating an empty file.";
        file_in.close();

        QFile file_create(settings_dir.filePath("app_settings_override.json"));
        if (!file_create.open(QIODevice::WriteOnly))
        {
            qWarning() << "Failed to open 'app_settings_override.json' file for writing";
        }
        return;
    }

    QByteArray json_data = file_in.readAll();
    file_in.close();

    QJsonParseError parse_error;
    QJsonDocument app_settings_overrided_json = QJsonDocument::fromJson(json_data, &parse_error);

    if (parse_error.error != QJsonParseError::NoError)
    {
        qWarning() << QString("'app_settings_override.json' parse error (code: %1) at %2: ").arg(parse_error.error).arg(parse_error.offset) + parse_error.errorString();
        return;
    }

    if (app_settings_overrided_json.isNull())
    {
        qWarning() << "Failed to create JSON doc from 'app_settings_override.json'";
        return;
    }

    if (!app_settings_overrided_json.isObject())
    {
        qWarning() << "JSON in 'app_settings_override.json' file is not an object.";
        return;
    }

    this->app_settings_overrided = app_settings_overrided_json.object();
}


void SketchCADSettingsConfig::setupAppSettingsDefault()
{
    // Setup default app config
    QJsonObject app_root;

    // -------------------

    QJsonArray plugins_dirs;
    plugins_dirs.append("plugins/");
    app_root["plugins_dirs"] = plugins_dirs;

    QJsonValue logs_dir("logs");
    app_root["logs_dir"] = logs_dir;

    QJsonValue max_logs_msg(500);
    app_root["max_logs_msg"] = max_logs_msg;

    // -------------------

    this->app_settings_default["app"] = app_root;
}


void SketchCADSettingsConfig::setupPluginsSettingsDefault()
{
    std::vector<AbstractSketchCADPlugin*> plugins = SketchCADPluginLoader::getInstance()->getPluginsByType<AbstractSketchCADPlugin>();

    for (auto plugin : plugins)
    {
        if (std::optional<QJsonObject> plugin_settings = plugin->getPluginInfo()->getDefaultSettings())
        {
            this->app_settings_default[plugin->getPluginInfo()->getFullName()] = *plugin_settings;
        }
    }
}


void SketchCADSettingsConfig::writeSettingsDefault()
{
    // Create dir for settings file
    QDir settings_dir = SketchCADSettingsConfig::getConfigDirectory();
    if (!settings_dir.exists()) {
        settings_dir.mkpath(".");
    }

    // Rewrite default settings file
    QJsonDocument app_settings_default_json(this->app_settings_default);

    QFile file_out(settings_dir.filePath("app_settings_default.json"));
    if (file_out.open(QIODevice::WriteOnly))
    {
        file_out.write(app_settings_default_json.toJson());
        file_out.close();
    }
    else
    {
        qWarning() << "Failed to open 'app_settings_default.json' file for writing";
    }
}
