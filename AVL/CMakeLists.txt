cmake_minimum_required(VERSION 3.19)
project(AVL LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(AVL
    main.cpp

    node.h node.cpp
    avltree.h avltree.cpp
)

target_link_libraries(AVL
    PRIVATE
        Qt::Core
)

include(GNUInstallDirs)

install(TARGETS AVL
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
