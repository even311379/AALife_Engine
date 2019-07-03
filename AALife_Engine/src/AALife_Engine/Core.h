#pragma once

#ifdef ALE_PLATFORM_WINDOWS
	#ifdef ALE_BUILD_DLL
		#define ALE_API __declspec(dllexport)
	#else 
		#define	ALE_API __declspec(dllimport)
	#endif
#else
	#error	aalife engine only support Windoes!

#endif

#ifdef ALE_ENABLE_ASSERTS
	#define ALE_ASSERT(x, ...) { if(!(x)) { ALE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define ALE_CORE_ASSERT(x, ...) { if(!(x)) { ALE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define ALE_ASSERT(x, ...)
	#define ALE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)