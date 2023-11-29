#ifndef ABSTRACTSKETCHCADPLUGIN_H
#define ABSTRACTSKETCHCADPLUGIN_H

#include "plugin_system/sketch_cad_plugin_info_container.h"

#include <QtPlugin>
#include <QString>

class AbstractSketchCADPlugin : public SketchCADPluginInfoContainer
{
private:
    QString install_dir;

public:
    virtual ~AbstractSketchCADPlugin() = default;

    void setInstallDir(const QString &install_dir) { this->install_dir = install_dir; }
    QString getInstallDir() { return this->install_dir; }
};

Q_DECLARE_INTERFACE(AbstractSketchCADPlugin, "scad_basic::AbstractSketchCADPlugin/1.0")

#endif // ABSTRACTSKETCHCADPLUGIN_H
