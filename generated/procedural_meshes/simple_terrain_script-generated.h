
#pragma once

#include <PFF.h>				// main engine header
#define ENTT_STANDARD_CPP
#include <entt/core/hashed_string.hpp>
#include <entt/entt.hpp>

#include "procedural_meshes/simple_terrain_script.h"

namespace PFF::reflect_simple_terrain_script_h {

	using namespace entt::literals;
	bool initialized = false;

	std::vector<entt::id_type> ids = {

		"test_project::simple_terrain_script::test_f32"_hs,
		"test_project::simple_terrain_script::test_unit"_hs,
		"test_project::simple_terrain_script::test_unit_long"_hs
	};

	std::map<entt::id_type, const char*> debug_names = {

		{ entt::type_hash<test_project::simple_terrain_script>::value(), "test_project::simple_terrain_script"},
		{ids[0], "test_f32"},
		{ids[1], "test_unit"},
		{ids[2], "test_unit_long"}
	};

	std::map<std::string, entt::id_type> string_to_map = {

		{ "test_project::simple_terrain_script", entt::type_hash<test_project::simple_terrain_script>::value() }
	};

	void init() {

		if (initialized)
			return;

		initialized = true;
		auto simple_terrain_script_factory = entt::meta<test_project::simple_terrain_script>()
			.data<&test_project::simple_terrain_script::test_f32, entt::as_ref_t>(ids[0])
			.data<&test_project::simple_terrain_script::test_unit, entt::as_ref_t>(ids[1])
			.data<&test_project::simple_terrain_script::test_unit_long, entt::as_ref_t>(ids[2])
			.type(entt::type_hash<test_project::simple_terrain_script>::value()); 

	}

	void display_properties(test_project::simple_terrain_script* script) {

		UI::table_row("test_f32", script->test_f32);
		UI::table_row("test_unit", script->test_unit);
		UI::table_row("test_unit_long", script->test_unit_long);
	}

	// test_project::simple_terrain_script
	void serialize_script(test_project::simple_terrain_script& component, const std::filesystem::path filepath, serializer::option option) { 

		serializer::yaml(filepath, "test_project::simple_terrain_script", option)
			.entry(KEY_VALUE(component.test_f32))
			.entry(KEY_VALUE(component.test_unit))
			.entry(KEY_VALUE(component.test_unit_long));
	}

	void delete_scripts(entt::registry& registry) {

		registry.clear<test_project::simple_terrain_script>();
	}

	void add_component(std::string class_name, PFF::entity entity) {

		if(class_name == "test_project::simple_terrain_script")
			entity.add_procedural_mesh_component<test_project::simple_terrain_script>("test_project::simple_terrain_script");
	}

}
