
#pragma once

#include <PFF.h>				// main engine header
#define ENTT_STANDARD_CPP
#include <entt/core/hashed_string.hpp>
#include <entt/entt.hpp>

#include "procedural_meshes/tree_generator.h"

namespace PFF::reflect_tree_generator_h {

	using namespace entt::literals;
	bool initialized = false;

	std::vector<entt::id_type> ids = {

		"test_project::point::position"_hs,
		"test_project::point::direction"_hs,
		"test_project::point::length"_hs,
		"test_project::point::size"_hs,
		"test_project::point::children"_hs,
		"test_project::tree_generator::trunk_direction"_hs,
		"test_project::tree_generator::trunk_length"_hs,
		"test_project::tree_generator::trunk_size"_hs,
		"test_project::tree_generator::max_depth"_hs,
	};

	std::map<entt::id_type, const char*> debug_names = {

		{ entt::type_hash<test_project::point>::value(), "test_project::point"},
		{ids[0], "position"},
		{ids[1], "direction"},
		{ids[2], "length"},
		{ids[3], "size"},
		{ids[4], "children"},
		{ entt::type_hash<test_project::tree_generator>::value(), "test_project::tree_generator"},
		{ids[5], "trunk_direction"},
		{ids[6], "trunk_length"},
		{ids[7], "trunk_size"},
		{ids[8], "max_depth"}
	};

	std::map<std::string, entt::id_type> string_to_map = {

		{ "test_project::point", entt::type_hash<test_project::point>::value() },
		{ "test_project::tree_generator", entt::type_hash<test_project::tree_generator>::value() },
	};

	void init() {

		if (initialized)
			return;

		initialized = true;
		auto point_factory = entt::meta<test_project::point>()
			.data<&test_project::point::position, entt::as_ref_t>(ids[0])
			.data<&test_project::point::direction, entt::as_ref_t>(ids[1])
			.data<&test_project::point::length, entt::as_ref_t>(ids[2])
			.data<&test_project::point::size, entt::as_ref_t>(ids[3])
			.data<&test_project::point::children, entt::as_ref_t>(ids[4])
			.type(entt::type_hash<test_project::point>::value()); 

		auto tree_generator_factory = entt::meta<test_project::tree_generator>()
			.data<&test_project::tree_generator::trunk_direction, entt::as_ref_t>(ids[5])
			.data<&test_project::tree_generator::trunk_length, entt::as_ref_t>(ids[6])
			.data<&test_project::tree_generator::trunk_size, entt::as_ref_t>(ids[7])
			.data<&test_project::tree_generator::max_depth, entt::as_ref_t>(ids[8])
			.type(entt::type_hash<test_project::tree_generator>::value()); 

	}

	void display_properties(test_project::point* script) {

		// class specifiers []
		if (UI::begin_collapsing_header_section("data")) {
			UI::begin_table("entity_component", false);
			UI::table_row("position##test_project::point::position", script->position);
			UI::table_row("direction##test_project::point::direction", script->direction);
			UI::table_row("length##test_project::point::length", script->length);
			UI::table_row("size##test_project::point::size", script->size);
			UI::table_row("children##test_project::point::children", script->children);
			UI::end_table();
		}
		UI::end_collapsing_header_section();

	}

	void display_properties(test_project::tree_generator* script) {

		// class specifiers [rebuild_on_property_change]
		bool changed = false;
		if (UI::begin_collapsing_header_section("trunk")) {
			UI::begin_table("entity_component", false);
			changed |= UI::table_row("direction##test_project::tree_generator::trunk_direction", script->trunk_direction, static_cast<f32>(0.01f), static_cast<glm::vec3>(0.f), static_cast<glm::vec3>(1.f));
			changed |= UI::table_row("length##test_project::tree_generator::trunk_length", script->trunk_length, static_cast<f32>(0.01f), static_cast<f32>(0.f), static_cast<f32>(1.f));
			changed |= UI::table_row("size##test_project::tree_generator::trunk_size", script->trunk_size, static_cast<f32>(0.01f), static_cast<f32>(0.f), static_cast<f32>(1.f));
			changed |= UI::table_row("max depth##test_project::tree_generator::max_depth", script->max_depth, static_cast<f32>(0.01f), static_cast<u32>(0.f), static_cast<u32>(1.f));
			UI::end_table();
		}
		UI::end_collapsing_header_section();

		if (changed)
			script->on_rebuild();
	}

	// test_project::tree_generator
	void serialize_script(test_project::tree_generator& component, const std::filesystem::path filepath, serializer::option option) { 

		serializer::yaml(filepath, "test_project::tree_generator", option)
			.entry(KEY_VALUE(component.trunk_direction))
			.entry(KEY_VALUE(component.trunk_length))
			.entry(KEY_VALUE(component.trunk_size))
			.entry(KEY_VALUE(component.max_depth));
	}

	void delete_scripts(entt::registry& registry) {

		registry.clear<test_project::tree_generator>();
	}

	void add_component(std::string class_name, PFF::entity entity) {

		if(class_name == "test_project::tree_generator")
			entity.add_procedural_mesh_component<test_project::tree_generator>("test_project::tree_generator");
	}

}
