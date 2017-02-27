cmake_minimum_required (VERSION 3.5)

set (GLFW_BUILD_DOCS     OFF CACHE BOOL "")
set (GLFW_BUILD_TESTS    OFF CACHE BOOL "")
set (GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/external/glfw)

add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/external/glm)

add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/external/glad)

project (DAVE CXX)

set (SOURCE
	source/core/engine.cpp
	source/core/system.cpp
	source/core/task.cpp
	source/core/task_scheduler.cpp

	source/video/video.cpp
)

add_library (${PROJECT_NAME} SHARED ${SOURCE})

find_package (OpenGL REQUIRED)

target_include_directories (${PROJECT_NAME}
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
	glad
	glm
	glfw
)

target_link_libraries (${PROJECT_NAME}
	glad
	glfw
)

target_compile_options(${PROJECT_NAME} PRIVATE
	"$<$<CXX_COMPILER_ID:Clang>:-std=c++1z>"
	"$<$<CXX_COMPILER_ID:GNU>:-std=c++1z>")

target_compile_options(${PROJECT_NAME} PRIVATE
	"$<$<CXX_COMPILER_ID:Clang>:-fPIC>"
	"$<$<CXX_COMPILER_ID:GNU>:-fPIC>")
