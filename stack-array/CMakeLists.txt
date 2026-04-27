cmake_minimum_required(VERSION 3.19)
project(stack-array LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(stack-array
    main.cpp
    stackarray.h stackarray.cpp
)

target_link_libraries(stack-array
    PRIVATE
        Qt::Core
)

include(GNUInstallDirs)

install(TARGETS stack-array
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
