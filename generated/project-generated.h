#pragma once

#define ENTT_STANDARD_CPP
#include <entt/core/hashed_string.hpp>
#include <entt/core/type_info.hpp>
#include <entt/meta/factory.hpp>
#include <entt/meta/meta.hpp>
#include <entt/meta/resolve.hpp>

#include <imgui.h>
#include <map>

#include "../.h"

namespace PFF {
	namespace Reflect 
	{
		using namespace entt::literals;
		bool initialized = false;

		std::vector<entt::id_type> ids = {
		};

		std::map<entt::id_type, const char*> debugNames;
		std::map<std::string, entt::id_type> stringToMap;
		void init()
		{
			if (initialized) return;
			initialized = true;

		debugNames = 
		{ 
		};

		stringToMap = 
		{ 
		};

		}
		void add_component(std::string class_name, entt::entity entity, entt::registry& registry)
		{
		}

		void SaveScript(entt::meta_any any, json& j, Entity entity)
		{
			auto typeData = entt::resolve(any.type().id());
			
			int size = j["Components"].size();
			auto typeName = debugNames.find(any.type().id())->second;
			json compJson;
			compJson[typeName] = {};
			compJson[typeName]["Entity"] = NEntity::GetID(entity);

			for (auto data : typeData.data())
			{
				auto name = debugNames.find(data.id());
				auto type = debugNames.find(data.type().id());
				if (name == debugNames.end() && type == debugNames.end())
					continue;

				if (data.type().is_floating_point())
				{
					entt::meta_handle handle = entt::meta_handle(any);
					float val = data.get(handle).cast<float>();
					compJson[typeName][name->second] = val;
				}
				else if (data.type().is_integral())
				{
					entt::meta_handle handle = entt::meta_handle(any);
					int val = data.get(handle).cast<int>();
					compJson[typeName][name->second] = val;
				}
			}

			j["Components"][size] = compJson;
		}

		void SaveScripts(json& j, entt::registry& registry, SceneData* sceneData)
		{
		}

		void LoadScript(entt::meta_any any, entt::meta_handle handle, json& j)
		{
			auto typeData = entt::resolve(any.type().id());
			auto typeName = debugNames.find(any.type().id())->second;

			for (auto data : typeData.data())
			{
				auto name = debugNames.find(data.id());
				auto type = debugNames.find(data.type().id());
				if (name == debugNames.end() && type == debugNames.end())
					continue;

				if (data.type().is_floating_point())
				{
					if (j[typeName].contains(name->second))
						data.set<float>(handle, j[typeName][name->second]);
				}
				else if (data.type().is_integral())
				{
					if (j[typeName].contains(name->second))
						data.set<int>(handle, j[typeName][name->second]);
				}
			}
		}

		void TryLoad(json& j, Entity entity, entt::registry& registry)
		{
			json::iterator it = j.begin();
			entt::entity e = entity.Handle;
			if (!registry.valid(e))
			{
				Logger::Error("Invalid entity, entity does not exist.");
				return;
			}

		}

		void ImGuiAny(entt::meta_any any, entt::meta_handle handle)
		{
			auto typeData = entt::resolve(any.type().id());
			auto typeName = debugNames.find(any.type().id())->second;

			if (ImGui::CollapsingHeader(typeName))
			{
				CImGui::BeginCollapsingHeaderGroup();
				for (auto data : typeData.data())
				{
					auto name = debugNames.find(data.id());
					auto type = debugNames.find(data.type().id());
					if (name == debugNames.end() && type == debugNames.end())
						continue;

					if (data.type().is_floating_point())
					{
						float* val = (float*)data.get(handle).data();
						CImGui::UndoableDragFloat(name->second, *val);
					}
					else if (data.type().is_integral())
					{
						int* val = (int*)data.get(handle).data();
						CImGui::UndoableDragInt(name->second, *val);
					}
				}
				CImGui::EndCollapsingHeaderGroup();
			}
		}

		void ImGui(Entity entity, entt::registry& registry)
		{
			entt::entity e = entity.Handle;
			if (!registry.valid(e)) return;
		}
		void delete_scripts()
		{
		}

		int tabs = 0;
		void printTabs()
		{
			for (int i = 0; i < tabs; i++)
			{
				printf("\t");
			}
		}


		void debugPrintAny(entt::meta_any any)
		{
			auto typeData = entt::resolve(any.type().id());
		
			for (auto data : typeData.data())
			{
				tabs++;
				auto name = debugNames.find(data.id());
				auto type = debugNames.find(data.type().id());
				if (name == debugNames.end() && type == debugNames.end())
					continue;
		
				if (data.type().is_class())
				{
					printTabs();
					printf("%s<%s>\n", name->second, type->second);
					tabs++;
					entt::meta_handle handle = entt::meta_handle(any);
					entt::meta_any resolvedData = data.get(handle);
					debugPrintAny(resolvedData);
					tabs--;
				}
				else
				{
					if (data.type().is_floating_point())
					{
						printTabs();
						entt::meta_handle handle = entt::meta_handle(any);
						float val = data.get(handle).cast<float>();
						printf("%s<float>: %2.3f\n", name->second, val);
					}
		 			else if (data.type().is_integral())
					{
						printTabs();
						entt::meta_handle handle = entt::meta_handle(any);
						int val = data.get(handle).cast<int>();
						printf("%s<int>: %d\n", name->second, val);
					}
				}
				tabs--;
			}
		}
		template<typename T>
		void debugPrint(const T& obj)
		{
			entt::meta_any any = entt::meta_any{ obj };
			debug_print_any(any);
		}
	}
}
