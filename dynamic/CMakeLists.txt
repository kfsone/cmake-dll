add_library (dynamic SHARED dynamic.cpp)

if (TEST_DYNAMIC_COPY)
	# Doesn't do what you think, doesn't work.
	add_custom_command (
		TARGET dynamic
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
				$<TARGET_RUNTIME_DLLS:dynamic>
				$<TARGET_FILE_DIR:dynamic>
		COMMAND_EXPAND_LISTS
	)
endif ()
