project (hello_dave CXX)

add_executable (
    hello_dave
    hello_dave.cpp
)

target_compile_options(hello_dave PRIVATE
    "$<$<CXX_COMPILER_ID:MSVC>:/std:c++latest>"
    "$<$<CXX_COMPILER_ID:Clang>:-std=c++1z>"
    "$<$<CXX_COMPILER_ID:GNU>:-std=c++1z>")

target_compile_definitions (
    hello_dave
    PUBLIC
)

target_include_directories (
    hello_dave
    PUBLIC
    DAVE
)

target_link_libraries (
    hello_dave
    PUBLIC
    DAVE
)

