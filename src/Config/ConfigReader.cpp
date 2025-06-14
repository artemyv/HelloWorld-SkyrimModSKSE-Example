#include "ConfigReader.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <spdlog/spdlog.h>
#include <fstream>
namespace HelloSkyrim::Config
{
	void ConfigReader::SetUp()
	{
		json config{};

		try {
			std::ifstream ifs;
			ifs.open(CONFIG_PATH, std::ios::in);

			if (!ifs.is_open()) {
				logger::info("No config file {} present", CONFIG_PATH);
				return;
			}

			config = json::parse(ifs, nullptr, true, true);
		} catch (nlohmann::json::parse_error& error) {
			logger::error("Failed to parse config file {}: {}", CONFIG_PATH, error.what());
			return;
		}

		const auto logLevelstr = config.value("logLevel", "info");
		const auto logLevel = spdlog::level::from_str(logLevelstr);

		spdlog::set_level(logLevel);
		spdlog::flush_on(logLevel);
		logger::info("Log level changed to {}", logLevelstr);
	}
}
