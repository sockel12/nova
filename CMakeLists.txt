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

add_subdirectory(deps/glad)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)

add_library(nova STATIC ${SRC_FILES})

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
  glfw
  glad
)

add_subdirectory(test_app)
