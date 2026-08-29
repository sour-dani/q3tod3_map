qt_add_library(q3tod3_map_core
    q3tod3_map.cpp q3tod3_map.h
)
target_link_libraries(q3tod3_map_core PUBLIC
    Qt::Core
    Qt::Gui
)

install(TARGETS q3tod3_map_core
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
