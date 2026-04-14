// VizEngine/src/VizEngine/Core.h
// Chapter 4: DLL Architecture — VizEngine_API dllexport/dllimport visibility macro.

#pragma once

#ifdef VP_PLATFORM_WINDOWS
	#ifdef VP_BUILD_DLL
		#define VizEngine_API __declspec(dllexport)
	#else
		#define VizEngine_API __declspec(dllimport)
	#endif
#elif defined(__GNUC__) || defined(__clang__)
	#define VizEngine_API __attribute__((visibility("default")))
#else
	#define VizEngine_API  // Fallback for unknown compilers
#endif
