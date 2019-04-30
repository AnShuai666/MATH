include_directories(../../include/MATH)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/examples_bin)

add_executable(string_main string_main.cpp)
target_link_libraries(string_main math_util)

add_executable(logging_main logging_main.cpp)
target_link_libraries(logging_main math_util)

add_executable(file_system_main file_system_main.cpp)
target_link_libraries(file_system_main matrix_base math_util)

add_executable(ArgPaser_main ArgPaser_main.cpp)
target_link_libraries(ArgPaser_main math_util)

