add_rules("mode.debug", "mode.release")


target("qt-mcauth")
    add_rules("qt.shared")

    add_files("src/**.cpp")
    add_files("include/**.h")
    add_includedirs("include", { public = true })

    set_languages("cxx20")
    set_warnings("allextra")
    add_frameworks("QtGui", "QtNetwork", "QtNetworkAuth", { public = true })
    add_cxflags("-fPIC", { force = true })
    add_defines("QT_MCAUTH_LIBRARY")

target("test")
    add_rules("qt.widgetapp")

    set_languages("cxx20")
    set_warnings("allextra")
    add_files("test/**.cpp")
    add_deps("qt-mcauth")
    add_includedirs("include")
    add_frameworks("QtNetwork")
