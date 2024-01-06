#ifndef SCENE_SCHEME_VIEW_MODEL_PLUGIN_H
#define SCENE_SCHEME_VIEW_MODEL_PLUGIN_H

#include "scene_scheme_view_model_global.h"

#include "scene_scheme_view_model_lib.h"
#include "plugin_system/plugins_types/scheme_view_model_plugin.h"


class SCENE_SCHEME_VIEW_MODEL_EXPORT SceneSchemeViewModelPlugin : public QObject, public SchemeViewModelPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "scad_basic::AbstractSketchCADPlugin/1.0")
    Q_INTERFACES(AbstractSketchCADPlugin)

public:
    virtual AbstractSchemeViewModel* getSchemeViewModel() const override { return new SceneSchemeViewModel(); }
    virtual std::shared_ptr<SketchCADPluginInfo> getPluginInfo() const override { return std::make_shared<SceneSchemeViewModelPluginInfo>(); }
};

#endif // SCENE_SCHEME_VIEW_MODEL_PLUGIN_H
