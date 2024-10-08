
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

		"PFF::DefaultScript::m_example_float_property"_hs,
		"PFF::DefaultScript::m_example_int_property"_hs,
	};

	std::map<entt::id_type, const char*> debug_names = {

		{ entt::type_hash<PFF::DefaultScript>::value(), "PFF::DefaultScript"},
		{ids[0], "m_example_float_property"},
		{ids[1], "m_example_int_property"}
	};

	std::map<std::string, entt::id_type> string_to_map = {

		{ "PFF::DefaultScript", entt::type_hash<PFF::DefaultScript>::value() },
	};

	void init() {

		//if (initialized)
		//	return;

		initialized = true;
		auto DefaultScript_factory = entt::meta<PFF::DefaultScript>()
			.data<&PFF::DefaultScript::m_example_float_property, entt::as_ref_t>(ids[0])
			.data<&PFF::DefaultScript::m_example_int_property, entt::as_ref_t>(ids[1])
			.type(entt::type_hash<PFF::DefaultScript>::value()); 

	}

	bool display_properties(PFF::DefaultScript* script) {

		// class specifiers []
		if (UI::begin_collapsing_header_section("data")) {
			UI::begin_table("entity_component", false);
			UI::table_row("m example float property##PFF::DefaultScript::m_example_float_property", script->m_example_float_property);
			UI::table_row("m example int property##PFF::DefaultScript::m_example_int_property", script->m_example_int_property);
			UI::end_table();
		}
		UI::end_collapsing_header_section();

		return false;
	}

	void serialize_script(PFF::DefaultScript* script, serializer::yaml& serializer) {

		// specifiers []
		serializer.sub_section("data", [&](serializer::yaml& data_section) {

			data_section.entry(KEY_VALUE(script->m_example_float_property))
				.entry(KEY_VALUE(script->m_example_int_property));
		});
	}

	void delete_scripts(entt::registry& registry) {

		registry.clear<PFF::DefaultScript>();
	}

	void add_component(std::string class_name, PFF::entity entity) {

		if(class_name == "PFF::DefaultScript")
			entity.add_script_component<PFF::DefaultScript>();
	}

}
