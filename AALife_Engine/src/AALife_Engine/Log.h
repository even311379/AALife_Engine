#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace ale {

	class ALE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};

}

// Core log macros
#define ALE_CORE_TRACE(...)   ::ale::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ALE_CORE_INFO(...)    ::ale::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ALE_CORE_WARN(...)    ::ale::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ALE_CORE_ERROR(...)   ::ale::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ALE_CORE_FATAL(...)   ::ale::Log::GetCoreLogger()->critical(__VA_ARGS__)

// client log macros
#define ALE_TRACE(...)        ::ale::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ALE_INFO(...)         ::ale::Log::GetClientLogger()->info(__VA_ARGS__)
#define ALE_WARN(...)         ::ale::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ALE_ERROR(...)        ::ale::Log::GetClientLogger()->error(__VA_ARGS__)
#define ALE_FATAL(...)        ::ale::Log::GetClientLogger()->critical(__VA_ARGS__)