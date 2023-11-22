#include "sketch_cad_plugin_loader.h"


SketchCADPluginLoader* SketchCADPluginLoader::instance = nullptr;


void SketchCADPluginLoader::loadPluginsFromDir(QString dir_path)
{
    QDir plugins_dir(dir_path);
    for (QString& filename : plugins_dir.entryList())
    {
        QPluginLoader pluginLoader(plugins_dir.absoluteFilePath(filename));
        QObject *plugin_obj = pluginLoader.instance();
        if (plugin_obj) {
            AbstractSketchCADPlugin *plugin = qobject_cast<AbstractSketchCADPlugin*>(plugin_obj);

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
        }
    }
}


AbstractSketchCADPlugin* SketchCADPluginLoader::getPluginByName(const QString &full_name) const
{
    return this->loaded_plugins.at(full_name).get();
}
