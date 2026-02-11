#pragma once

#include "Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Komet {
	class KOMET_API Log {
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//CORE LOG MACROS
#define KM_CORE_TRACE(...)   ::Komet::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define KM_CORE_INFO(...)    ::Komet::Log::GetCoreLogger()->info(__VA_ARGS__)
#define KM_CORE_WARN(...)    ::Komet::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define KM_CORE_ERROR(...)   ::Komet::Log::GetCoreLogger()->error(__VA_ARGS__)
#define KM_CORE_FATAL(...)   ::Komet::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//CLIENT LOG MACROS

#define KM_TRACE(...)        ::Komet::Log::GetClientLogger()->trace(__VA_ARGS__)
#define KM_INFO(...)         ::Komet::Log::GetClientLogger()->info(__VA_ARGS__)
#define KM_WARN(...)         ::Komet::Log::GetClientLogger()->warn(__VA_ARGS__)
#define KM_ERROR(...)        ::Komet::Log::GetClientLogger()->error(__VA_ARGS__)
#define KM_FATAL(...)	     ::Komet::Log::GetClientLogger()->fatal(__VA_ARGS__)