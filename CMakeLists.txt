cmake_minimum_required (VERSION 3.5)

set (BUILD_SHARED_LIBS   ON)
set (GLFW_BUILD_DOCS     OFF CACHE BOOL "")
set (GLFW_BUILD_TESTS    OFF CACHE BOOL "")
set (GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/external/glfw)

add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/external/glm)

add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/external/glad)

set (LUA_COMPAT_5_1 OFF CACHE BOOL "")
set (LUA_COMPAT_5_2 OFF CACHE BOOL "")
add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/external/lua/lua)
set (LUA_INCLUDE_DIRS
	 ${CMAKE_CURRENT_SOURCE_DIR}/external/lua/lua/src
	 ${CMAKE_CURRENT_BINARY_DIR}/external/lua/lua
)

project (DAVE CXX)

set (SOURCE
	source/core/engine.cpp
	source/core/system.cpp
	source/core/task.cpp
	source/core/task_scheduler.cpp

	source/video/video.cpp
)

add_library (${PROJECT_NAME} SHARED ${SOURCE})

target_include_directories (${PROJECT_NAME}
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include

	# OpenGL
	glad
	glm
	glfw

	# Lua
	${LUA_INCLUDE_DIRS}
	${CMAKE_CURRENT_SOURCE_DIR}/external/lua/sol2
)

target_link_libraries (${PROJECT_NAME}
	glad
	glfw
	liblua
)

target_compile_options(${PROJECT_NAME} PRIVATE
	"$<$<CXX_COMPILER_ID:Clang>:-std=c++1z>"
	"$<$<CXX_COMPILER_ID:GNU>:-std=c++1z>")

target_compile_options(${PROJECT_NAME} PRIVATE
	"$<$<CXX_COMPILER_ID:Clang>:-fPIC>"
	"$<$<CXX_COMPILER_ID:GNU>:-fPIC>")
