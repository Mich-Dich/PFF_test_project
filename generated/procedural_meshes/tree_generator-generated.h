
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
		"test_project::tree_generator::direction"_hs,
		"test_project::tree_generator::starting_size"_hs,
		"test_project::tree_generator::random_seed"_hs,
		"test_project::tree_generator::trunk_section_length"_hs,
		"test_project::tree_generator::trunk_section_length_variation"_hs,
		"test_project::tree_generator::trunk_split_chance"_hs,
		"test_project::tree_generator::trunk_segment_count"_hs,
		"test_project::tree_generator::trunk_segment_count_variation"_hs,
		"test_project::tree_generator::branch_section_length"_hs,
		"test_project::tree_generator::branch_section_length_variation"_hs,
		"test_project::tree_generator::branch_direction_variation"_hs,
		"test_project::tree_generator::branch_split_chance"_hs,
		"test_project::tree_generator::branch_segment_count"_hs,
		"test_project::tree_generator::branch_segment_count_variation"_hs,
	};

	std::map<entt::id_type, const char*> debug_names = {

		{ entt::type_hash<test_project::point>::value(), "test_project::point"},
		{ids[0], "position"},
		{ids[1], "direction"},
		{ids[2], "length"},
		{ids[3], "size"},
		{ids[4], "children"},
		{ entt::type_hash<test_project::tree_generator>::value(), "test_project::tree_generator"},
		{ids[5], "direction"},
		{ids[6], "starting_size"},
		{ids[7], "random_seed"},
		{ids[8], "trunk_section_length"},
		{ids[9], "trunk_section_length_variation"},
		{ids[10], "trunk_split_chance"},
		{ids[11], "trunk_segment_count"},
		{ids[12], "trunk_segment_count_variation"},
		{ids[13], "branch_section_length"},
		{ids[14], "branch_section_length_variation"},
		{ids[15], "branch_direction_variation"},
		{ids[16], "branch_split_chance"},
		{ids[17], "branch_segment_count"},
		{ids[18], "branch_segment_count_variation"}
	};

	std::map<std::string, entt::id_type> string_to_map = {

		{ "test_project::point", entt::type_hash<test_project::point>::value() },
		{ "test_project::tree_generator", entt::type_hash<test_project::tree_generator>::value() },
	};

	void init() {

		//if (initialized)
		//	return;

		initialized = true;
		auto point_factory = entt::meta<test_project::point>()
			.data<&test_project::point::position, entt::as_ref_t>(ids[0])
			.data<&test_project::point::direction, entt::as_ref_t>(ids[1])
			.data<&test_project::point::length, entt::as_ref_t>(ids[2])
			.data<&test_project::point::size, entt::as_ref_t>(ids[3])
			.data<&test_project::point::children, entt::as_ref_t>(ids[4])
			.type(entt::type_hash<test_project::point>::value()); 

		auto tree_generator_factory = entt::meta<test_project::tree_generator>()
			.data<&test_project::tree_generator::direction, entt::as_ref_t>(ids[5])
			.data<&test_project::tree_generator::starting_size, entt::as_ref_t>(ids[6])
			.data<&test_project::tree_generator::random_seed, entt::as_ref_t>(ids[7])
			.data<&test_project::tree_generator::trunk_section_length, entt::as_ref_t>(ids[8])
			.data<&test_project::tree_generator::trunk_section_length_variation, entt::as_ref_t>(ids[9])
			.data<&test_project::tree_generator::trunk_split_chance, entt::as_ref_t>(ids[10])
			.data<&test_project::tree_generator::trunk_segment_count, entt::as_ref_t>(ids[11])
			.data<&test_project::tree_generator::trunk_segment_count_variation, entt::as_ref_t>(ids[12])
			.data<&test_project::tree_generator::branch_section_length, entt::as_ref_t>(ids[13])
			.data<&test_project::tree_generator::branch_section_length_variation, entt::as_ref_t>(ids[14])
			.data<&test_project::tree_generator::branch_direction_variation, entt::as_ref_t>(ids[15])
			.data<&test_project::tree_generator::branch_split_chance, entt::as_ref_t>(ids[16])
			.data<&test_project::tree_generator::branch_segment_count, entt::as_ref_t>(ids[17])
			.data<&test_project::tree_generator::branch_segment_count_variation, entt::as_ref_t>(ids[18])
			.type(entt::type_hash<test_project::tree_generator>::value()); 

	}

	bool display_properties(test_project::point* script) {

		// class specifiers [rebuild_on_property_change]
		bool changed = false;
		if (UI::begin_collapsing_header_section("data")) {
			UI::begin_table("entity_component", false);
			changed |= UI::table_row("position##test_project::point::position", script->position);
			changed |= UI::table_row("direction##test_project::point::direction", script->direction);
			changed |= UI::table_row("length##test_project::point::length", script->length);
			changed |= UI::table_row("size##test_project::point::size", script->size);
			changed |= UI::table_row("children##test_project::point::children", script->children);
			UI::end_table();
		}
		UI::end_collapsing_header_section();

		return changed;
	}

	bool display_properties(test_project::tree_generator* script) {

		// class specifiers [rebuild_on_property_change]
		bool changed = false;
		if (UI::begin_collapsing_header_section("data")) {
			UI::begin_table("entity_component", false);
			changed |= UI::table_row("direction##test_project::tree_generator::direction", script->direction, static_cast<f32>(0.01f), static_cast<glm::vec3>(0.f), static_cast<glm::vec3>(1.f));
			changed |= UI::table_row("starting size##test_project::tree_generator::starting_size", script->starting_size, static_cast<f32>(0.01f), static_cast<f32>(0.f), static_cast<f32>(1.f));
			changed |= UI::table_row("random seed##test_project::tree_generator::random_seed", script->random_seed, static_cast<f32>(1), static_cast<u32>(0), static_cast<u32>(6854521));
			UI::end_table();
		}
		UI::end_collapsing_header_section();

		if (UI::begin_collapsing_header_section("trunk")) {
			UI::begin_table("entity_component", false);
			changed |= UI::table_row("section length##test_project::tree_generator::trunk_section_length", script->trunk_section_length, static_cast<f32>(5), static_cast<f32>(10.f), static_cast<f32>(300.f));
			changed |= UI::table_row("section length variation##test_project::tree_generator::trunk_section_length_variation", script->trunk_section_length_variation, static_cast<f32>(0.1f), static_cast<f32>(1.f), static_cast<f32>(100.f));
			changed |= UI::table_row("split chance##test_project::tree_generator::trunk_split_chance", script->trunk_split_chance, static_cast<f32>(0.01f), static_cast<f32>(0.f), static_cast<f32>(1.f));
			changed |= UI::table_row("segment count##test_project::tree_generator::trunk_segment_count", script->trunk_segment_count, static_cast<f32>(0.01f), static_cast<u32>(0), static_cast<u32>(10));
			changed |= UI::table_row("segment count variation##test_project::tree_generator::trunk_segment_count_variation", script->trunk_segment_count_variation, static_cast<f32>(1), static_cast<u32>(0), static_cast<u32>(10));
			UI::end_table();
		}
		UI::end_collapsing_header_section();

		if (UI::begin_collapsing_header_section("branch")) {
			UI::begin_table("entity_component", false);
			changed |= UI::table_row("section length##test_project::tree_generator::branch_section_length", script->branch_section_length, static_cast<f32>(1), static_cast<f32>(1.f), static_cast<f32>(150.f));
			changed |= UI::table_row("section length variation##test_project::tree_generator::branch_section_length_variation", script->branch_section_length_variation, static_cast<f32>(0.02f), static_cast<f32>(0.f), static_cast<f32>(5.f));
			changed |= UI::table_row("direction variation##test_project::tree_generator::branch_direction_variation", script->branch_direction_variation, static_cast<f32>(0.02f), static_cast<f32>(0.f), static_cast<f32>(5.f));
			changed |= UI::table_row("split chance##test_project::tree_generator::branch_split_chance", script->branch_split_chance, static_cast<f32>(0.01f), static_cast<f32>(0.f), static_cast<f32>(1.f));
			changed |= UI::table_row("segment count##test_project::tree_generator::branch_segment_count", script->branch_segment_count, static_cast<f32>(1), static_cast<u32>(0), static_cast<u32>(10));
			changed |= UI::table_row("segment count variation##test_project::tree_generator::branch_segment_count_variation", script->branch_segment_count_variation, static_cast<f32>(1), static_cast<u32>(0), static_cast<u32>(10));
			UI::end_table();
		}
		UI::end_collapsing_header_section();

		if (changed)
			script->on_rebuild();
		return changed;
	}

	void serialize_script(test_project::point* script, serializer::yaml& serializer) {

		// specifiers [rebuild_on_property_change]
		serializer.sub_section("data", [&](serializer::yaml& data_section) {

			data_section.entry(KEY_VALUE(script->position))
				.entry(KEY_VALUE(script->direction))
				.entry(KEY_VALUE(script->length))
				.entry(KEY_VALUE(script->size))
				.vector("children", script->children, [&](serializer::yaml& children_section, u64 x) {			// std::vector<point*> | point

					serialize_script(script->children[x], serializer);
				});
		});
	}

	void serialize_script(test_project::tree_generator* script, serializer::yaml& serializer) {

		// specifiers [rebuild_on_property_change]
		serializer.sub_section("data", [&](serializer::yaml& data_section) {

			data_section.entry(KEY_VALUE(script->direction))
				.entry(KEY_VALUE(script->starting_size))
				.entry(KEY_VALUE(script->random_seed));
		});
		serializer.sub_section("trunk", [&](serializer::yaml& trunk_section) {

			trunk_section.entry(KEY_VALUE(script->trunk_section_length))
				.entry(KEY_VALUE(script->trunk_section_length_variation))
				.entry(KEY_VALUE(script->trunk_split_chance))
				.entry(KEY_VALUE(script->trunk_segment_count))
				.entry(KEY_VALUE(script->trunk_segment_count_variation));
		});
		serializer.sub_section("branch", [&](serializer::yaml& branch_section) {

			branch_section.entry(KEY_VALUE(script->branch_section_length))
				.entry(KEY_VALUE(script->branch_section_length_variation))
				.entry(KEY_VALUE(script->branch_direction_variation))
				.entry(KEY_VALUE(script->branch_split_chance))
				.entry(KEY_VALUE(script->branch_segment_count))
				.entry(KEY_VALUE(script->branch_segment_count_variation));
		});
	}

	void delete_scripts(entt::registry& registry) {

		registry.clear<test_project::tree_generator>();
	}

	void add_component(std::string class_name, PFF::entity entity) {

		if(class_name == "test_project::tree_generator")
			entity.add_procedural_mesh_component<test_project::tree_generator>("test_project::tree_generator");
	}

}
