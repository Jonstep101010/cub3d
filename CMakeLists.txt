# Works with 3.14 and tested through 3.27
cmake_minimum_required(VERSION 3.14...3.28)

# Project name and a few useful settings. Other commands can pick up the results
project(
  CUBED
  VERSION 0.1
  DESCRIPTION "cub3d with cmake"
  LANGUAGES C)

set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -fsanitize=address")

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  # Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here

  # Let's ensure -std=c++xx instead of -std=g++xx
  set(CMAKE_CXX_EXTENSIONS OFF)

  # Let's nicely support folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  # Testing only available if this is the main app
  # Note this needs to be done in the main CMakeLists
  # since it calls enable_testing, which must be in the
  # main CMakeLists.
  include(CTest)

endif()

# FetchContent added in CMake 3.11, downloads during the configure step
# FetchContent_MakeAvailable was added in CMake 3.14; simpler usage
include(FetchContent)

# The compiled library code is here
add_subdirectory(src)

# link main.c to libcubed
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/MLX42)

add_executable(cub3d src/main.c)
target_link_libraries(cub3d PRIVATE cubed mlx42)
target_include_directories(cub3d PRIVATE 
	${CMAKE_CURRENT_SOURCE_DIR}/libs/MLX42/include/MLX42/
	${CMAKE_CURRENT_SOURCE_DIR}/include/
)

# implement compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
   AND BUILD_TESTING)
#   add_subdirectory(tests)
endif()
