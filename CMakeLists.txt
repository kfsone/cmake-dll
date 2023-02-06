cmake_minimum_required (VERSION 3.21)
project (CMakeDll LANGUAGES CXX)

add_subdirectory (dynamic)

add_executable (main main.cpp)
target_link_libraries (main dynamic)

if (TEST_MAIN_COPY)
	add_custom_command (
		TARGET main
			COMMAND ${CMAKE_COMMAND} -E copy_if_different
				$<TARGET_RUNTIME_DLLS:main>
				$<TARGET_FILE_DIR:main>
		COMMAND_EXPAND_LISTS
	)
endif ()
