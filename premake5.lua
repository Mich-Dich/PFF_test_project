include "C:/CustomGameEngine/PFF/dependencies.lua"

workspace "PFF_project"
	architecture "x64"
	configurations { "Debug", "Release" }
	flags { "MultiProcessorCompile" }
	startproject "test_project"

	project "test_project"
		location "metadata/project_files"					--Set the location for workspace(solution) files
		kind "SharedLib"
		language "C++"
		cppdialect "C++17"
		staticruntime "off"

	targetdir("bin/%{prj.name}_build_DLL")
	objdir("bin-int/%{prj.name}")

	--------------------------------------TODO: make PCH an option in the editor--------------------------------------
	--pchheader "pch.h"
	--pchsource "src/pch.cpp"

	files
	{
		"generated/**.h",
		"generated/**.hpp",
		"generated/**.cpp",
		"src/**.h",
		"src/**.hpp",
		"src/**.cpp",
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
	debugcommand("C:/CustomGameEngine/PFF/bin/Debug-windows-x86_64/PFF_editor/PFF_editor.exe")
	debugdir("C:/CustomGameEngine/PFF/bin/Debug-windows-x86_64/PFF_editor")
	-- If you need to pass arguments to your game engine, use:								debugargs { "arg1", "arg2" }

	libdirs 
	{
		"C:/CustomGameEngine/PFF/bin/Debug-windows-x86_64/PFF",
		"C:/CustomGameEngine/PFF/bin/Debug-windows-x86_64/vendor/imgui",
	}

	links
	{
		"PFF",
		"ImGui"
	}

	defines "PFF_PROJECT"

    prebuildcommands {
		"cd C:/CustomGameEngine/PFF/bin/Debug-windows-x86_64/PFF && " ..
		"C:/CustomGameEngine/PFF/bin/Debug-windows-x86_64/PFF_helper/PFF_helper.exe 0 0 0 C:/CustomGameEngine/PFF_projects/test_project",
    }

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
