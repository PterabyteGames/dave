project (glad C)

add_library (glad SHARED "")

target_compile_definitions (
    glad

    PRIVATE
    GLAD_GLAPI_EXPORT_BUILD

    PUBLIC
    GLAD_GLAPI_EXPORT
)

target_sources(
    glad
    PRIVATE
    ${PROJECT_SOURCE_DIR}/glad.c
)

target_include_directories (
    glad
    PUBLIC
    ${PROJECT_SOURCE_DIR}
)
