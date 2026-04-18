cmake_minimum_required(VERSION 3.10)

file(GLOB_RECURSE TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(nova-test-app ${TEST_SOURCES})

target_link_libraries(nova-test-app PRIVATE nova)

target_include_directories(nova-test-app PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Make resources available next to the executable in the build tree.
set(TEST_APP_RESOURCES_SRC "${CMAKE_CURRENT_SOURCE_DIR}/resources")
set(TEST_APP_RESOURCES_DST "$<TARGET_FILE_DIR:nova-test-app>/resources")

if(WIN32)
	# Symlink creation can require elevated privileges on Windows.
	add_custom_command(TARGET nova-test-app POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E remove_directory "${TEST_APP_RESOURCES_DST}"
		COMMAND ${CMAKE_COMMAND} -E copy_directory "${TEST_APP_RESOURCES_SRC}" "${TEST_APP_RESOURCES_DST}"
		COMMENT "Copying test_app resources next to nova-test-app"
	)
else()
	add_custom_command(TARGET nova-test-app POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E remove_directory "${TEST_APP_RESOURCES_DST}"
		COMMAND ${CMAKE_COMMAND} -E create_symlink "${TEST_APP_RESOURCES_SRC}" "${TEST_APP_RESOURCES_DST}"
		COMMENT "Symlinking test_app resources next to nova-test-app"
	)
endif()

