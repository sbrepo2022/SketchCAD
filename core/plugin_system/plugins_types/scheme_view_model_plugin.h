#ifndef SCHEMEVIEWMODELPLUGIN_H
#define SCHEMEVIEWMODELPLUGIN_H

#include "core_global.h"
#include "plugin_system/abstract_sketch_cad_plugin.h"
#include "scheme/scheme_model/abstract_scheme_view_model.h"

class CORE_EXPORT SchemeViewModelPlugin : public AbstractSketchCADPlugin
{
public:
    virtual ~SchemeViewModelPlugin() = default;
    virtual AbstractSchemeViewModel* getSchemeViewModel() = 0;
};

Q_DECLARE_INTERFACE(SchemeViewModelPlugin, "scad_basic::SchemeViewModelPlugin/1.0")

#endif // SCHEMEVIEWMODELPLUGIN_H
