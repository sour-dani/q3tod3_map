add_executable(q3tod3_map WIN32 MACOSX_BUNDLE
    main.cpp
    ../core/q3tod3_map.cpp
    ../core/q3tod3_map.h
)
set(COMPILE_INFO "${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_SYSTEM_NAME}-${CMAKE_CXX_COMPILER_ID}")
# x86_64-pc-windows-msvc
target_include_directories(q3tod3_map PRIVATE
    ../core
)

target_compile_definitions(q3tod3_map PRIVATE
    VERSION="${CMAKE_PROJECT_VERSION}"
    COMPILE_INFO="${COMPILE_INFO}"
)
install(TARGETS q3tod3_map
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
message(${COMPILE_INFO})
