include_directories(../../include)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(HEADERS
        ${PROJECT_SOURCE_DIR}/include/Matrix/define.h
        ${PROJECT_SOURCE_DIR}/include/Matrix/matrix.hpp
        ${PROJECT_SOURCE_DIR}/include/Matrix/vector.hpp
        ../../include/Matrix/algorithm_base.h )
set(SOURCE_FILES

        a.cpp ../../include/function/function.hpp)

add_library(matrix_base SHARED ${HEADERS} ${SOURCE_FILES})