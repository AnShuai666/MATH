include_directories(../include)
add_subdirectory(Geometry)
add_subdirectory(Graph)
add_subdirectory(Matrix)
add_subdirectory(Optimization)
add_subdirectory(Probability)
add_subdirectory(Function)
add_subdirectory(Util)


set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
link_directories(${PROJECT_SOURCE_DIR}/lib)

add_library(math SHARED Matrix/a.cpp)
target_link_libraries(math util function matrix)

install(TARGETS math
        LIBRARY DESTINATION lib/MATH
        ARCHIVE DESTINATION lib/MATH
        RUNTIME DESTINATION bin/MATH
        )
