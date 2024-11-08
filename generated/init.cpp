
#include "init.h"

#define PFF_ADD_COMPONENT_GENERATED_MACRO(name)					for (auto str_class : reflect_##name::string_to_map) {					\
																	if (str_class.first != class_name) continue;						\
																	reflect_##name::add_component(class_name, entity);					\
																	return;}

#define PFF_DISPLAY_PROPERTIE_GENERATED_MACRO(name, cast)		for (auto str_class : reflect_##name::string_to_map) {					\
																	if (str_class.first != class_name) continue;						\
																	reflect_##name::display_properties((##cast*) script);				\
																	return;}

#define PFF_SERIALIZE_SCRIPT_GENERATED_MACRO(name, cast)		for (auto str_class : reflect_##name::string_to_map) {					\
																	if (str_class.first != class_name) continue;						\
																	reflect_##name::serialize_script((cast*) script, serializer);		\
																	return;}

extern "C" namespace PFF::init {

	void init_scripts(entt::registry* registry) {

		LOG(Info, "PROJECT - initializing scripts");

		registry->storage<test_project::simple_terrain_script>();
		registry->storage<test_project::tree_generator>();
		registry->storage<mesh_ops::mesh_ops>();

		ImGui::SetCurrentContext(application::get().get_imgui_layer()->get_context());
		reflect_simple_terrain_script_h::init();
		reflect_tree_generator_h::init();
		reflect_mesh_ops_test_h::init();

		LOG(Info, "PROJECT - successfully initalized scripts");
	}

	void add_component(std::string class_name, PFF::entity entity) {

		VALIDATE(entity.is_valid(), return, "", "Invalid entity in script");

		PFF_ADD_COMPONENT_GENERATED_MACRO(simple_terrain_script_h);
		PFF_ADD_COMPONENT_GENERATED_MACRO(tree_generator_h);
		PFF_ADD_COMPONENT_GENERATED_MACRO(mesh_ops_test_h);
	}

	void display_properties(std::string class_name, entity_script* script) {

		if (!script) {
			ImGui::Text("Script pointer is null");
			return;
		}

		PFF_DISPLAY_PROPERTIE_GENERATED_MACRO(simple_terrain_script_h, test_project::simple_terrain_script);
		PFF_DISPLAY_PROPERTIE_GENERATED_MACRO(tree_generator_h, test_project::tree_generator);
		PFF_DISPLAY_PROPERTIE_GENERATED_MACRO(mesh_ops_test_h, mesh_ops::mesh_ops);
	}

	void serialize_script(std::string class_name, entity_script* script, serializer::yaml& serializer) {

		PFF_SERIALIZE_SCRIPT_GENERATED_MACRO(simple_terrain_script_h, test_project::simple_terrain_script);
		PFF_SERIALIZE_SCRIPT_GENERATED_MACRO(tree_generator_h, test_project::tree_generator);
		PFF_SERIALIZE_SCRIPT_GENERATED_MACRO(mesh_ops_test_h, mesh_ops::mesh_ops);
	}

}
