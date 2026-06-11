cmake_minimum_required(VERSION 3.19)
project(rat-in-maze LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(rat-in-maze
    main.cpp
    Solution.h
)

target_link_libraries(rat-in-maze
    PRIVATE
        Qt::Core
)

include(GNUInstallDirs)

install(TARGETS rat-in-maze
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
