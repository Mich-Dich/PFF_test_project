#pragma once

#include <PFF.h>
#define ENTT_STANDARD_CPP
#include <entt/entt.hpp>


#define RETURN_CHAR_ARRAY(array_name) 				if (count != nullptr) *count = sizeof(array_name) / sizeof(array_name[0]) - 1;		\
														return array_name;

extern "C" namespace PFF::init {

	static const char* procedural_mesh_scripts[] = {
		nullptr
	};

	static const char* scripts[] = {
		nullptr
	};


	PROJECT_API void init_scripts(entt::registry* registry);

	PROJECT_API void add_component(std::string class_name, PFF::entity entity);

	PROJECT_API void display_properties(std::string class_name, entity_script* script);

	PROJECT_API void serialize_script(std::string class_name, entity_script* script, serializer::yaml& serializer);

	PROJECT_API const char** get_all_procedural_mesh_scripts(u32* count) { RETURN_CHAR_ARRAY(procedural_mesh_scripts); }

	PROJECT_API const char** get_all_scripts(u32 * count) { RETURN_CHAR_ARRAY(scripts); }

}
