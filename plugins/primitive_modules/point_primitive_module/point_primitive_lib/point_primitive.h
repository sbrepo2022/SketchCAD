#ifndef POINTPRIMITIVE_H
#define POINTPRIMITIVE_H

#include "point_primitive_lib_global.h"

#include "primitive/primitive_model/abstract_primitive_fabric.h"
#include "primitive/primitive_model/abstract_primitive.h"


class POINT_PRIMITIVE_LIB_EXPORT PointPrimitivePluginInfo : public SketchCADPluginInfo
{
    // Functional information
    virtual int getVersion() const override { return 1; }
    virtual QString getNamespace() const override { return "scad_default"; }
    virtual QString getName() const override { return "PointPrimitivePlugin"; }

    // Descriptional information
    virtual QString getAuthor() const override { return "Sergey Borisov"; }
    virtual QString getAuthorEmail() const override { return "borisov123.sergey@yandex.ru"; }
    virtual QString getTitle() const override { return "Point primitive"; }
    virtual QString getDescription() const override { return "Point primitive."; } /* getDescription() may return HTML text */
};


class POINT_PRIMITIVE_LIB_EXPORT PointPrimitive : public AbstractPrimitive
{
    Q_OBJECT

protected:
    virtual std::vector<std::unique_ptr<AbstractPrimitiveViewItem>> createPrimitiveViewItems(const std::shared_ptr<AbstractPrimitive> &primitive) override;
    virtual std::vector<std::unique_ptr<SelectableModelComponent>> createSelectableModelComponents(const std::shared_ptr<AbstractPrimitive> &primitive) override;

public:
    PointPrimitive(ID id = 0);

    std::shared_ptr<SketchCADPluginInfo> getPluginInfo() const override;
};


class POINT_PRIMITIVE_LIB_EXPORT PointPrimitiveFabric : public AbstractPrimitiveFabric
{
public:
    virtual std::shared_ptr<AbstractPrimitive> createPrimitive() override;
    virtual std::shared_ptr<AbstractPrimitive> createUninitializedPrimitive(ID id) override;
};


#endif // POINTPRIMITIVE_H
