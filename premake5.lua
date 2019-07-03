workspace "AALife_Engine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "AALife_Engine"
	location "AALife_Engine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ALE_PLATFORM_WINDOWS",
			"ALE_BUILD_DLL",
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "ALE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "ALE_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "ALE_DIST"
		symbols "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"AALife_Engine/src"
	}

	links
	{
		"AALife_Engine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ALE_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "ALE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "ALE_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "ALE_DIST"
		symbols "On"