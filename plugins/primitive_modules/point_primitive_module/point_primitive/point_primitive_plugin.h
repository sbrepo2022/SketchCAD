#ifndef POINT_PROPERTIES_COMPONENT_PLUGIN_H
#define POINT_PROPERTIES_COMPONENT_PLUGIN_H

#include "point_primitive_global.h"
#include "plugin_system/plugins_types/primitive_plugin.h"
#include "point_primitive.h"

#include <memory>


class POINT_PRIMITIVE_EXPORT PointPrimitivePlugin : public QObject, public PrimitivePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "scad_basic::AbstractSketchCADPlugin/1.0")
    Q_INTERFACES(AbstractSketchCADPlugin)

public:
    virtual AbstractPrimitiveFabric* getPrimitiveFabric() const override { return new PointPrimitiveFabric; }
    virtual std::shared_ptr<SketchCADPluginInfo> getPluginInfo() const override { return std::make_shared<PointPrimitivePluginInfo>(); }
};

#endif // POINT_PROPERTIES_COMPONENT_PLUGIN_H
