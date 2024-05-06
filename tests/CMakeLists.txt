# Testing library
FetchContent_Declare(
  unity
  GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
  GIT_TAG v2.5.2)
FetchContent_MakeAvailable(unity)

# # Tests need to be added as executables first
# add_executable(unitytestlib unitytestlib.c)

# # Should be linked to the main library, as well as the Catch2 testing library
# target_link_libraries(unitytestlib PRIVATE c_library unity::framework)

# add_test(NAME unitytestlibtest COMMAND unitytestlib) # Command can be a target

find_program(RUBY
    NAMES ruby
    REQUIRED    # NOTE: this doesn't work until CMake 3.18
    DOC "Path to ruby executable"
	message("RUBY FOUND")
    )

if(${RUBY} STREQUAL "RUBY-NOTFOUND")
    message(WARNING "Program 'ruby' not found. Can not auto-generate Unity test runners")
endif()
# 		# message(WARNING "Program 'ruby' not found. Can not auto-generate Unity test runners")


function(add_unity_tests test_directory lib_name)
	if (NOT RUBY)
		message(WARNING "Program 'ruby' not found. Can not auto-generate Unity test runners")
		return()
	endif()
	file(GLOB test_files "${test_directory}/*.c")# find all .c files in the current directory and subdirectories
	foreach(test_file ${test_files})
		get_filename_component(target ${test_file} NAME_WE)
		set(runner_file "${CMAKE_CURRENT_BINARY_DIR}/${target}_runner.c")
		add_custom_command(
			OUTPUT ${runner_file}
			COMMAND ${RUBY} "${unity_SOURCE_DIR}/auto/generate_test_runner.rb" "${test_file}" "${runner_file}"
			DEPENDS ${test_file}
			COMMENT "Generating test runner for: '${test_file}'"
		)
		add_executable(${target}_runner ${runner_file} ${test_file})
		target_link_libraries(${target}_runner PRIVATE unity::framework ${lib_name})
		target_include_directories(${target}_runner PRIVATE ../src ../include)
		add_test(NAME ${target} COMMAND ${target}_runner)
	endforeach()
endfunction()

add_unity_tests(./ cubed)