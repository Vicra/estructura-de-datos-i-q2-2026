cmake_minimum_required(VERSION 3.19)
project(Projecto_EstructuraDeDatos LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(Projecto_EstructuraDeDatos
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    LinkedList.h
    LinkedList.cpp
    LinkedListController.h
    LinkedListController.cpp
    DoubleLinkedList.h
    DoubleLinkedList.cpp
    DoubleLinkedListController.h
    DoubleLinkedListController.cpp
    StackController.h
    StackController.cpp
    NodeStack.h
    Stack.h
    Stack.cpp
    Queue.h
    QueueController.h
    QueueController.cpp
    NodeQueue.h
    BST.h
    BST.cpp
    BSTController.h
    BSTController.cpp
    AVL.h
    AVL.cpp
    AVLController.h
    AVLController.cpp
    ClickableNode.h
    ClickableNode.cpp
    ClickableNodeBST.h
    ClickableNodeBST.cpp
)

target_link_libraries(Projecto_EstructuraDeDatos
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS Projecto_EstructuraDeDatos
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Projecto_EstructuraDeDatos
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
