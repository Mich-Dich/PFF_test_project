include "C:/dev/PFF/bin/Debug-windows-x86_64/dependencies.lua"

workspace "test_project"
architecture "x64"
	configurations { "Debug", "Release" }
	flags { "MultiProcessorCompile" }
	startproject "test_project"

	project "test_project"
		location "metadata/project_files"					--Set the location for workspace(solution) files
		kind "SharedLib"
		language "C++"
		cppdialect "C++20"
		staticruntime "on"

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
		"C:/dev/PFF/bin/Debug-windows-x86_64/PFF/src",
		"C:/dev/PFF/bin/Debug-windows-x86_64/vendor/entt",
		"C:/dev/PFF/bin/Debug-windows-x86_64/vendor/glm",
		"C:/dev/PFF/bin/Debug-windows-x86_64/vendor/imgui",
		"%{IncludeDir.Vulkan}",
	}

	symbolspath '$(OutDir)$(TargetName)-$([System.DateTime]::Now.ToString("HH_mm_ss_fff")).pdb'
	debugcommand("C:/dev/PFF/bin/Debug-windows-x86_64/PFF_editor/PFF_editor.exe")
	debugdir("C:/dev/PFF/bin/Debug-windows-x86_64/PFF_editor")
	-- for passing arguments to game engine, use:								debugargs { "arg1", "arg2" }

	libdirs 
	{
		"C:/dev/PFF/bin/Debug-windows-x86_64/PFF",
		"C:/dev/PFF/bin/Debug-windows-x86_64/vendor/imgui",
		"C:/dev/PFF/bin/Debug-windows-x86_64/vendor/glfw",
	}

	links
	{
		"PFF",
		"ImGui",
		"GLFW"
	}

	defines "PFF_PROJECT"

    prebuildcommands {
		"cd C:/dev/PFF/bin/Debug-windows-x86_64/PFF && " ..
		"C:/dev/PFF/bin/Debug-windows-x86_64/PFF_helper/PFF_helper.exe 0 0 0 C:/dev/PFF_test_project",
    }

	cleancommands{
		"{RMDIR} %{cfg.buildtarget.directory}",
		"{RMDIR} %{cfg.objdir}",
		"{RMDIR} generated",
		"echo Cleaning completed for %{prj.name}"
	}

	rebuildcommands{
		"{RMDIR} %{cfg.buildtarget.directory}",
		"{RMDIR} %{cfg.objdir}",
		"premake5 --file=%{wks.location}premake5.lua vs2019",
		"msbuild /t:rebuild /p:configuration=%{cfg.buildcfg} %{wks.location}%{prj.name}.vcxproj",
		"echo Rebuild completed for %{prj.name}"
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
