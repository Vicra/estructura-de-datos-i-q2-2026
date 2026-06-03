cmake_minimum_required(VERSION 3.19)
project(site-mapper LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(site-mapper
    main.cpp
)

target_link_libraries(site-mapper
    PRIVATE
        Qt::Core
)

include(GNUInstallDirs)

install(TARGETS site-mapper
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
