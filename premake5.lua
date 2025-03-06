
PFF_source_location = "/home/mich/workspace/PFF/"

include (PFF_source_location .. "/dependencies.lua")
include (PFF_source_location .. "/premake5.lua")

PFF_engine_location = PFF_source_location .. "/bin/" .. outputs

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
        PFF_source_location .. "/PFF/src",
        PFF_source_location .. "/%{vendor_path.entt}",
        PFF_source_location .. "/%{vendor_path.glm}",
        PFF_source_location .. "/%{vendor_path.ImGui}",
		"%{IncludeDir.Vulkan}",
		"%{IncludeDir.VulkanUtils}",
    }

    symbolspath '$(OutDir)$(TargetName)-$([System.DateTime]::Now.ToString("HH_mm_ss_fff")).pdb'
    debugcommand(PFF_engine_location .. "/PFF_editor/PFF_editor.exe")
    debugdir(PFF_engine_location .. "/PFF_editor")
    -- For passing arguments to game engine, use: debugargs { "arg1", "arg2" }

    libdirs 
    {
		PFF_engine_location.. "/PFF",
        PFF_engine_location .. "/vendor/imgui",
    }

    links
    {
        "PFF",
        "ImGui"
    }

    defines "PFF_PROJECT"

	cleancommands{
		"{RMDIR} %{cfg.buildtarget.directory}",
		"{RMDIR} %{cfg.objdir}",
		"{RMDIR} generated",
		"echo Cleaning completed for %{prj.name}"
	}

	filter { "system:windows" }
		defines "PFF_PLATFORM_WINDOWS"
		
		prebuildcommands {
			"cd " .. PFF_engine_location .. "/PFF",
			PFF_engine_location .. "/PFF_helper/PFF_helper.exe 0 0 0 /home/mich/workspace/PFF_test_projects",
		}

		rebuildcommands{
			"{RMDIR} %{cfg.buildtarget.directory}",
			"{RMDIR} %{cfg.objdir}",
			"premake5 --file=%{wks.location}premake5.lua vs2019",
			"msbuild /t:rebuild /p:configuration=%{cfg.buildcfg} %{wks.location}%{prj.name}.vcxproj",
			"echo Rebuild completed for %{prj.name}"
		}

	filter { "system:linux" }
		defines "PFF_PLATFORM_LINUX"

		prebuildcommands {
			"cd " .. PFF_engine_location .. "/PFF",
			PFF_engine_location .. "/PFF_helper/PFF_helper 0 0 0 /home/mich/workspace/PFF_test_projects",
			"cd -"
		}
		
		rebuildcommands{
			"{RMDIR} %{cfg.buildtarget.directory}",
			"{RMDIR} %{cfg.objdir}",
			PFF_engine_location .. "/vendor/premake5/premake5 gmake2",
			"make -j",
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
