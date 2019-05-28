include_directories( ../../include)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/examples_bin)

add_executable(matrix_main matrix_main.cpp)
target_link_libraries(matrix_main matrix)

add_executable(vector_main vector_main.cpp)
target_link_libraries(vector_main matrix)

