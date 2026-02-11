#pragma once


#ifdef KM_PLATFORM_WINDOWS
#ifdef KM_DYNAMIC_LINK
	#ifdef KM_BUILD_DLL
		#define KOMET_API __declspec(dllexport)
	#else
		#define KOMET_API __declspec(dllimport)
	#endif
#else
	#define KOMET_API
#endif
#else
	#error Komet Engine is designed ONLY for WINDOWS!
#endif

//#ifdef KM_DEBUG
//	#define KM_ENABLE_ASSERTS
//#endif // HZ_DEBUG


#ifdef KM_ENABLE_ASSERTS
	#define KM_ASSERT(x, ...) { if(!(x)) { KM_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define KM_CORE_ASSERT(x, ...) { if(!(x)) { KM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(), } }
#else
	#define KM_ASSERT(x, ...)
	#define KM_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)

#define KM_BIND_EVENT_FN(fn) (std::bind(&fn, this, std::placeholders::_1))
