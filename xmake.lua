-- xmake.lua for HelloSkyrim SKSE plugin

-- Set C++23 standard
set_languages("c++23")

add_rules("mode.releasedbg")

add_repositories("SkyrimScripting https://github.com/SkyrimScripting/Packages.git")

-- Add required SKSE/CommonLibSSE package (assumes you have a xmake package or local path)
-- You may need to adjust this to your environment
add_requires("skyrim-commonlib-ng")

-- Define the target (shared library for SKSE plugin)
target("HelloSkyrim")
    set_kind("shared")
    add_files("src/plugin.cpp")
    add_headerfiles("src/logger.h", "src/PCH.h")
    -- Precompiled header
    set_pcxxheader("src/PCH.h")
    add_packages("skyrim-commonlib-ng")
    add_rules("@skyrim-commonlib-ng/plugin", {
        name = "Simple Plugin HelloSkyrim NG",
        version = "0.0.1",
        author = "walkingvart",
        email = "artemyv@gmail.com",
        mods_folder = os.getenv("SKYRIM_MODS_FOLDERS")
    })

