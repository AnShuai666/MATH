include_directories(../../include)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/examples_bin)

add_executable(logging_main logging_main.cpp)
target_link_libraries(logging_main math_util)

