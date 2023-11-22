#include "abstract_scheme_serializer.h"

#include "helpers/vector_to_map_with_id.h"
#include "plugin_system/sketch_cad_plugin_loader.h"
#include "plugin_system/plugins_types/primitive_plugin.h"
#include "primitive/primitive_model/abstract_primitive_fabric.h"
#include "primitive/primitive_model/abstract_constraint.h"
#include "scheme/scheme_serializer/serialization_context.h"


void AbstractSchemeSerializer::loadSchemeFromStream(std::istream &in, SchemeModel &scheme_model)
{
    // Getting plain data from virtual serializer method (needs to be override in inherited class)
    std::vector<PrimitivePlainData> plain_data_objects = this->loadPlainDataFromStream(in);

    // Start transaction for doing scheme comands without direct execution
    SchemeTransaction scheme_transaction = scheme_model.createTransaction();

    // Init temporary maps
    std::unordered_map<ID, PrimitivePlainData> plain_data_map;
    std::unordered_map<ID, std::unique_ptr<AbstractPrimitiveFabric>> primitive_fabrics_map;

    // Create primitives in scheme model without initialization
    for (auto& plain_data : plain_data_objects)
    {
        plain_data_map.insert(std::make_pair(plain_data.primitive_id, plain_data));

        AbstractSketchCADPlugin* plugin = SketchCADPluginLoader::getInstance()->getPluginByName(plain_data.primitive_type_name);
        PrimitivePlugin* primitive_plugin = dynamic_cast<PrimitivePlugin*>(plugin);
        if (primitive_plugin == nullptr)
            continue;

        AbstractPrimitiveFabric *primitive_fabric = primitive_plugin->getPrimitiveFabric();
        std::shared_ptr<AbstractPrimitive> primitive = primitive_fabric->createUninitializedPrimitive(plain_data.primitive_id);
        std::shared_ptr<AbstractConstraint> constraint = std::dynamic_pointer_cast<AbstractConstraint>(primitive);
        primitive_fabrics_map.emplace(primitive->getId(), primitive_fabric);

        if (constraint)
            scheme_transaction.addConstraint(constraint);
        else
            scheme_transaction.addPrimitive(primitive);
    }

    // Create serialization context
    SerializationContext serialization_context(
        helpers::vector_to_map_with_id<std::shared_ptr<AbstractPrimitive>>(scheme_transaction.getPrimitivesToAdd()),
        helpers::vector_to_map_with_id<std::shared_ptr<AbstractConstraint>>(scheme_transaction.getConstraintsToAdd())
    );

    // Initialize primitives
    for (auto& primitive_to_add : scheme_transaction.getPrimitivesToAdd())
    {
        ID id = primitive_to_add->getId();
        primitive_fabrics_map[id]->initFromPlainData(primitive_to_add, plain_data_map[id], serialization_context);
    }

    // Apply transaction
    scheme_transaction.applyTransaction();
}


void AbstractSchemeSerializer::saveSchemeToStream(std::ostream &out, const SchemeModel &scheme_model)
{
    std::vector<PrimitivePlainData> plain_data_objects;

    for (auto& primitive_id : scheme_model.getPrimitivesIDs())
    {
        plain_data_objects.push_back(scheme_model.getPrimitive(primitive_id)->toPlainData());
    }

    this->savePlainDataToStream(out, plain_data_objects);
}
