include "/home/mich/workspace/PFF/bin/Debug-linux-x86_64/dependencies.lua"

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
		"/home/mich/workspace/PFF/bin/Debug-linux-x86_64/PFF/src",
		"/home/mich/workspace/PFF/bin/Debug-linux-x86_64/vendor/entt",
		"/home/mich/workspace/PFF/bin/Debug-linux-x86_64/vendor/glm",
		"/home/mich/workspace/PFF/bin/Debug-linux-x86_64/vendor/imgui",
		"%{IncludeDir.Vulkan}",
	}

	symbolspath '$(OutDir)$(TargetName)-$([System.DateTime]::Now.ToString("HH_mm_ss_fff")).pdb'
	debugcommand("/home/mich/workspace/PFF/bin/Debug-linux-x86_64/PFF_editor/PFF_editor.exe")
	debugdir("/home/mich/workspace/PFF/bin/Debug-linux-x86_64/PFF_editor")
	-- for passing arguments to game engine, use:								debugargs { "arg1", "arg2" }

	libdirs 
	{
		"/home/mich/workspace/PFF/bin/Debug-linux-x86_64/PFF",
		"/home/mich/workspace/PFF/bin/Debug-linux-x86_64/vendor/imgui",
		"/home/mich/workspace/PFF/bin/Debug-linux-x86_64/vendor/glfw",
	}

	links
	{
		"PFF",
		"ImGui",
		"GLFW"
	}

	defines "PFF_PROJECT"

    prebuildcommands {
		"cd /home/mich/workspace/PFF/bin/Debug-linux-x86_64/PFF && " ..
		"/home/mich/workspace/PFF/bin/Debug-linux-x86_64/PFF_helper/PFF_helper.exe 0 0 0 /home/mich/workspace/PFF_test_projects",
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
