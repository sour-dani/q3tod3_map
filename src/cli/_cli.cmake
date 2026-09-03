add_executable(q3tod3_map MACOSX_BUNDLE
    ${CMAKE_SOURCE_DIR}/src/cli/main.cpp
    ${CMAKE_SOURCE_DIR}/src/core/q3tod3_map.cpp
    ${CMAKE_SOURCE_DIR}/src/core/q3tod3_map.h
    ${CMAKE_SOURCE_DIR}/src/core/config.h
)

target_include_directories(q3tod3_map PRIVATE
    ${CMAKE_SOURCE_DIR}/src/core
)

install(TARGETS q3tod3_map
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
