
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
		"test_project::section_settings::section_default_length"_hs,
		"test_project::section_settings::section_length_variation"_hs,
		"test_project::section_settings::direction_variation"_hs,
		"test_project::section_settings::split_chance"_hs,
		"test_project::section_settings::starting_direction"_hs,
		"test_project::section_settings::grow_direction"_hs,
		"test_project::section_settings::direction_change_speed"_hs,
		"test_project::tree_generator::starting_direction"_hs,
		"test_project::tree_generator::grow_direction"_hs,
		"test_project::tree_generator::grow_direction_start_point"_hs,
		"test_project::tree_generator::starting_size"_hs,
		"test_project::tree_generator::random_seed"_hs,
		"test_project::tree_generator::trunk_section_settings"_hs,
		"test_project::tree_generator::trunk_segment_count"_hs,
		"test_project::tree_generator::trunk_segment_count_variation"_hs,
		"test_project::tree_generator::trunk_repulsion_strength"_hs,
		"test_project::tree_generator::trunk_repulsion_influence"_hs,
		"test_project::tree_generator::trunk_influence_of_repulsion_on_grow_direction"_hs,
		"test_project::tree_generator::branch_section_settings"_hs,
		"test_project::tree_generator::branch_spawn_chance"_hs,
		"test_project::tree_generator::branch_spawn_height"_hs,
		"test_project::tree_generator::branch_split_chance"_hs,
		"test_project::tree_generator::branch_start_angle_to_trunk"_hs,
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
		{ entt::type_hash<test_project::section_settings>::value(), "test_project::section_settings"},
		{ids[5], "section_default_length"},
		{ids[6], "section_length_variation"},
		{ids[7], "direction_variation"},
		{ids[8], "split_chance"},
		{ids[9], "starting_direction"},
		{ids[10], "grow_direction"},
		{ids[11], "direction_change_speed"},
		{ entt::type_hash<test_project::tree_generator>::value(), "test_project::tree_generator"},
		{ids[12], "starting_direction"},
		{ids[13], "grow_direction"},
		{ids[14], "grow_direction_start_point"},
		{ids[15], "starting_size"},
		{ids[16], "random_seed"},
		{ids[17], "trunk_section_settings"},
		{ids[18], "trunk_segment_count"},
		{ids[19], "trunk_segment_count_variation"},
		{ids[20], "trunk_repulsion_strength"},
		{ids[21], "trunk_repulsion_influence"},
		{ids[22], "trunk_influence_of_repulsion_on_grow_direction"},
		{ids[23], "branch_section_settings"},
		{ids[24], "branch_spawn_chance"},
		{ids[25], "branch_spawn_height"},
		{ids[26], "branch_split_chance"},
		{ids[27], "branch_start_angle_to_trunk"},
		{ids[28], "branch_segment_count"},
		{ids[29], "branch_segment_count_variation"}
	};

	std::map<std::string, entt::id_type> string_to_map = {

		{ "test_project::point", entt::type_hash<test_project::point>::value() },
		{ "test_project::section_settings", entt::type_hash<test_project::section_settings>::value() },
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

		auto section_settings_factory = entt::meta<test_project::section_settings>()
			.data<&test_project::section_settings::section_default_length, entt::as_ref_t>(ids[5])
			.data<&test_project::section_settings::section_length_variation, entt::as_ref_t>(ids[6])
			.data<&test_project::section_settings::direction_variation, entt::as_ref_t>(ids[7])
			.data<&test_project::section_settings::split_chance, entt::as_ref_t>(ids[8])
			.data<&test_project::section_settings::starting_direction, entt::as_ref_t>(ids[9])
			.data<&test_project::section_settings::grow_direction, entt::as_ref_t>(ids[10])
			.data<&test_project::section_settings::direction_change_speed, entt::as_ref_t>(ids[11])
			.type(entt::type_hash<test_project::section_settings>::value()); 

		auto tree_generator_factory = entt::meta<test_project::tree_generator>()
			.data<&test_project::tree_generator::starting_direction, entt::as_ref_t>(ids[12])
			.data<&test_project::tree_generator::grow_direction, entt::as_ref_t>(ids[13])
			.data<&test_project::tree_generator::grow_direction_start_point, entt::as_ref_t>(ids[14])
			.data<&test_project::tree_generator::starting_size, entt::as_ref_t>(ids[15])
			.data<&test_project::tree_generator::random_seed, entt::as_ref_t>(ids[16])
			.data<&test_project::tree_generator::trunk_section_settings, entt::as_ref_t>(ids[17])
			.data<&test_project::tree_generator::trunk_segment_count, entt::as_ref_t>(ids[18])
			.data<&test_project::tree_generator::trunk_segment_count_variation, entt::as_ref_t>(ids[19])
			.data<&test_project::tree_generator::trunk_repulsion_strength, entt::as_ref_t>(ids[20])
			.data<&test_project::tree_generator::trunk_repulsion_influence, entt::as_ref_t>(ids[21])
			.data<&test_project::tree_generator::trunk_influence_of_repulsion_on_grow_direction, entt::as_ref_t>(ids[22])
			.data<&test_project::tree_generator::branch_section_settings, entt::as_ref_t>(ids[23])
			.data<&test_project::tree_generator::branch_spawn_chance, entt::as_ref_t>(ids[24])
			.data<&test_project::tree_generator::branch_spawn_height, entt::as_ref_t>(ids[25])
			.data<&test_project::tree_generator::branch_split_chance, entt::as_ref_t>(ids[26])
			.data<&test_project::tree_generator::branch_start_angle_to_trunk, entt::as_ref_t>(ids[27])
			.data<&test_project::tree_generator::branch_segment_count, entt::as_ref_t>(ids[28])
			.data<&test_project::tree_generator::branch_segment_count_variation, entt::as_ref_t>(ids[29])
			.type(entt::type_hash<test_project::tree_generator>::value()); 

	}

	bool display_properties(test_project::point* script) {

		// class specifiers [rebuild_on_property_change]
		bool changed = false;
		if (UI::begin_collapsing_header_section("data")) {
			UI::begin_table("entity_component", false);
			changed |= UI::table_row("position##test_project::point::position", script->position); // type: glm::vec3 
			changed |= UI::table_row("direction##test_project::point::direction", script->direction); // type: glm::vec3 
			changed |= UI::table_row("length##test_project::point::length", script->length); // type: f32 
			changed |= UI::table_row("size##test_project::point::size", script->size); // type: f32 
			changed |= UI::table_row("children##test_project::point::children", script->children); // type: std::vector<point*> 
			UI::end_table();
		}
		UI::end_collapsing_header_section();

		return changed;
	}

	bool display_properties(test_project::section_settings* script) {

		// class specifiers [rebuild_on_property_change]
		bool changed = false;
		if (UI::begin_collapsing_header_section("data")) {
			UI::begin_table("entity_component", false);
			changed |= UI::table_row("section default length##test_project::section_settings::section_default_length", script->section_default_length, static_cast<f32>(0.1f), static_cast<f32>(0.1f), static_cast<f32>(15.f));
			changed |= UI::table_row("section length variation##test_project::section_settings::section_length_variation", script->section_length_variation, static_cast<f32>(0.02f), static_cast<f32>(0.f), static_cast<f32>(1.f));
			changed |= UI::table_row("direction variation##test_project::section_settings::direction_variation", script->direction_variation, static_cast<f32>(0.02f), static_cast<f32>(0.f), static_cast<f32>(60.f));
			changed |= UI::table_row("split chance##test_project::section_settings::split_chance", script->split_chance, static_cast<f32>(0.001f), static_cast<f32>(0.f), static_cast<f32>(1.f));
			changed |= UI::table_row("starting direction##test_project::section_settings::starting_direction", script->starting_direction, static_cast<f32>(0.01f), static_cast<glm::vec3>(1.f), static_cast<glm::vec3>(1.f));
			changed |= UI::table_row("grow direction##test_project::section_settings::grow_direction", script->grow_direction, static_cast<f32>(0.01f), static_cast<glm::vec3>(1.f), static_cast<glm::vec3>(1.f));
			changed |= UI::table_row("direction change speed##test_project::section_settings::direction_change_speed", script->direction_change_speed, static_cast<f32>(0.01f), static_cast<f32>(0.f), static_cast<f32>(10.f));
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
			changed |= UI::table_row("starting direction##test_project::tree_generator::starting_direction", script->starting_direction, static_cast<f32>(0.01f), static_cast<glm::vec3>(0.f), static_cast<glm::vec3>(1.f));
			changed |= UI::table_row("grow direction##test_project::tree_generator::grow_direction", script->grow_direction, static_cast<f32>(0.01f), static_cast<glm::vec3>(0.f), static_cast<glm::vec3>(1.f));
			changed |= UI::table_row("grow direction start point##test_project::tree_generator::grow_direction_start_point", script->grow_direction_start_point, static_cast<f32>(0.01f), static_cast<f32>(0.f), static_cast<f32>(1.f));
			changed |= UI::table_row("starting size##test_project::tree_generator::starting_size", script->starting_size, static_cast<f32>(0.01f), static_cast<f32>(0.f), static_cast<f32>(1.f));
			changed |= UI::table_row("random seed##test_project::tree_generator::random_seed", script->random_seed, static_cast<f32>(1), static_cast<int32>(1), static_cast<int32>(6854521));
			UI::end_table();
		}
		UI::end_collapsing_header_section();

		if (UI::begin_collapsing_header_section("trunk")) {
			UI::begin_table("entity_component", false);
			UI::end_table();
			changed |= display_properties(&script->trunk_section_settings);
			UI::begin_table("entity_component", false);
			changed |= UI::table_row("segment count##test_project::tree_generator::trunk_segment_count", script->trunk_segment_count, static_cast<f32>(0.01f), static_cast<u32>(0), static_cast<u32>(50));
			changed |= UI::table_row("segment count variation##test_project::tree_generator::trunk_segment_count_variation", script->trunk_segment_count_variation, static_cast<f32>(1), static_cast<u32>(0), static_cast<u32>(30));
			changed |= UI::table_row("repulsion strength##test_project::tree_generator::trunk_repulsion_strength", script->trunk_repulsion_strength, static_cast<f32>(0.01f), static_cast<f32>(0.f), static_cast<f32>(1.f));
			changed |= UI::table_row("repulsion influence##test_project::tree_generator::trunk_repulsion_influence", script->trunk_repulsion_influence, static_cast<f32>(0.1f), static_cast<f32>(0.f), static_cast<f32>(10.f));
			changed |= UI::table_row("influence of repulsion on grow direction##test_project::tree_generator::trunk_influence_of_repulsion_on_grow_direction", script->trunk_influence_of_repulsion_on_grow_direction, static_cast<f32>(0.05f), static_cast<f32>(0.f), static_cast<f32>(30.f));
			UI::end_table();
		}
		UI::end_collapsing_header_section();

		if (UI::begin_collapsing_header_section("branch")) {
			UI::begin_table("entity_component", false);
			UI::end_table();
			changed |= display_properties(&script->branch_section_settings);
			UI::begin_table("entity_component", false);
			changed |= UI::table_row("spawn chance##test_project::tree_generator::branch_spawn_chance", script->branch_spawn_chance, static_cast<f32>(0.01f), static_cast<f32>(0.f), static_cast<f32>(1.0f));
			changed |= UI::table_row("spawn height##test_project::tree_generator::branch_spawn_height", script->branch_spawn_height, static_cast<f32>(0.01f), static_cast<f32>(0.f), static_cast<f32>(1.f));
			changed |= UI::table_row("split chance##test_project::tree_generator::branch_split_chance", script->branch_split_chance, static_cast<f32>(0.01f), static_cast<f32>(0.f), static_cast<f32>(1.f));
			changed |= UI::table_row("start angle to trunk##test_project::tree_generator::branch_start_angle_to_trunk", script->branch_start_angle_to_trunk, static_cast<f32>(1), static_cast<u32>(0), static_cast<u32>(180));
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

	void serialize_script(test_project::section_settings* script, serializer::yaml& serializer) {

		// specifiers [rebuild_on_property_change]
		serializer.sub_section("data", [&](serializer::yaml& data_section) {

			data_section.entry(KEY_VALUE(script->section_default_length))
				.entry(KEY_VALUE(script->section_length_variation))
				.entry(KEY_VALUE(script->direction_variation))
				.entry(KEY_VALUE(script->split_chance))
				.entry(KEY_VALUE(script->starting_direction))
				.entry(KEY_VALUE(script->grow_direction))
				.entry(KEY_VALUE(script->direction_change_speed));
		});
	}

	void serialize_script(test_project::tree_generator* script, serializer::yaml& serializer) {

		// specifiers [rebuild_on_property_change]
		serializer.sub_section("data", [&](serializer::yaml& data_section) {

			data_section.entry(KEY_VALUE(script->starting_direction))
				.entry(KEY_VALUE(script->grow_direction))
				.entry(KEY_VALUE(script->grow_direction_start_point))
				.entry(KEY_VALUE(script->starting_size))
				.entry(KEY_VALUE(script->random_seed));
		});
		serializer.sub_section("trunk", [&](serializer::yaml& trunk_section) {

			serialize_script(&script->trunk_section_settings, serializer);
			trunk_section.entry(KEY_VALUE(script->trunk_segment_count))
				.entry(KEY_VALUE(script->trunk_segment_count_variation))
				.entry(KEY_VALUE(script->trunk_repulsion_strength))
				.entry(KEY_VALUE(script->trunk_repulsion_influence))
				.entry(KEY_VALUE(script->trunk_influence_of_repulsion_on_grow_direction));
		});
		serializer.sub_section("branch", [&](serializer::yaml& branch_section) {

			serialize_script(&script->branch_section_settings, serializer);
			branch_section.entry(KEY_VALUE(script->branch_spawn_chance))
				.entry(KEY_VALUE(script->branch_spawn_height))
				.entry(KEY_VALUE(script->branch_split_chance))
				.entry(KEY_VALUE(script->branch_start_angle_to_trunk))
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
