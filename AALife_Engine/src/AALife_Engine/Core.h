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

#define BIT(x) (1 << x)