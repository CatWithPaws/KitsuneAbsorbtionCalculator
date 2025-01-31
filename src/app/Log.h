#pragma once


#include "spdlog/spdlog.h"

namespace Dudy
{
	class  Log
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


//Core Log macros
#define DD_CORE_ERROR(...)		::Dudy::Log::GetCoreLogger()->error(__VA_ARGS__)
#define DD_CORE_WARN(...)		::Dudy::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define DD_CORE_INFO(...)		::Dudy::Log::GetCoreLogger()->info(__VA_ARGS__)
#define DD_CORE_TRACE(...)		::Dudy::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define DD_CORE_FATAL(...)		::Dudy::Log::GetCoreLogger()->critical(__VA_ARGS__)

//Client Log macros
#define DD_ERROR(...)			::Dudy::Log::GetClientLogger()->error(__VA_ARGS__)
#define DD_WARN(...)			::Dudy::Log::GetClientLogger()->warn(__VA_ARGS__)
#define DD_INFO(...)			::Dudy::Log::GetClientLogger()->info(__VA_ARGS__)
#define DD_TRACE(...)			::Dudy::Log::GetClientLogger()->trace(__VA_ARGS__)
#define DD_FATAL(...)			::Dudy::Log::GetClientLogger()->critical(__VA_ARGS__)