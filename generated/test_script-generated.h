
#pragma once

#include <PFF.h>				// main engine header
#define ENTT_STANDARD_CPP
#include <entt/core/hashed_string.hpp>
#include <entt/entt.hpp>

#include "test_script.h"

namespace PFF::reflect_test_script_h {

	using namespace entt::literals;
	bool initialized = false;

	std::vector<entt::id_type> ids = {

		"DefaultScript::m_example_float_property"_hs,
		"DefaultScript::m_example_int_property"_hs
	};

	std::map<entt::id_type, const char*> debug_names = {

		{ entt::type_hash<DefaultScript>::value(), "DefaultScript"},
		{ids[0], "m_example_float_property"},
		{ids[1], "m_example_int_property"}
	};

	std::map<std::string, entt::id_type> string_to_map = {

		{ "DefaultScript", entt::type_hash<DefaultScript>::value() }
	};

	void init() {

		if (initialized)
			return;

		initialized = true;
		auto defaultScript_factory = entt::meta<DefaultScript>()
			.data<&DefaultScript::m_example_float_property, entt::as_ref_t>(ids[0])
			.data<&DefaultScript::m_example_int_property, entt::as_ref_t>(ids[1])
			.type(entt::type_hash<DefaultScript>::value()); 

	}

	// DefaultScript
	void serialize_script(DefaultScript& component, const std::filesystem::path filepath, serializer::option option) { 

		serializer::yaml(filepath, "DefaultScript", option)
			.entry(KEY_VALUE(component.m_example_float_property))
			.entry(KEY_VALUE(component.m_example_int_property));
	}

	void delete_scripts(entt::registry& registry) {

		registry.clear<DefaultScript>();
	}

	void add_component(std::string class_name, PFF::entity entity) {

		if(class_name == "DefaultScript") {

			if constexpr (std::is_base_of_v<procedural_mesh_script, DefaultScript>)
				entity.add_procedural_mesh_component<DefaultScript>("DefaultScript");

			else if constexpr (std::is_base_of_v<entity_script, DefaultScript>)
				entity.add_script_component<DefaultScript>();

		}
	}

}
