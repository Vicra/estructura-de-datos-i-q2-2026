cmake_minimum_required(VERSION 3.19)
project(SimpleLinkedList LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(SimpleLinkedList
    main.cpp
    node.h node.cpp
)

target_link_libraries(SimpleLinkedList
    PRIVATE
        Qt::Core
)

include(GNUInstallDirs)

install(TARGETS SimpleLinkedList
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
