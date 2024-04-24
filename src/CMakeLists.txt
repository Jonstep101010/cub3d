# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${CUBED_SOURCE_DIR}/include/*.h")

file(GLOB sources **/**.c)
list(REMOVE_ITEM sources "./main.c")

# Make an automatic library - will be static or dynamic based on user setting
add_library(cubed ${sources} ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(cubed PUBLIC
	${PROJECT_SOURCE_DIR}/include
	${PROJECT_SOURCE_DIR}/include/MLX42
	${PROJECT_SOURCE_DIR}/include/libft
	${PROJECT_SOURCE_DIR}/include/libgnl
	${PROJECT_SOURCE_DIR}/include/libutils/include
)

# Add custom targets for the libraries
add_custom_target(libft COMMAND make -C ${PROJECT_SOURCE_DIR}/include/libft)
add_custom_target(libutils COMMAND make -C ${PROJECT_SOURCE_DIR}/include/libutils)
add_custom_target(libgnl COMMAND make -C ${PROJECT_SOURCE_DIR}/include/libgnl)
# Add dependencies
add_dependencies(cubed libft libutils libgnl)

# Link the libraries with your executable
target_link_libraries(cubed 
    ${PROJECT_SOURCE_DIR}/include/libft/libft.a 
    ${PROJECT_SOURCE_DIR}/include/libutils/libutils.a 
    ${PROJECT_SOURCE_DIR}/include/libgnl/libgnl.a 
)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})