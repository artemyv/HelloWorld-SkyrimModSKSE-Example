add_rules("mode.debug", "mode.release", "mode.releasedbg")

set_languages("c++23")

option("commonlib")
    set_default("skyrim-commonlib-ng")
option_end()

option("build_example")
    set_default(true)
option_end()

library_name = "SkyrimScripting.Logging"

if has_config("build_example") then
    add_repositories("SkyrimScripting https://github.com/SkyrimScripting/Packages.git")
end

if not has_config("commonlib") then
    print("Please specify the commonlib package to use with the --commonlib option")
    return
end

add_requires(get_config("commonlib"))

commonlib_version = get_config("commonlib"):match("skyrim%-commonlib%-(.*)")

target(library_name)
    set_kind("static")
    add_files("src/*.cpp")
    add_includedirs("include", { public = true })
    add_headerfiles("include/(**.h)")
    add_packages(get_config("commonlib"), { public = true })

if has_config("build_example") then
    mod_info = { name = "Test plugin for " .. library_name }

    mods_folders = os.getenv("SKYRIM_MODS_FOLDERS")

    if mods_folders then
        mod_info.mods_folders = mods_folders
    else
        print("SKYRIM_MODS_FOLDERS environment variable not set")
    end

    target("_SksePlugin-" .. commonlib_version:upper())
        set_basename(mod_info.name .. "-" .. commonlib_version:upper())
        add_files("*.cpp")
        add_rules("@skyrim-commonlib-" .. commonlib_version .. "/plugin", {
            mod_name = mod_info.name .. " (" .. commonlib_version:upper() .. ")",
            mods_folders = mod_info.mods_folders or "",
            name = mod_info.name
        })
        add_deps(library_name)
end
