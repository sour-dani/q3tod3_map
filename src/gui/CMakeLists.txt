qt_add_executable(q3tod3_map_gui WIN32 MACOSX_BUNDLE
    main.cpp
    about.cpp
    about.h
    about.ui
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ../core/q3tod3_map.cpp
    ../core/q3tod3_map.h
)

target_include_directories(q3tod3_map_gui PRIVATE
    ../core
)

target_compile_definitions(q3tod3_map_gui PRIVATE
    VERSION="${CMAKE_PROJECT_VERSION}"
    QT_DISABLE_DEPRECATED_BEFORE=0x060000
)

target_link_libraries(q3tod3_map_gui PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

install(TARGETS q3tod3_map_gui
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET q3tod3_map_gui
    FILENAME_VARIABLE deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})
