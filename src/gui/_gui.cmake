qt_add_executable(q3tod3_map_gui WIN32 MACOSX_BUNDLE
    ${CMAKE_SOURCE_DIR}/src/gui/main.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/about.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/about.h
    ${CMAKE_SOURCE_DIR}/src/gui/about.ui
    ${CMAKE_SOURCE_DIR}/src/gui/mainwindow.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/mainwindow.h
    ${CMAKE_SOURCE_DIR}/src/gui/mainwindow.ui
    ${CMAKE_SOURCE_DIR}/src/core/q3tod3_map.cpp
    ${CMAKE_SOURCE_DIR}/src/core/q3tod3_map.h
    ${CMAKE_SOURCE_DIR}/src/core/config.h
)
target_include_directories(q3tod3_map_gui PRIVATE
    ${CMAKE_SOURCE_DIR}/src/core
)

target_compile_definitions(q3tod3_map_gui PRIVATE
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
