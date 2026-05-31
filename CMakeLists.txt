cmake_minimum_required(VERSION 3.16)

project(PhysicsPenguin LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)
find_package(OpenGL REQUIRED)

include(FetchContent)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0af55ccecd98d4e5a8d1fad7de25ba429d60e863
)

FetchContent_Declare(
    glfw
    URL https://github.com/glfw/glfw/archive/refs/tags/3.4.tar.gz
)

FetchContent_MakeAvailable(glm glfw)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(PhysicsPenguin main.cpp glad.c
    core/core.cpp core/core.h core/events.cpp core/events.h core/input.cpp core/input.h core/mesh.cpp core/mesh.h core/particle.cpp core/particle.h core/scene.h core/scenemanager.cpp core/scenemanager.h core/shader.cpp core/shader.h core/window.cpp core/window.h
    scenes/triangletestscene.cpp scenes/triangletestscene.h
    shaders/test_triangle.frag shaders/test_triangle.vert)
target_link_libraries(PhysicsPenguin PRIVATE glm::glm glfw Threads::Threads OpenGL::GL)

include(GNUInstallDirs)
install(TARGETS PhysicsPenguin
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)