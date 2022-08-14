#include "Logger.h"

namespace OpenGLRenderer
{
	std::shared_ptr<spdlog::logger> Logger::s_Logger;

	void Logger::Initialize()
	{
		spdlog::set_pattern("%^[%T]$ %v%$");
		s_Logger = spdlog::stdout_color_mt("LOGGER");
		s_Logger->set_level(spdlog::level::trace);
		LOG_INFO("Logger initialized.");
	}
}
