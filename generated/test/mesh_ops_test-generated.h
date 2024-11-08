
#pragma once

#include <PFF.h>				// main engine header
#define ENTT_STANDARD_CPP
#include <entt/core/hashed_string.hpp>
#include <entt/entt.hpp>

#include "test/mesh_ops_test.h"

namespace PFF::reflect_mesh_ops_test_h {

	using namespace entt::literals;
	bool initialized = false;

	std::vector<entt::id_type> ids = {

	};

	std::map<entt::id_type, const char*> debug_names = {

		{ entt::type_hash<mesh_ops::mesh_ops>::value(), "mesh_ops::mesh_ops"},
	};

	std::map<std::string, entt::id_type> string_to_map = {

		{ "mesh_ops::mesh_ops", entt::type_hash<mesh_ops::mesh_ops>::value() },
	};

	void init() {

		//if (initialized)
		//	return;

		initialized = true;
		auto mesh_ops_factory = entt::meta<mesh_ops::mesh_ops>()
			.type(entt::type_hash<mesh_ops::mesh_ops>::value()); 

	}

	bool display_properties(mesh_ops::mesh_ops* script) {

		// class specifiers []
		return false;
	}

	void serialize_script(mesh_ops::mesh_ops* script, serializer::yaml& serializer) {

		// specifiers []
	}

	void delete_scripts(entt::registry& registry) {

		registry.clear<mesh_ops::mesh_ops>();
	}

	void add_component(std::string class_name, PFF::entity entity) {

		if(class_name == "mesh_ops::mesh_ops")
			entity.add_procedural_mesh_component<mesh_ops::mesh_ops>("mesh_ops::mesh_ops");
	}

}
