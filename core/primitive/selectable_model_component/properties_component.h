#ifndef PROPERTIESCOMPONENT_H
#define PROPERTIESCOMPONENT_H

#include "core_global.h"
#include "primitive/selectable_model_component/selectable_model_component.h"
#include "primitive/selectable_model_component/form_generator.h"

#include <QWidget>
#include <QFormLayout>
#include <memory>

class CORE_EXPORT PropertiesComponent : public SelectableModelComponent
{
    Q_OBJECT;

public:
    explicit PropertiesComponent(const std::weak_ptr<AbstractPrimitive> &linked_primitive);
    virtual ~PropertiesComponent();

protected:
    // Метод generateForm используется для генерации стандартной формы с параметрами
    // Создан для вызова в конструкторе для инициализации component_widget
    QWidget* generateForm(const QList<QMap<QString, QVariant>> &widget_properties);

private:
    FormGenerator form_generator;
};

#endif // PROPERTIESCOMPONENT_H
