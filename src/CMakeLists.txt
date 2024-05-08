# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -fsanitize=address")
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${CUBED_SOURCE_DIR}/libs/*.h")

file(GLOB sources mock_dda.c input/*.c input/textures/*.c input/map/*.c utils/*.c view/*.c dda_ray/*.c)

# Make an automatic library - will be static or dynamic based on user setting
add_library(cubed ${sources} ${HEADER_LIST})

# Add custom targets for the libraries
add_custom_target(libgnl COMMAND make -C ${PROJECT_SOURCE_DIR}/libs/gnl)
add_custom_target(libutils COMMAND make -C ${PROJECT_SOURCE_DIR}/libs/utils)
add_custom_target(libft COMMAND make -C ${PROJECT_SOURCE_DIR}/libs/libft)

# Add dependencies
add_dependencies(cubed libft libutils libgnl)

# Link the libraries with your executable
target_link_libraries(cubed
	${PROJECT_SOURCE_DIR}/libs/gnl/libgnl.a
	${PROJECT_SOURCE_DIR}/libs/utils/libutils.a
	${PROJECT_SOURCE_DIR}/libs/libft/libft.a
)

# We need this directory, and users of our library will need it too
target_include_directories(cubed PUBLIC
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/libs/MLX42/include/MLX42
	${PROJECT_SOURCE_DIR}/libs/gnl
	${PROJECT_SOURCE_DIR}/libs/utils/include
	${PROJECT_SOURCE_DIR}/libs/libft
)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
