workspace "Komet"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Komet/vendor/GLFW/include"
IncludeDir["Glad"] = "Komet/vendor/Glad/include"
IncludeDir["ImGui"] = "Komet/vendor/imgui"
IncludeDir["glm"] = "Komet/vendor/glm"

group "Dependencies"
	include "Komet/vendor/GLFW"
	include "Komet/vendor/Glad"
	include "Komet/vendor/imgui"


group""

project "Komet"
	location "Komet"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "kmpch.h"
	pchsource "Komet/src/kmpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",

	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"

	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
		"dwmapi.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"KM_PLATFORM_WINDOWS",
			"KM_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		buildoptions { "/utf-8" }


	filter "configurations:Debug"
		defines "KM_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "KM_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "KM_DIST"
		runtime "Release"
		optimize "on"



project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Komet/vendor/spdlog/include",
		"Komet/src",
		"Komet/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Komet"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"KM_PLATFORM_WINDOWS"			
		}

		buildoptions { "/utf-8" }


	filter "configurations:Debug"
		defines "KM_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "KM_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "KM_DIST"
		runtime "Release"
		optimize "on"
		