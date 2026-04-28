cmake_minimum_required(VERSION 3.19)
project(QueueLL LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(QueueLL
    main.cpp
    queue.h queue.cpp
    node.h node.cpp
)

target_link_libraries(QueueLL
    PRIVATE
        Qt::Core
)

include(GNUInstallDirs)

install(TARGETS QueueLL
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
