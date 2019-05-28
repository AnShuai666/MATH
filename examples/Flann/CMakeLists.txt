include_directories(../../include)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/examples_bin)

#if (BUILD_C_BINDINGS)
    add_executable(flann_example_c flann_example.c)
    target_link_libraries(flann_example_c flann)
    set_target_properties(flann_example_c PROPERTIES COMPILE_FLAGS -std=c99)
#endif()
add_executable(flann_example_cpp flann_example.cpp)





