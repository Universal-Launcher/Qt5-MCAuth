add_rules("mode.debug", "mode.release")

set_languages("cxx20")
set_warnings("allextra")

target("qt-mcauth")
    set_kind("shared")
    add_rules("qt.shared")

    add_files("src/**.cpp")
    add_headerfiles("src/**.h")
    add_includedirs("include", { public = true })

    add_frameworks("QtCore", "QtNetwork", "QtNetworkAuth")

    on_load(function (target)
        import("detect.sdks.find_qt")

        local qt = find_qt()
        if (not qt) then
            -- Disable building by default if Qt is not found
            target:set("default", false)
        end
    end)

target("test")
    set_kind("binary")
    add_rules("qt.console")

    add_files("test/**.cpp")
    add_deps("qt-mcauth")
