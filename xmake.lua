-- xmake.lua for HelloSkyrim SKSE plugin

-- Set C++23 standard
set_languages("c++23")

add_rules("mode.releasedbg")

add_repositories("SkyrimScripting https://github.com/SkyrimScripting/Packages.git")

-- Add required SKSE/CommonLibSSE package (assumes you have a xmake package or local path)
-- You may need to adjust this to your environment
add_requires("skyrim-commonlib-ng", "nlohmann_json")

if is_mode("releasedbg") then
    add_defines("NDEBUG")
    set_optimize("fastest")
    set_symbols("debug")
end

-- Define the target (shared library for SKSE plugin)
target("HelloSkyrim")
    set_kind("shared")
    add_files("src/plugin.cpp", "src/EventProcessor.cpp","src/Config/ConfigReader.cpp")
    add_headerfiles("src/PCH.h", "src/EventProcessor.h", "src/logger.h", "src/Config/ConfigReader.h")
    -- Precompiled header
    set_pcxxheader("src/PCH.h")
    add_packages("skyrim-commonlib-ng", "nlohmann_json")
    add_includedirs("src/integration/QuickLootIE")
    add_rules("@skyrim-commonlib-ng/plugin", {
        name = "HelloSkyrim",
        description = "A simple SKSE plugin for Skyrim SE/AE",
        version = "0.0.2",
        author = "walkingvart",
        email = "artemyv@gmail.com",
        mods_folder = os.getenv("SKYRIM_MODS_FOLDERS"),
        mod_files = { "SKSE"}
    })

