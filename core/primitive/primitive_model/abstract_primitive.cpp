#include "abstract_primitive.h"
#include "abstract_primitive_view_item.h"
#include "primitive/selectable_model_component/primitive_properties_component.h"
#include "primitive/primitive_model/primitive_plain_data.h"


AbstractPrimitive::AbstractPrimitive(ID id) :
    QObject(nullptr),
    IdCounterT(),
    initialized(false),
    primitive_view_manager(new PrimitiveViewItemsManager()),
    selectable_model_components_keeper(new SelectableModelComponentsKeeper()),
    marked_remove(false),
    marked_update(true)
{
    this->selectable_model_components_keeper->addComponent(std::make_unique<PrimitivePropertiesComponent>()); // inline plugin: scad_inline::PrimitivePropertiesComponentPlugin

    connect(this->selectable_model_components_keeper.get(), &SelectableModelComponentsKeeper::doAction, this, &AbstractPrimitive::doAction);

    if (id > 0)
    {
        this->id = id;
    }
}


void AbstractPrimitive::initialize()
{
    if (this->initialized) return;
    this->initialized = true;

    auto subscribe_to_primitives = this->subscribeToPrimitives();
    for (auto& primitive_weak : subscribe_to_primitives)
    {
        if (auto primitive_shared = primitive_weak.lock()) {
            connect(primitive_shared.get(), &AbstractPrimitive::update, this, &AbstractPrimitive::onUpdate);
            connect(primitive_shared.get(), &AbstractPrimitive::remove, this, &AbstractPrimitive::onRemove);
        }
    }

    auto primitive_view_items = this->createPrimitiveViewItems();
    for (auto& primitive_view_item : primitive_view_items)
    {
        this->primitive_view_manager->addPrimitiveViewItem(std::move(primitive_view_item));
    }
}

/*
 *  @brief Convert current object to plain data. Use parent class method at beginning of inherited class method to get PrimitivePlainData.
 */
PrimitivePlainData AbstractPrimitive::toPlainData() const
{
    PrimitivePlainData primitive_plain_data;
    primitive_plain_data.primitive_type_name = this->getPluginInfo()->getFullName();
    primitive_plain_data.primitive_id = this->getId();

    SelectableModelComponent* component = this->selectable_model_components_keeper->getComponentByName("scad_inline::PrimitivePropertiesComponentPlugin");
    PrimitivePropertiesComponent* primitive_properties_component = dynamic_cast<PrimitivePropertiesComponent*>(component);

    if (primitive_properties_component != nullptr)
    {
        QVariant primitive_name_variant = primitive_properties_component->property("primitive_name");
        primitive_plain_data.primitive_properties.insert(std::make_pair("primitive_name", primitive_name_variant));
    }

    return primitive_plain_data;
}


void AbstractPrimitive::fromPlainData(const PrimitivePlainData &plain_data, const SerializationContext &serialization_context)
{
    auto it = plain_data.primitive_properties.find("primitive_name");
    if (it != plain_data.primitive_properties.end())
    {
        SelectableModelComponent* component = this->selectable_model_components_keeper->getComponentByName("scad_inline::PrimitivePropertiesComponentPlugin");
        PrimitivePropertiesComponent* primitive_properties_component = dynamic_cast<PrimitivePropertiesComponent*>(component);

        if (primitive_properties_component != nullptr)
        {
            primitive_properties_component->onPrimitiveNameChanged(it->second.toString());
        }
    }

    Q_UNUSED(serialization_context)
}


void AbstractPrimitive::onUpdate(const AbstractPrimitive &primitive)
{
    this->marked_update = true;
    emit update(*this);
    Q_UNUSED(primitive)
}


void AbstractPrimitive::onRemove(const AbstractPrimitive &primitive)
{
    this->marked_remove = true;
    emit remove(*this);
    Q_UNUSED(primitive)
}
