#pragma once

#include <PFF.h>
#define ENTT_STANDARD_CPP
#include <entt/entt.hpp>

#include "procedural_meshes/simple_terrain_script.h"
#include "procedural_meshes/simple_terrain_script-generated.h"
#include "test_script.h"
#include "test_script-generated.h"

extern "C" namespace PFF::init {

	static void init_component_ids(entt::registry* registry) {

		registry->storage<simple_terrain_script>();
		registry->storage<DefaultScript>();
	}

	PROJECT_API void add_component(std::string className, PFF::entity entity) {

		ASSERT(entity.is_valid(), "", "Invalid entity in script");
		for (auto strClass : reflect_simple_terrain_script_h::string_to_map) {

			if (strClass.first != className) 
				continue;

			reflect_simple_terrain_script_h::add_component(className, entity);
			return;
		}
		for (auto strClass : reflect_test_script_h::string_to_map) {

			if (strClass.first != className) 
				continue;

			reflect_test_script_h::add_component(className, entity);
			return;
		}
	}

	PROJECT_API void init_scripts(entt::registry* registry) {

		LOG(Info, "Initializing scripts");
		init_component_ids(registry);
		reflect_simple_terrain_script_h::init();
		reflect_test_script_h::init();
	}
}
