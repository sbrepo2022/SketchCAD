#ifndef EDITMODEPLUGIN_H
#define EDITMODEPLUGIN_H

#include "core_global.h"
#include "plugin_system/abstract_sketch_cad_plugin.h"
#include "edit_mode/abstract_edit_mode.h"

class CORE_EXPORT EditModePlugin : public AbstractSketchCADPlugin
{
public:
    virtual ~EditModePlugin() = default;
    virtual AbstractEditMode* getEditMode() = 0;
};

Q_DECLARE_INTERFACE(EditModePlugin, "scad_basic::EditModePlugin/1.0")

#endif // EDITMODEPLUGIN_H
