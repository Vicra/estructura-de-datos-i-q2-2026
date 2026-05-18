cmake_minimum_required(VERSION 3.19)
project(BinarySearchTree LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(BinarySearchTree
    main.cpp
    node.h node.cpp
    bst.h bst.cpp
)

target_link_libraries(BinarySearchTree
    PRIVATE
        Qt::Core
)

include(GNUInstallDirs)

install(TARGETS BinarySearchTree
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
