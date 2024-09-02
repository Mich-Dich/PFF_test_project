include "C:/CustomGameEngine/PFF/dependencies.lua"

workspace "PFF_project"
	architecture "x64"
	configurations { "Debug", "Release" }
	flags { "MultiProcessorCompile" }
	startproject "test_project"

	project "test_project"
		kind "SharedLib"
		language "C++"
		cppdialect "C++17"
		staticruntime "off"

	targetdir("bin/%{prj.name}")
	objdir("bin-int/%{prj.name}")

	--------------------------------------TODO: make PCH an option in the editor--------------------------------------
	--pchheader "pch.h"
	--pchsource "src/pch.cpp"

	files
	{
		"**.h",
		"**.hpp",
		"**.cpp",
	}

	includedirs
	{
		"content",
		"src",
		"C:/CustomGameEngine/PFF/PFF/src",
		"C:/CustomGameEngine/PFF/%{vendor_path.entt}",
		"C:/CustomGameEngine/PFF/%{vendor_path.glm}",
		"C:/CustomGameEngine/PFF/%{vendor_path.ImGui}",
		"C:/VulkanSDK/1.3.250.1/Include",
	}

	symbolspath '$(OutDir)$(TargetName)-$([System.DateTime]::Now.ToString("HH_mm_ss_fff")).pdb'

	libdirs 
	{
		"C:/CustomGameEngine/PFF/bin/Debug-windows-x86_64/PFF",
		"C:/CustomGameEngine/PFF/bin/Debug-windows-x86_64/imgui",
	}

	links
	{
		"PFF"
	}

	defines "PFF_PROJECT"

	filter "system:windows"
		defines "PFF_PLATFORM_WINDOWS"
		systemversion "latest"
		buildcommands { "del /S *.pdb" }

	filter "configurations:Debug"
		defines "PROJECT_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PROJECT_RELEASE"
		runtime "Release"
		optimize "on"
