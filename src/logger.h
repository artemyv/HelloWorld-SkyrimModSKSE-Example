#pragma once

// This is a snippet you can put at the top of all of your SKSE plugins!

#include <spdlog/sinks/basic_file_sink.h>

namespace logger = SKSE::log;
namespace HelloSkyrim {
    auto SetupLog() {
        auto logsFolder = SKSE::log::log_directory();
        if (!logsFolder) SKSE::stl::report_and_fail("SKSE log_directory not provided, logs disabled.");
        auto pluginName    = SKSE::PluginDeclaration::GetSingleton()->GetName();
        auto logFilePath   = *logsFolder / std::format("{}.log", pluginName);
        auto fileLoggerPtr = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFilePath.string(), true);
        auto loggerPtr     = std::make_shared<spdlog::logger>("log", std::move(fileLoggerPtr));
        spdlog::set_default_logger(std::move(loggerPtr));
        spdlog::set_level(spdlog::level::info);  // vart::todo read log level from ini file
        spdlog::flush_on(spdlog::level::info);
        return logFilePath;
    }
}
