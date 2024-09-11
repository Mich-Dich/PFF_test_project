
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

		"test_project::simple_terrain_script::height_scale"_hs,
	};

	std::map<entt::id_type, const char*> debug_names = {

		{ entt::type_hash<test_project::simple_terrain_script>::value(), "test_project::simple_terrain_script"},
		{ids[0], "height_scale"}
	};

	std::map<std::string, entt::id_type> string_to_map = {

		{ "test_project::simple_terrain_script", entt::type_hash<test_project::simple_terrain_script>::value() },
	};

	void init() {

		//if (initialized)
		//	return;

		initialized = true;
		auto simple_terrain_script_factory = entt::meta<test_project::simple_terrain_script>()
			.data<&test_project::simple_terrain_script::height_scale, entt::as_ref_t>(ids[0])
			.type(entt::type_hash<test_project::simple_terrain_script>::value()); 

	}

	bool display_properties(test_project::simple_terrain_script* script) {

		// class specifiers []
		if (UI::begin_collapsing_header_section("data")) {
			UI::begin_table("entity_component", false);
			UI::table_row("height scale##test_project::simple_terrain_script::height_scale", script->height_scale, static_cast<f32>(10.f), static_cast<f32>(200.f), static_cast<f32>(200.f));
			UI::end_table();
		}
		UI::end_collapsing_header_section();

		return false;
	}

	void serialize_script(test_project::simple_terrain_script* script, serializer::yaml& serializer) {

		// specifiers []
		serializer.sub_section("data", [&](serializer::yaml& data_section) {

			data_section.entry(KEY_VALUE(script->height_scale));
		});
	}

	void delete_scripts(entt::registry& registry) {

		registry.clear<test_project::simple_terrain_script>();
	}

	void add_component(std::string class_name, PFF::entity entity) {

		if(class_name == "test_project::simple_terrain_script")
			entity.add_procedural_mesh_component<test_project::simple_terrain_script>("test_project::simple_terrain_script");
	}

}
