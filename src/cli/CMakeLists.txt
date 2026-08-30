qt_add_executable(q3tod3_map WIN32 MACOSX_BUNDLE
    main.cpp
)

target_include_directories(q3tod3_map PRIVATE
    ../core
)

target_compile_definitions(q3tod3_map PRIVATE
    APP_VERSION="${CMAKE_PROJECT_VERSION}"
)

install(TARGETS q3tod3_map
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET q3tod3_map
    FILENAME_VARIABLE deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)

install(SCRIPT ${deploy_script})
