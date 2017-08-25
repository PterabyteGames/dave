project (glad C)

add_library (glad
	INTERFACE
)

target_include_directories (
  glad
  INTERFACE
  ${PROJECT_SOURCE_DIR}
)
