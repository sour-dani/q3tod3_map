qt_add_executable(q3tod3_map WIN32 MACOSX_BUNDLE
    main.cpp
    ../core/q3tod3_map.cpp
    ../core/q3tod3_map.h
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
