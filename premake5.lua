workspace "AALife_Engine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

    flags
	{
		"MultiProcessorCompile"
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution dir)
IncludeDir = {}
IncludeDir["GLFW"] = "AALife_Engine/vendor/GLFW/include"
IncludeDir["Glad"] = "AALife_Engine/vendor/Glad/include"
IncludeDir["ImGui"] = "AALife_Engine/vendor/imgui"
IncludeDir["glm"] = "AALife_Engine/vendor/glm"
IncludeDir["stb_image"] = "AALife_Engine/vendor/stb_image"

group "Dependencies"
	include "AALife_Engine/vendor/GLFW"
	include "AALife_Engine/vendor/Glad"
	include "AALife_Engine/vendor/imgui"


group ""

project "AALife_Engine"
	location "AALife_Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "alePCH.h"
	pchsource "AALife_Engine/src/alePCH.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp",
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
		"%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"ALE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "ALE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ALE_RELEASE"
		runtime "Release"
		symbols "on"

	filter "configurations:Dist"
		defines "ALE_DIST"
		runtime "Release"
		symbols "on"

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
		"AALife_Engine/vendor/spdlog/include",
		"AALife_Engine/src",
		"AALife_Engine/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"AALife_Engine"
	}

	filter "system:windows"
		systemversion "latest"    

	filter "configurations:Debug"
		defines "ALE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ALE_RELEASE"
		runtime "Release"
		symbols "on"

	filter "configurations:Dist"
		defines "ALE_DIST"
		runtime "Release"
		symbols "on"

