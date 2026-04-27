cmake_minimum_required(VERSION 3.19)
project(stack-ll LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(stack-ll
    main.cpp
    stackll.h stackll.cpp
    node.h node.cpp
)

target_link_libraries(stack-ll
    PRIVATE
        Qt::Core
)

include(GNUInstallDirs)

install(TARGETS stack-ll
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
