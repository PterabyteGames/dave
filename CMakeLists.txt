cmake_minimum_required (VERSION 3.5)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option (DAVEAPI_EXPORT ON "")
option (DAVEAPI_EXPORT_BUILD ON "")

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
	source/core/platform_desktop.cpp
	source/core/system.cpp
	source/core/task.cpp
	source/core/task_scheduler.cpp

	source/video/video.cpp
	source/video/window_desktop.cpp

	external/glad/glad.c
)

if (WIN32 OR UNIX)
	set (WINDOW_HANDLE_FORWARD_DECLARATION GLFWwindow)
endif()

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/include/dave/core/platform.hpp.in
	            ${CMAKE_CURRENT_BINARY_DIR}/dave/core/platform.hpp
			    @ONLY)

add_library (${PROJECT_NAME} SHARED ${SOURCE})

target_include_directories (${PROJECT_NAME}
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_BINARY_DIR}

	# OpenGL
	SYSTME PUBLIC
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
	opengl32
)

target_compile_definitions (
    ${PROJECT_NAME}
    PUBLIC
    DAVEAPI_EXPORT
    DAVEAPI_EXPORT_BUILD
)

target_compile_options(${PROJECT_NAME} PRIVATE
	"$<$<CXX_COMPILER_ID:MSVC>:/std:c++latest>"
	"$<$<CXX_COMPILER_ID:Clang>:-std=c++1z>"
	"$<$<CXX_COMPILER_ID:GNU>:-std=c++1z>")

target_compile_options(${PROJECT_NAME} PRIVATE
	"$<$<CXX_COMPILER_ID:Clang>:-fPIC>"
	"$<$<CXX_COMPILER_ID:GNU>:-fPIC>")

add_subdirectory (examples)
