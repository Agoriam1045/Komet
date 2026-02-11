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
IncludeDir["stbi"] = "Komet/vendor/stbi"
IncludeDir["Assimp"] = "Komet/vendor/assimp/include"

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
		"%{prj.name}/src/Komet/Shaders/**.glsl"

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
		"%{IncludeDir.glm}",
		"%{IncludeDir.stbi}",
		"%{IncludeDir.Assimp}",
		"Komet/vendor/assimp/build/include"

	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
		"dwmapi.lib",
		"%{wks.location}/Komet/vendor/assimp/build/lib/Release/assimp-vc143-mt.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"KM_PLATFORM_WINDOWS",
			
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
	debugdir "%{wks.location}"
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
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Komet"
	}

	filter "system:windows"
		systemversion "latest"

		postbuildcommands
        {
            ("{COPY} %{wks.location}/Komet/vendor/assimp/build/bin/Release/assimp-vc143-mt.dll %{cfg.targetdir}")
        }

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
		