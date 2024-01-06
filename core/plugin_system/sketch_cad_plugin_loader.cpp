#include "sketch_cad_plugin_loader.h"


SketchCADPluginLoader* SketchCADPluginLoader::instance = nullptr;


void SketchCADPluginLoader::loadPluginsFromDir(QString dir_path)
{
    QDir plugins_dir(dir_path);
    for (QString& filename : plugins_dir.entryList())
    {
        QPluginLoader plugin_loader(plugins_dir.absoluteFilePath(filename));
        QObject *plugin_obj = plugin_loader.instance();
        if (! plugin_obj)
        {
            qWarning() << QString("Cannot get plugin instance for '%1'").arg(plugins_dir.absoluteFilePath(filename));
            continue;
        }

        AbstractSketchCADPlugin *plugin = qobject_cast<AbstractSketchCADPlugin*>(plugin_obj);
        if (! plugin)
        {
            qWarning() << QString("Cannot cast plugin '%1' to AbstractSketchCADPlugin").arg(plugins_dir.absoluteFilePath(filename));
            continue;
        }

        QString plugin_name = plugin->getPluginInfo()->getFullName();
        auto it = this->loaded_plugins.find(plugin_name);
        if (it != this->loaded_plugins.end())
        {
            AbstractSketchCADPlugin *prev_plugin = it->second.get();
            if (prev_plugin->getPluginInfo()->getVersion() < plugin->getPluginInfo()->getVersion())
            {
                it->second = std::unique_ptr<AbstractSketchCADPlugin>(plugin);
            }
        }
        else
        {
            this->loaded_plugins.emplace(plugin_name, plugin);
        }

        qInfo() << QString("Plugin %1 (v%2) from '%3' was successfuly loaded")
                       .arg(plugin->getPluginInfo()->getFullName())
                       .arg(plugin->getPluginInfo()->getVersion())
                       .arg(plugins_dir.absolutePath());
    }
}


AbstractSketchCADPlugin* SketchCADPluginLoader::getPluginByName(const QString &full_name) const
{
    return this->loaded_plugins.at(full_name).get();
}
