QT -= gui
QT += widgets

TEMPLATE = lib
DEFINES += CORE_LIBRARY

CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    edit_mode/abstract_edit_mode.cpp \
    edit_mode/edit_mode_dispatcher.cpp \
    edit_mode/edit_mode_info.cpp \
    edit_mode/edit_mode_plugin_info_container.cpp \
    logs_keeper/sketch_cad_logs_keeper.cpp \
    plugin_system/abstract_sketch_cad_plugin.cpp \
    plugin_system/plugins_types/edit_mode_plugin.cpp \
    plugin_system/plugins_types/primitive_plugin.cpp \
    plugin_system/plugins_types/primitive_view_item_plugin.cpp \
    plugin_system/plugins_types/scheme_action_command_plugin.cpp \
    plugin_system/plugins_types/scheme_view_model_plugin.cpp \
    plugin_system/plugins_types/selectable_model_component_plugin.cpp \
    plugin_system/plugins_types/tile_view_plugin.cpp \
    plugin_system/sketch_cad_plugin_info.cpp \
    plugin_system/sketch_cad_plugin_info_container.cpp \
    plugin_system/sketch_cad_plugin_loader.cpp \
    primitive/primitive_model/abstract_constraint.cpp \
    primitive/primitive_model/abstract_primitive.cpp \
    primitive/primitive_model/abstract_primitive_fabric.cpp \
    primitive/primitive_model/abstract_primitive_view_item.cpp \
    primitive/primitive_model/primitive_plain_data.cpp \
    primitive/primitive_model/primitive_view_item_info.cpp \
    primitive/primitive_model/primitive_view_item_info_container.cpp \
    primitive/primitive_model/primitive_view_items_manager.cpp \
    primitive/selectable_model_component/primitive_properties_component/primitive_name_change_action_command.cpp \
    scheme/scheme_action_command/abstract_scheme_action_command.cpp \
    scheme/scheme_action_command/abstract_scheme_action_command_fabric.cpp \
    scheme/scheme_action_command/scheme_history.cpp \
    scheme/scheme_event/scheme_event.cpp \
    scheme/scheme_model/abstract_scheme_view_model.cpp \
    scheme/scheme_model/scheme_model.cpp \
    scheme/scheme_model/scheme_transaction/scheme_transaction.cpp \
    scheme/scheme_model/scheme_transaction/scheme_transaction_interface.cpp \
    scheme/scheme_model/scheme_view_models_manager.cpp \
    primitive/selectable_model_component/selectable_model_components_keeper.cpp \
    primitive/selectable_model_component/selectable_model_component.cpp \
    primitive/selectable_model_component/properties_component.cpp \
    primitive/selectable_model_component/primitive_properties_component/primitive_properties_component.cpp \
    primitive/selectable_model_component/form_generator.cpp \
    scheme/scheme_model/schemes_dispatcher.cpp \
    scheme/scheme_serializer/abstract_scheme_serializer.cpp \
    scheme/scheme_serializer/serialization_context.cpp \
    settings_config/sketch_cad_settings_config.cpp \
    tile_view/abstract_tile_view.cpp \
    tile_view/abstract_tile_view_fabric.cpp \
    tile_view/tile_view_dispatcher.cpp \
    tile_view/tile_view_info.cpp \
    tile_view/tile_view_plugin_info_container.cpp

HEADERS += \
    edit_mode/abstract_edit_mode.h \
    edit_mode/edit_mode_dispatcher.h \
    edit_mode/edit_mode_info.h \
    edit_mode/edit_mode_plugin_info_container.h \
    helpers/id_counter.h \
    helpers/vector_to_map_with_id.h \
    logs_keeper/sketch_cad_logs_keeper.h \
    plugin_system/abstract_sketch_cad_plugin.h \
    plugin_system/plugins_types/edit_mode_plugin.h \
    plugin_system/plugins_types/primitive_plugin.h \
    plugin_system/plugins_types/primitive_view_item_plugin.h \
    plugin_system/plugins_types/scheme_action_command_plugin.h \
    plugin_system/plugins_types/scheme_view_model_plugin.h \
    plugin_system/plugins_types/selectable_model_component_plugin.h \
    plugin_system/plugins_types/tile_view_plugin.h \
    plugin_system/sketch_cad_plugin_info.h \
    plugin_system/sketch_cad_plugin_info_container.h \
    plugin_system/sketch_cad_plugin_loader.h \
    primitive/primitive_model/abstract_constraint.h \
    primitive/primitive_model/abstract_primitive.h \
    primitive/primitive_model/abstract_primitive_fabric.h \
    primitive/primitive_model/abstract_primitive_view_item.h \
    primitive/primitive_model/primitive_plain_data.h \
    primitive/primitive_model/primitive_view_item_info.h \
    primitive/primitive_model/primitive_view_item_info_container.h \
    primitive/primitive_model/primitive_view_items_manager.h \
    primitive/selectable_model_component/primitive_properties_component/primitive_name_change_action_command.h \
    scheme/scheme_action_command/abstract_scheme_action_command_fabric.h \
    scheme/scheme_model/scheme_transaction/scheme_transaction.h \
    scheme/scheme_model/scheme_transaction/scheme_transaction_interface.h \
    scheme/scheme_model/schemes_dispatcher.h \
    scheme/scheme_serializer/abstract_scheme_serializer.h \
    scheme/scheme_serializer/serialization_context.h \
    scheme/scheme_action_command/abstract_scheme_action_command.h \
    core_global.h \
    core.h \
    scheme/scheme_action_command/scheme_history.h \
    scheme/scheme_event/scheme_event.h \
    scheme/scheme_model/abstract_scheme_view_model.h \
    scheme/scheme_model/scheme_model.h \
    scheme/scheme_model/scheme_view_models_manager.h \
    primitive/selectable_model_component/selectable_model_components_keeper.h \
    primitive/selectable_model_component/selectable_model_component.h \
    primitive/selectable_model_component/properties_component.h \
    primitive/selectable_model_component/primitive_properties_component/primitive_properties_component.h \
    primitive/selectable_model_component/form_generator.h \
    settings_config/sketch_cad_settings_config.h \
    tile_view/abstract_tile_view.h \
    tile_view/abstract_tile_view_fabric.h \
    tile_view/tile_view_dispatcher.h \
    tile_view/tile_view_info.h \
    tile_view/tile_view_plugin_info_container.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
