
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

	};

	std::map<entt::id_type, const char*> debug_names = {

		{ entt::type_hash<simple_terrain_script>::value(), "simple_terrain_script"},
	};

	std::map<std::string, entt::id_type> string_to_map = {

		{ "simple_terrain_script", entt::type_hash<simple_terrain_script>::value() }
	};

	void init() {

		if (initialized)
			return;

		initialized = true;
		auto simple_terrain_script_factory = entt::meta<simple_terrain_script>()
			.type(entt::type_hash<simple_terrain_script>::value()); 

	}

	// simple_terrain_script
	void serialize_script(simple_terrain_script& component, const std::filesystem::path filepath, serializer::option option) { }

	void delete_scripts(entt::registry& registry) {

		registry.clear<simple_terrain_script>();
	}

	void add_component(std::string class_name, PFF::entity entity) {

		if(class_name == "simple_terrain_script") {

			if constexpr (std::is_base_of_v<entity_script, simple_terrain_script>)
				entity.add_script_component<simple_terrain_script>();

			else if constexpr (std::is_base_of_v<procedural_mesh_script, simple_terrain_script>)
				entity.add_procedural_mesh_component<simple_terrain_script>();

		}
	}

}
