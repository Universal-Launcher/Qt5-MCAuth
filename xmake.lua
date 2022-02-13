add_rules("mode.debug", "mode.release")

set_languages("cxx20")
set_warnings("allextra")

target("qt-mcauth")
    add_rules("qt.shared")

    add_files("src/**.cpp")
    add_includedirs("include", { public = true })

    add_frameworks("QtNetwork", "QtNetworkAuth", { public = true })
    add_defines("QT_MCAUTH_LIBRARY")

target("qt-mcauth_static")
    add_rules("qt.static")

    add_files("src/**.cpp")
    add_includedirs("include", { public = true })

    add_frameworks("QtNetwork", "QtNetworkAuth", { public = true })
    add_defines("QT_MCAUTH_LIBRARY_STATIC")

target("test")
    add_rules("qt.console")

    add_files("test/**.cpp")
    --add_deps("qt-mcauth_static")
    add_files("src/**.cpp")
    add_includedirs("include")
    add_frameworks("QtNetwork", "QtNetworkAuth", { public = true })
