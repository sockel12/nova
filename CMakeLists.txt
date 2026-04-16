cmake_minimum_required(VERSION 3.10)

project(nova VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GENERATE_COMPILE_COMMANDS ON)


include(FetchContent)

# spdlog
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(spdlog)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_library(nova STATIC ${SRC_FILES})

target_include_directories(nova
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(nova 
  PUBLIC 
  spdlog::spdlog
)
