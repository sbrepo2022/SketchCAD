#ifndef FIELDELEMENTPROPERTIESCOMPONENT_H
#define FIELDELEMENTPROPERTIESCOMPONENT_H

#include "core_global.h"
#include "plugin_system/sketch_cad_plugin_info.h"
#include "primitive/selectable_model_component/properties_component.h"


class CORE_EXPORT PrimitivePropertiesComponentPluginInfo : public SketchCADPluginInfo
{
    // Functional information
    virtual int getVersion() const override { return 1; }
    virtual QString getNamespace() const override { return "scad_inline"; }
    virtual QString getName() const override { return "PrimitivePropertiesComponentPlugin"; }

    // Descriptional information
    virtual QString getAuthor() const override { return "Sergey Borisov"; }
    virtual QString getAuthorEmail() const override { return "borisov123.sergey@yandex.ru"; }
    virtual QString getTitle() const override { return "Primitive properties"; }
    virtual QString getDescription() const override { return "Basic primitive properties."; } /* getDescription() may return HTML text */
};


class PrimitivePropertiesComponent : public PropertiesComponent
{
    Q_OBJECT;
    Q_PROPERTY(QString primitive_name MEMBER m_primitive_name NOTIFY primitiveNameChanged);

private:
    QString m_primitive_name, m_primitive_name_old;

public:
    explicit PrimitivePropertiesComponent(const std::weak_ptr<AbstractPrimitive> &linked_primitive);
    virtual ~PrimitivePropertiesComponent();

    std::shared_ptr<SketchCADPluginInfo> getPluginInfo() const override;

    QString getPrimitiveName();
    void directSetPrimitiveName(QString primitive_name);

public slots:
    void onPrimitiveNameChanged(QString primitive_name);

signals:
    void primitiveNameChanged(QString primitive_name);
};

#endif // FIELDELEMENTPROPERTIESCOMPONENT_H
