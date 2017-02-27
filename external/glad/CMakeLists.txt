project (glad C)

add_library (glad
	SHARED
	glad.c
)

target_include_directories (
	glad
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_compile_options(glad PRIVATE
                       "$<$<C_COMPILER_ID:Clang>:-std=c11>"
                       "$<$<C_COMPILER_ID:GNU>:-std=c11>")

