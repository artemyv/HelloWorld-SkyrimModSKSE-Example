#pragma once

namespace HelloSkyrim::Config
{
	class ConfigReader
	{
	public:
		ConfigReader() = delete;
		~ConfigReader() = delete;
		ConfigReader(ConfigReader const&) = delete;
		ConfigReader(ConfigReader const&&) = delete;
		ConfigReader operator=(ConfigReader&) = delete;
		ConfigReader operator=(ConfigReader&&) = delete;

		static void SetUp();

	private:
		static constexpr auto CONFIG_PATH = "Data\\SKSE\\Plugins\\HelloSkyrim.json";
	};
}
