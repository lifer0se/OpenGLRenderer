#ifndef LOGGER_CLASS_H
#define LOGGER_CLASS_H

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"


#define LOG_TRACE(...)      ::OpenGLRenderer::Logger::GetLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)       ::OpenGLRenderer::Logger::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)       ::OpenGLRenderer::Logger::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)      ::OpenGLRenderer::Logger::GetLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)   ::OpenGLRenderer::Logger::GetLogger()->critical(__VA_ARGS__)

namespace OpenGLRenderer
{
	class Logger
	{
	public:
		static void Initialize();

		inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }

	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};

}

#endif
