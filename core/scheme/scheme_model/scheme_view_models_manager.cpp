#include "scheme_view_models_manager.h"

#include "plugin_system/sketch_cad_plugin_loader.h"
#include "plugin_system/plugins_types/scheme_view_model_plugin.h"

SchemeViewModelsManager::SchemeViewModelsManager()
    : QObject(nullptr)
{
    std::vector<SchemeViewModelPlugin*> plugins = SketchCADPluginLoader::getInstance()->getPluginsByType<SchemeViewModelPlugin>();
    for (auto plugin : plugins)
    {
        AbstractSchemeViewModel* scheme_view_model = plugin->getSchemeViewModel();
        connect(scheme_view_model, &AbstractSchemeViewModel::schemeEventOccured, this, &SchemeViewModelsManager::schemeEventOccured);
        connect(scheme_view_model, &AbstractSchemeViewModel::doAction, this, &SchemeViewModelsManager::doAction);
        this->scheme_views_models.emplace(scheme_view_model->getPluginInfo()->getFullName(), scheme_view_model);
    }
}


AbstractSchemeViewModel* SchemeViewModelsManager::getSchemeViewModelByName(const QString &full_name) const
{
    return this->scheme_views_models.at(full_name).get();
}


void SchemeViewModelsManager::attachPrimitive(const std::shared_ptr<AbstractPrimitive> &primitive)
{
    for (auto it = this->scheme_views_models.begin(); it != this->scheme_views_models.end(); ++it)
    {
        it->second->attachPrimitive(primitive);
    }
}


void SchemeViewModelsManager::detachPrimitive(const std::shared_ptr<AbstractPrimitive> &primitive)
{
    for (auto it = this->scheme_views_models.begin(); it != this->scheme_views_models.end(); ++it)
    {
        it->second->detachPrimitive(primitive);
    }
}
