#ifndef SCHEMEACTIONCOMMANDPLUGIN_H
#define SCHEMEACTIONCOMMANDPLUGIN_H

#include "plugin_system/abstract_sketch_cad_plugin.h"
#include "scheme/scheme_action_command/abstract_scheme_action_command_fabric.h"

class SchemeActionCommandPlugin : public AbstractSketchCADPlugin
{
public:
    virtual ~SchemeActionCommandPlugin() = default;
    virtual AbstractSchemeActionCommandFabric* getSchemeActionCommandFabric() = 0;
};

#endif // SCHEMEACTIONCOMMANDPLUGIN_H
