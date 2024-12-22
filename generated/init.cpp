
#include "init.h"

#define PFF_ADD_COMPONENT_GENERATED_MACRO(name)					for (auto str_class : reflect_##name::string_to_map) {					\
																	if (str_class.first != class_name) continue;						\
																	reflect_##name::add_component(class_name, entity);					\
																	return;}

#define PFF_DISPLAY_PROPERTIE_GENERATED_MACRO(name, cast)		for (auto str_class : reflect_##name::string_to_map) {					\
																	if (str_class.first != class_name) continue;						\
																	reflect_##name::display_properties((##cast*) script);				\
																	return;}

#define PFF_SERIALIZE_SCRIPT_GENERATED_MACRO(name, cast)		for (auto str_class : reflect_##name::string_to_map) {					\
																	if (str_class.first != class_name) continue;						\
																	reflect_##name::serialize_script((cast*) script, serializer);		\
																	return;}

extern "C" namespace PFF::init {

	void init_scripts(entt::registry* registry) {

		LOG(Info, "PROJECT - initializing scripts");


		ImGui::SetCurrentContext(application::get().get_imgui_layer()->get_context());

		LOG(Info, "PROJECT - successfully initalized scripts");
	}

	void add_component(std::string class_name, PFF::entity entity) {

		VALIDATE(entity.is_valid(), return, "", "Invalid entity in script");

	}

	void display_properties(std::string class_name, entity_script* script) {

		if (!script) {
			ImGui::Text("Script pointer is null");
			return;
		}

	}

	void serialize_script(std::string class_name, entity_script* script, serializer::yaml& serializer) {

	}

}
