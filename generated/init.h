#pragma once

#include <PFF.h>
#define ENTT_STANDARD_CPP
#include <entt/entt.hpp>

#include "procedural_meshes/simple_terrain_script.h"
#include "procedural_meshes/simple_terrain_script-generated.h"
#include "procedural_meshes/tree_generator.h"
#include "procedural_meshes/tree_generator-generated.h"
#include "test_script.h"
#include "test_script-generated.h"

#define PFF_ADD_COMPONENT_GENERATED_MACRO(name)					for (auto str_class : reflect_##name::string_to_map) {			\
																	if (str_class.first != class_name) continue;				\
																	reflect_##name::add_component(class_name, entity);			\
																	return;}

#define PFF_DISPLAY_PROPERTIE_GENERATED_MACRO(name, cast)		for (auto str_class : reflect_##name::string_to_map) {			\
																	if (str_class.first != class_name) continue;				\
																	reflect_##name::display_properties((##cast*) script);		\
																	return;}

extern "C" namespace PFF::init {

	static const char* procedural_mesh_scripts[] = {
		"test_project::simple_terrain_script",
		"test_project::tree_generator",
		nullptr
	};

	static const char* scripts[] = {
		"PFF::DefaultScript",
		nullptr
	};

	PROJECT_API void init_scripts(entt::registry* registry) {

		LOG(Info, "Initializing scripts");

		registry->storage<test_project::simple_terrain_script>();
		registry->storage<test_project::tree_generator>();
		registry->storage<PFF::DefaultScript>();

		ImGui::SetCurrentContext(application::get().get_imgui_layer()->get_context());
		reflect_simple_terrain_script_h::init();
		reflect_tree_generator_h::init();
		reflect_test_script_h::init();
	}

	PROJECT_API void add_component(std::string class_name, PFF::entity entity) {

		ASSERT(entity.is_valid(), "", "Invalid entity in script");
		PFF_ADD_COMPONENT_GENERATED_MACRO(simple_terrain_script_h);
		PFF_ADD_COMPONENT_GENERATED_MACRO(tree_generator_h);
		PFF_ADD_COMPONENT_GENERATED_MACRO(test_script_h);
	}

	PROJECT_API void display_properties(std::string class_name, entity_script* script) {

		if (!script) {
			ImGui::Text("Script pointer is null");
			return;
		}

		PFF_DISPLAY_PROPERTIE_GENERATED_MACRO(simple_terrain_script_h, test_project::simple_terrain_script);
		PFF_DISPLAY_PROPERTIE_GENERATED_MACRO(tree_generator_h, test_project::tree_generator);
		PFF_DISPLAY_PROPERTIE_GENERATED_MACRO(test_script_h, PFF::DefaultScript);
	}

	PROJECT_API const char** get_all_procedural_mesh_scripts(u32 * count) {

		if (count != nullptr)
			*count = sizeof(procedural_mesh_scripts) / sizeof(procedural_mesh_scripts[0]) - 1;			// Calculate the number of items in the array (excluding the null terminator)
		
		return procedural_mesh_scripts;
	}

	PROJECT_API const char** get_all_scripts(u32 * count) {

		if (count != nullptr)
			*count = sizeof(scripts) / sizeof(scripts[0]) - 1;			// Calculate the number of items in the array (excluding the null terminator)
		
		return scripts;
	}

}
