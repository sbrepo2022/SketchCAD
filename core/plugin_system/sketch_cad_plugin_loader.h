#ifndef SKETCHCADPLUGINLOADER_H
#define SKETCHCADPLUGINLOADER_H

#include "core_global.h"
#include "plugin_system/abstract_sketch_cad_plugin.h"

#include <QDir>
#include <QPluginLoader>

#include <memory>
#include <unordered_map>
#include <vector>

class CORE_EXPORT SketchCADPluginLoader
{
// Singletone specific realization
private:
    // Private constructor and destructor
    SketchCADPluginLoader() {}
    ~SketchCADPluginLoader() {}

    // Forbiden copy and assigning
    SketchCADPluginLoader(const SketchCADPluginLoader&) = delete;
    SketchCADPluginLoader& operator=(const SketchCADPluginLoader&) = delete;

    static SketchCADPluginLoader* instance;

public:
    // Static method for singletone instance getting
    static SketchCADPluginLoader* getInstance() {
        if (instance == nullptr) {
            instance = new SketchCADPluginLoader();
        }
        return instance;
    }

// Functional data and methods
private:
    std::unordered_map<QString, std::unique_ptr<AbstractSketchCADPlugin>> loaded_plugins;

public:
    void loadPluginsFromDir(QString dir_path);

    template<class T>
    std::vector<T*> getPluginsByType() const
    {
        std::vector<T*> result;
        for (auto it = this->loaded_plugins.begin(); it != this->loaded_plugins.end(); ++it)
        {
            T* ptr = dynamic_cast<T*>(it->second.get());
            if (ptr != nullptr)
            {
                result.push_back(ptr);
            }
        }
        return result;
    }

    AbstractSketchCADPlugin* getPluginByName(const QString &full_name) const;
};

#endif // SKETCHCADPLUGINLOADER_H
