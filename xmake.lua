add_rules("mode.debug", "mode.release")

set_languages("cxx20")
set_warnings("allextra")


option("test")
    set_default(false)
    set_showmenu(true)
    set_description("Compile test program")

target("qt-mcauth")
    add_rules("qt.shared")

    add_files("src/**.cpp")
    add_files("include/**.h")
    add_headerfiles("include/(qt_mcauth/**.h)")
    add_includedirs("include", { public = true })

    add_frameworks("QtGui", "QtNetwork", "QtNetworkAuth", { public = true })
    add_cxflags("-fPIC", { force = true })
    add_defines("QT_MCAUTH_LIBRARY")


if has_config("test") then
    target("test")
        add_rules("qt.widgetapp")
        add_files("test/main.cpp", "test/secret.h")
        add_deps("qt-mcauth")
        add_frameworks("QtNetwork")
end
