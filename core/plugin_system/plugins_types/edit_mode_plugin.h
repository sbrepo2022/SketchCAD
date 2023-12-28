#ifndef EDITMODEPLUGIN_H
#define EDITMODEPLUGIN_H

#include "plugin_system/abstract_sketch_cad_plugin.h"
#include "edit_mode/abstract_edit_mode.h"

class EditModePlugin : public AbstractSketchCADPlugin, public EditModePluginInfoContainer
{
public:
    virtual ~EditModePlugin() = default;
    virtual AbstractEditMode* getEditMode() = 0;
};

#endif // EDITMODEPLUGIN_H
