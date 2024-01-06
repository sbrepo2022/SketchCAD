#ifndef POINT_PROPERTIES_COMPONENT_H
#define POINT_PROPERTIES_COMPONENT_H

#include "point_primitive_lib_global.h"
#include "primitive/selectable_model_component/properties_component.h"


class POINT_PRIMITIVE_LIB_EXPORT PointPropertiesComponentPluginInfo : public SketchCADPluginInfo
{
    // Functional information
    virtual int getVersion() const override { return 1; }
    virtual QString getNamespace() const override { return "scad_default"; }
    virtual QString getName() const override { return "PointPropertiesComponentPlugin"; }

    // Descriptional information
    virtual QString getAuthor() const override { return "Sergey Borisov"; }
    virtual QString getAuthorEmail() const override { return "borisov123.sergey@yandex.ru"; }
    virtual QString getTitle() const override { return "Point properties"; }
    virtual QString getDescription() const override { return "Point primitive properties."; } /* getDescription() may return HTML text */
};


class POINT_PRIMITIVE_LIB_EXPORT PointPropertiesComponent : public PropertiesComponent
{
    Q_OBJECT;
    Q_PROPERTY(QPointF point_position MEMBER m_point_position NOTIFY pointPositionChanged);

private:
    QPointF m_point_position, m_point_position_old;

public:
    explicit PointPropertiesComponent(const std::weak_ptr<AbstractPrimitive> &linked_primitive);
    virtual ~PointPropertiesComponent();

    std::shared_ptr<SketchCADPluginInfo> getPluginInfo() const override;

    QPointF getPointPosition() const;
    void directSetPointPosition(QPointF point_position);

public slots:
    void onPointPositionChanged(QPointF point_position);

signals:
    void pointPositionChanged(QPointF point_position);
};

#endif // POINT_PROPERTIES_COMPONENT_H
