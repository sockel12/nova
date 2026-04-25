cmake_minimum_required(VERSION 3.10)

project(nova VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



include(FetchContent)

# SPDLOG dependency
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(spdlog)


# GLM dependency
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 1.0.3
)
FetchContent_MakeAvailable(glm)

# EnTT dependency
FetchContent_Declare(
  entt
  GIT_REPOSITORY https://github.com/skypjack/entt.git
  GIT_TAG v3.16.0
)
FetchContent_MakeAvailable(entt)

# GLFW dependency
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
option(NOVA_GLFW_USE_WAYLAND "Enable GLFW Wayland backend" OFF)
option(NOVA_GLFW_USE_X11 "Enable GLFW X11 backend" ON)
set(GLFW_BUILD_WAYLAND ${NOVA_GLFW_USE_WAYLAND} CACHE BOOL "" FORCE)
set(GLFW_BUILD_X11 ${NOVA_GLFW_USE_X11} CACHE BOOL "" FORCE)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
)
FetchContent_MakeAvailable(glfw)

# Dear ImGui dependency
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui.git
  GIT_TAG v1.92.1
)
FetchContent_MakeAvailable(imgui)

add_library(imgui STATIC
  ${imgui_SOURCE_DIR}/imgui.cpp
  ${imgui_SOURCE_DIR}/imgui_draw.cpp
  ${imgui_SOURCE_DIR}/imgui_tables.cpp
  ${imgui_SOURCE_DIR}/imgui_widgets.cpp
  ${imgui_SOURCE_DIR}/imgui_demo.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
  ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui
  PUBLIC
  ${imgui_SOURCE_DIR}
  ${imgui_SOURCE_DIR}/backends
)

target_compile_definitions(imgui PUBLIC
  IMGUI_IMPL_OPENGL_LOADER_GLAD2
)

target_link_libraries(imgui PUBLIC glfw)

add_subdirectory(deps/glad)
add_subdirectory(deps/stb)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)

add_library(nova STATIC ${SRC_FILES})

target_precompile_headers(nova PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/nova/common.h)

target_compile_definitions(nova PUBLIC
    GLFW_INCLUDE_NONE
)

target_include_directories(nova
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
 
target_link_libraries(nova 
  PUBLIC 
  spdlog::spdlog
  EnTT::EnTT
  glfw
  glad
  glm
  imgui
  stb
)

add_subdirectory(test_app)
