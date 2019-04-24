include_directories( ../../include)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/examples_bin)

add_executable(matrix_main matrix_main.cpp)
target_link_libraries(matrix_main matrix_base)

add_executable(file_main file_main.cpp)
target_link_libraries(file_main matrix_base math_util)