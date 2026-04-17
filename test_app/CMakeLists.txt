cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(nova-test-app ${TEST_SOURCES})

target_link_libraries(nova-test-app PRIVATE nova)

target_include_directories(nova-test-app PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

