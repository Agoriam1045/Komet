#pragma once


#ifdef KM_PLATFORM_WINDOWS
	#ifdef KM_BUILD_DLL
		#define KOMET_API __declspec(dllexport)
	#else
		#define KOMET_API __declspec(dllimport)
	#endif
#else
	#error Komet Engine is designed ONLY for WINDOWS!
#endif