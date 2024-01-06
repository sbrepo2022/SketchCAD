#ifndef SCHEMEVIEWMODELPLUGIN_H
#define SCHEMEVIEWMODELPLUGIN_H

#include "plugin_system/abstract_sketch_cad_plugin.h"
#include "scheme/scheme_model/abstract_scheme_view_model.h"

class SchemeViewModelPlugin : public AbstractSketchCADPlugin
{
public:
    virtual ~SchemeViewModelPlugin() = default;
    virtual AbstractSchemeViewModel* getSchemeViewModel() const = 0;
};

#endif // SCHEMEVIEWMODELPLUGIN_H
