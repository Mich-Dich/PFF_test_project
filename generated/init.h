#pragma once
#include <PFF.h>

#define ENTT_STANDARD_CPP
#include <entt.hpp>

extern "C" namespace PFF {
	extern "C" namespace Init {

		static void InitComponentIds(SceneData & scene)
		{
		}
		extern "C" PFF_SCRIPT void AddComponent(entt::registry& registryRef, std::string className, entt::entity entity)
		{
			Log::Assert(registryRef.valid(entity), "Invalid entity in script");
		}

		extern "C" PFF_SCRIPT void UpdateScripts(entt::registry& registryRef, float dt)
		{
		}

		extern "C" PFF_SCRIPT void EditorUpdateScripts(entt::registry& registryRef, float dt)
		{
		}

		extern "C" PFF_SCRIPT void NotifyBeginContact(Entity a, Entity b)
		{
		}

		extern "C" PFF_SCRIPT void NotifyEndContact(Entity a, Entity b)
		{
		}

		extern "C" PFF_SCRIPT void SaveScripts(entt::registry& registryRef, json& j, SceneData* sceneData)
		{
			Log::Info("Saving scripts");
		}

		extern "C" PFF_SCRIPT void LoadScript(entt::registry& registryRef, const json& j, Entity entity)
		{
		}

		extern "C" PFF_SCRIPT void InitScripts(SceneData* sceneData)
		{
			Log::Info("Initializing scripts");
			InitComponentIds(*sceneData);
		}

		extern "C" PFF_SCRIPT void InitImGui(void* ctx)
		{
			Log::Info("Initializing ImGui");
			ImGui::SetCurrentContext((ImGuiContext*)ctx);
		}

		extern "C" PFF_SCRIPT void ImGui(entt::registry& registryRef, Entity entity)
		{
		}

		extern "C" PFF_SCRIPT void DeleteScripts()
		{
			Log::Info("Deleting Scripts");
		}
	}
}
